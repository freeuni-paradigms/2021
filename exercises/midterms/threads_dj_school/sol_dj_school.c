#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

typedef struct {
  sem_t teacherSignal;
  sem_t studentSignal;
  bool available;
  int currStudentId;
  bool currMark;
  pthread_mutex_t lock;
} TeacherArgs;


sem_t studentDoneSem;
sem_t teachersDoneSem;
TeacherArgs teachers[MAX_NUM_TEACHERS];
sem_t teachersSem;
int g_num_teachers;
bool allStutentsDone;

void* Teacher(void* args) {
  int id = *(int*)args;
  // IMPLEMENT
  while (true) {
    sem_wait(&teachers[id].teacherSignal);
    if (allStutentsDone) {
      break;
    }
    teachers[id].currMark = TeacherEvaluateStudent(id, teachers[id].currStudentId);
    sem_post(&teachers[id].studentSignal);
  }
  TeacherDone(id);
  sem_post(&teachersDoneSem);
  return NULL;
}

void* Student(void* args) {
  int id = *(int*)args;
  bool mark = false;
  // IMPLEMENT
  while (!mark) {
    StudentRecordSet(id);
    sem_wait(&teachersSem);
    for (int teacherId = 0; teacherId < g_num_teachers; teacherId++) {
      pthread_mutex_lock(&teachers[teacherId].lock);
      if (!teachers[teacherId].available) {
        pthread_mutex_unlock(&teachers[teacherId].lock);
        continue;
      }
      teachers[teacherId].available = false;
      teachers[teacherId].currStudentId = id;
      pthread_mutex_unlock(&teachers[teacherId].lock);

      sem_post(&teachers[teacherId].teacherSignal);
      sem_wait(&teachers[teacherId].studentSignal);

      // აქ საჭიროა ლოქის აღება, იმიტომ რომ available-ცვლადზე რეიზ ქონდიშენი არ მოხდეს.
      pthread_mutex_lock(&teachers[teacherId].lock);
      mark = teachers[teacherId].currMark;
      teachers[teacherId].available = true;     
      pthread_mutex_unlock(&teachers[teacherId].lock);
      StudentWasEvaluatedByTeacher(id, teacherId, mark);
      break;
    }
    sem_post(&teachersSem);
  }
  StudentDone(id);
  sem_post(&studentDoneSem);
  return NULL;
}

void StartSchool(int num_students, int num_teachers) {
  // IMPLEMENT: Initialize semaphores and mutexes if needed.
  allStutentsDone = false;
  g_num_teachers = num_teachers;
  sem_init(&teachersSem, 0, num_teachers);
  int teacher_id[MAX_NUM_TEACHERS];
  int student_id[MAX_NUM_STUDENTS];
  for (int i = 0; i < num_teachers; ++i) {
    teacher_id[i] = i;
    pthread_t tid;
    teachers[i].available = true;
    sem_init(&teachers[i].studentSignal, 0, 0);
    sem_init(&teachers[i].teacherSignal, 0, 0);
    pthread_mutex_init(&teachers[i].lock, NULL);
    pthread_create(&tid, NULL, Teacher, &teacher_id[i]);
    pthread_detach(tid);
  }
  for (int i = 0; i < num_students; ++i) {
    student_id[i] = i;
    pthread_t tid;
    pthread_create(&tid, NULL, Student, &student_id[i]);
    pthread_detach(tid);
  }

  // IMPLEMENT: Wait for the all students and teachers to finish.
  for (int i = 0; i < num_students; i++) {
    sem_wait(&studentDoneSem);
  }

  allStutentsDone = true;
  for (int i = 0; i < num_teachers; i++) {
    sem_post(&teachers[i].teacherSignal);
  }

  for (int i = 0; i < num_teachers; i++) {
    sem_wait(&teachersDoneSem);
  }
  SchoolEnd();
}