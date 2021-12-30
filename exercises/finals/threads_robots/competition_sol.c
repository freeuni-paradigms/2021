#include "competition_sol.h"

#include <stdlib.h>

#include "robot.h"

void CompetitionInit(Competition* comp) {
  comp->robots_fighting = 0;
  comp->robots_in_queue = 0;
  comp->can_add_participant = true;
  comp->winner = NULL;
  pthread_mutex_init(&comp->lock, NULL);
  pthread_cond_init(&comp->cond, NULL);
  pthread_cond_init(&comp->winner_cond, NULL);
}

typedef struct {
  Competition* comp;
  const Robot* x;
  const Robot* y;
} FightData;

void* fight(void * data) {
  FightData * fightData = data;
  const Robot * winner = NULL;
  if (RobotFightWith(fightData->x, fightData->y)) {
    winner = fightData->x;
  } else {
    winner = fightData->y;
  }

  Competition* comp = fightData->comp;
  pthread_mutex_lock(&comp->lock);
  comp->robots_fighting -= 2;
  comp->robots[fightData->comp->robots_in_queue] = winner;
  comp->robots_in_queue++;
  pthread_cond_signal(&comp->cond);
  pthread_mutex_unlock(&comp->lock);

  free(data);
  return NULL;
}


void * Start(void * data) {
  Competition* comp = data;

  const Robot * x = NULL;
  while (true) {
    const Robot * y;

    pthread_mutex_lock(&comp->lock);
    bool finished = false;
    while(comp->robots_in_queue == 0) {
      if (comp->robots_fighting > 0 || comp->can_add_participant) {
        pthread_cond_wait(&comp->cond, &comp->lock);
      } else {
        finished = true;
        break;
      }
    }

    if (finished) {
      pthread_mutex_unlock(&comp->lock);
      break;
    }

    comp->robots_in_queue--;
    y = comp->robots[comp->robots_in_queue];
    pthread_mutex_unlock(&comp->lock);
    
    if (x == NULL) {
      x = y;
      continue;
    }

    pthread_t fight_thread;
    FightData* fightData = malloc(sizeof(FightData));
    fightData->comp = comp;
    fightData->x = x;
    fightData->y = y;
    x = NULL;
    y = NULL;

    pthread_mutex_lock(&comp->lock);
    comp->robots_fighting += 2;
    pthread_mutex_unlock(&comp->lock);
    pthread_create(&fight_thread, NULL, fight, fightData);
    // pthread_detach(fight_thread);
  }

  pthread_mutex_lock(&comp->lock);
  comp->winner = x;
  pthread_cond_signal(&comp->winner_cond);
  pthread_mutex_unlock(&comp->lock);

  return NULL;
}

void CompetitionStart(Competition* comp) {
  pthread_t start_thread;
  pthread_create(&start_thread, NULL, Start, comp);
  pthread_detach(start_thread);
}

const Robot* CompetitionStop(Competition* comp) {
  pthread_mutex_lock(&comp->lock);
  comp->can_add_participant = false;
  pthread_cond_signal(&comp->cond);
  while (comp->winner == NULL) {
    pthread_cond_wait(&comp->winner_cond, &comp->lock);
  }
  pthread_mutex_unlock(&comp->lock);

  pthread_mutex_destroy(&comp->lock);
  pthread_cond_destroy(&comp->cond);
  pthread_cond_destroy(&comp->winner_cond);

  return comp->winner;
}

bool CompetitionAddParticipant(Competition* comp, const Robot* robot) {
  pthread_mutex_lock(&comp->lock);
  if (!comp->can_add_participant) {
    pthread_mutex_unlock(&comp->lock);
    return false;
  }

  comp->robots[comp->robots_in_queue] = robot;
  comp->robots_in_queue++;
  pthread_mutex_unlock(&comp->lock);
  
  return true;
}
