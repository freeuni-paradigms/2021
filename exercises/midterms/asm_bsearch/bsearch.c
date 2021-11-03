typedef struct {
  int age;
  char *name;
} Owner;

typedef struct {
  int mileage;
  bool lights[4];
  Owner owner;
} Car;

typedef int (*StrCmp)(char *, char *);

int bsearch(Car *cars, int n, char *person, StrCmp cmp_fn) {
  int l = 0;
  int r = n;
  while (l < r) {
    short m = (l + r) / 2;
    r = m;
    if (cmp_fn((Owner *)(cars[m].lights)->name, person) < 0) {
      l = m;
    }
  }
  return l;
}