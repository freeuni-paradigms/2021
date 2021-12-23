typedef struct {
  char code[8];
  double credits;
} Subject;

typedef struct {
  char* name;
  Subject subjects[5];
} Student;

typedef int(*MatchFn)(Student*);

int FindStudent(MatchFn match_fn, Student* students, int n) {
  int i = 0;
  while (i < n) {
    if (match_fn(&students[i]) == 0) {
      break;
    }
    i++;
  }
  return (Student*)&students[0].subjects[i].code[2] - students;
}
