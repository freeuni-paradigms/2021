#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

typedef struct {
  int id;
  bool available;
  int currStudentId;
  bool currMark;
  bool allStutentsDone;
  pthread_mutex_t lock;
  sem_t studentSignal;
  sem_t teacherSignal;
  sem_t* teachersDoneSem;
} TeacherArgs;

void* Teacher(void* args) {
  TeacherArgs* teacher = args;
  // IMPLEMENT
  while (true) {
    sem_wait(&teacher->teacherSignal);
    if (teacher->allStutentsDone) {
      break;
    }
    teacher->currMark = TeacherEvaluateStudent(teacher->id, teacher->currStudentId);
    sem_post(&teacher->studentSignal);
  }
  TeacherDone(teacher->id);
  sem_post(teacher->teachersDoneSem);
  return NULL;
}

typedef struct {
  int id;
  int num_teachers;
  TeacherArgs* teachers;
  sem_t* studentsDoneSem;
  sem_t* teachersSem;
} StudentArgs;

void* Student(void* args) {
  StudentArgs* student = args;
  bool mark = false;
  // IMPLEMENT
  while (!mark) {
    StudentRecordSet(student->id);
    sem_wait(student->teachersSem);
    for (int teacherId = 0; teacherId < student->num_teachers; teacherId++) {
      pthread_mutex_lock(&student->teachers[teacherId].lock);
      if (!student->teachers[teacherId].available) {
        pthread_mutex_unlock(&student->teachers[teacherId].lock);
        continue;
      }
      student->teachers[teacherId].available = false;
      student->teachers[teacherId].currStudentId = student->id;
      pthread_mutex_unlock(&student->teachers[teacherId].lock);

      sem_post(&student->teachers[teacherId].teacherSignal);
      sem_wait(&student->teachers[teacherId].studentSignal);

      // აქ საჭიროა ლოქის აღება, იმიტომ რომ available-ცვლადზე რეიზ ქონდიშენი არ მოხდეს.
      pthread_mutex_lock(&student->teachers[teacherId].lock);
      mark = student->teachers[teacherId].currMark;
      student->teachers[teacherId].available = true;     
      pthread_mutex_unlock(&student->teachers[teacherId].lock);
      StudentWasEvaluatedByTeacher(student->id, teacherId, mark);
      break;
    }
    sem_post(student->teachersSem);
  }
  StudentDone(student->id);
  sem_post(student->studentsDoneSem);
  return NULL;
}

void StartSchool(int num_students, int num_teachers) {
  // IMPLEMENT: Initialize semaphores and mutexes if needed.
  sem_t teachersDoneSem;
  sem_init(&teachersDoneSem, 0, 0);

  TeacherArgs teachers[MAX_NUM_TEACHERS];
  for (int i = 0; i < num_teachers; ++i) {
    teachers[i].id = i;
    teachers[i].available = true;
    teachers[i].allStutentsDone = false;
    pthread_mutex_init(&teachers[i].lock, NULL);
    sem_init(&teachers[i].studentSignal, 0, 0);
    sem_init(&teachers[i].teacherSignal, 0, 0);
    teachers[i].teachersDoneSem = &teachersDoneSem;
    
    pthread_t tid;
    pthread_create(&tid, NULL, Teacher, &teachers[i]);
    pthread_detach(tid);
  }

  sem_t studentsDoneSem;
  sem_t teachersSem;
  sem_init(&studentsDoneSem, 0, 0);
  sem_init(&teachersSem, 0, num_teachers);

  StudentArgs students[MAX_NUM_STUDENTS];
  for (int i = 0; i < num_students; ++i) {
    students[i].id = i;
    students[i].num_teachers = num_teachers;
    students[i].teachers = teachers;
    students[i].studentsDoneSem = &studentsDoneSem;
    students[i].teachersSem = &teachersSem;
    
    pthread_t tid;
    pthread_create(&tid, NULL, Student, &students[i]);
    pthread_detach(tid);
  }

  // IMPLEMENT: Wait for the all students and teachers to finish.
  for (int i = 0; i < num_students; i++) {
    sem_wait(&studentsDoneSem);
  }

  for (int i = 0; i < num_teachers; i++) {
    teachers[i].allStutentsDone = true;
    sem_post(&teachers[i].teacherSignal);
  }

  for (int i = 0; i < num_teachers; i++) {
    sem_wait(&teachersDoneSem);
  }
  SchoolEnd();
}