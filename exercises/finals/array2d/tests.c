#include "array2d.h"
#include "str_array2d.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASSERT(expr) {							\
    if (!(expr)) {							\
    printf("%s:%d: Assertion failed: %s\n", __FILE__, __LINE__, #expr);	\
    return false;							\
  }									\
}

#define TEST(test) { \
    printf("++ RUNNING TEST: %s\n", #test);	\
    if ((test)()) {				\
      printf("-- TEST %s: SUCCEEDED\n", #test);	\
    } else {								\
      printf("-- TEST %s: FAILED !!!!!!!!!!!!!!!!!!!\n", #test);	\
    }									\
    printf("\n");							\
  }

// Array2D

bool Array2D_Integers_2x2_Get_Set() {
  int n = 2, m = 2;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(int), /*free_fn=*/NULL);
  int count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Array2DSet(&arr, i, j, &count);
      ASSERT(count == *(int*)Array2DGet(&arr, i, j));
      ++count;
    }
  }
  Array2DDestroy(&arr);
  return true;
}

bool Array2D_Integers_2x2_Get_Set_Overwrite() {
  int n = 2, m = 2;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(int), /*free_fn=*/NULL);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Array2DSet(&arr, i, j, &i);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ASSERT(i == *(int*)Array2DGet(&arr, i, j));
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int x = i * m + j;
      Array2DSet(&arr, i, j, &x);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int x = i * m + j;
      ASSERT(x == *(int*)Array2DGet(&arr, i, j));
    }
  }
  Array2DDestroy(&arr);
  return true;
}

void Add(void* sum, const void* elem, int i, int j) {
  *(int*)sum += *(const int*)elem;
}

bool Array2D_Integers_5x20_Iterate() {
  int n = 5, m = 20;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(int), /*free_fn=*/NULL);
  int count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Array2DSet(&arr, i, j, &count);
      ASSERT(*(int*)Array2DGet(&arr, i, j) == count);
      ++count;
    }
  }
  int sum = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, Add, &sum);
  ASSERT(sum == 99 * 100 / 2);
  Array2DDestroy(&arr);
  return true;
}

void AddDouble(void* sum, const void* elem, int i, int j) {
  *(int*)sum += *(const double*)elem;
}

bool Array2D_Doubles_5x20_Iterate_Remove_Iterate() {
  int n = 5, m = 20;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(double), /*free_fn=*/NULL);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      double x = i * m + j;
      Array2DSet(&arr, i, j, &x);
      ASSERT(x == *(double*)Array2DGet(&arr, i, j));
    }
  }
  int sum = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, AddDouble, &sum);
  ASSERT(sum == 99 * 100 / 2);
  int new_sum = sum;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i % 2 == 0 && j % 3 == 0) {
	Array2DRemove(&arr, i, j);
	new_sum -= i * m + j;
      }
    }
  }
  sum = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, AddDouble, &sum);
  ASSERT(new_sum == sum);
  Array2DDestroy(&arr);
  return true;
}

void CheckIfTrue(void* aux, const void* elem, int i, int j) {
  if (*(bool*)elem) {
    *(int*)aux += 1;
  }
}

bool Array2D_Bools_100x100_Grow_Iterate() {
  int n = 100, m = 100;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(bool), /*free_fn=*/NULL);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      bool x = (i % 2 == 0 && j % 2 == 0);
      if (x) {
	Array2DSet(&arr, i, j, &x);
      }
    }
  }
  int count_trues = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, CheckIfTrue, &count_trues);
  ASSERT(n * m / 4 == count_trues);
  Array2DGrow(&arr, n + 20, m + 30);
  count_trues = 0;
  Array2DIterate(&arr, 0, 0, n + 19, m + 29, CheckIfTrue, &count_trues);
  ASSERT(n * m / 4 == count_trues);
  Array2DDestroy(&arr);
  return true;
}

void StrFree(void* elem) {
  free(*(char**)elem);
}

bool Array2D_Strings_5x5_Overwrite() {
  Array2D arr;
  Array2DInit(&arr, 5, 5, sizeof(char*), StrFree);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      char val[10];
      sprintf(val, "%d-%d", i, j);
      char* x = strdup(val);
      Array2DSet(&arr, i, j, &x);
    }
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      char val[10];
      sprintf(val, "%d-%d", i, j);
      const void* x = Array2DGet(&arr, i, j);
      ASSERT(strcmp(val, *(char**)x) == 0);
    }
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      char val[10];
      sprintf(val, "%d-%d", j, i);  // reverse i, j order
      char* x = strdup(val);
      Array2DSet(&arr, i, j, &x);
    }
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      char val[10];
      sprintf(val, "%d-%d", j, i);
      const void* x = Array2DGet(&arr, i, j);
      ASSERT(strcmp(val, *(char**)x) == 0);
    }
  }
  Array2DDestroy(&arr);
  return true;
}

// StrArray2D

bool StrArray2D_Get_Set() {
  int n = 10, m = 10;
  StrArray2D arr;
  StrArray2DInit(&arr, n, m);
  for (int i = 0; i < n / 2; ++i) {
    for (int j = 0; j < m / 2; ++j) {
      char val[10];
      sprintf(val, "%d-%d", i, j);
      StrArray2DSet(&arr, i, j, strdup(val));
      ASSERT(0 == strcmp(val, StrArray2DGet(&arr, i, j)));
    }
  }
  StrArray2DDestroy(&arr);
  return true;
}

bool StrArray2D_Get_Set_Overwrite() {
  int n = 10, m = 10;
  StrArray2D arr;
  StrArray2DInit(&arr, n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char val[10];
      sprintf(val, "%d-%d", i, j);
      StrArray2DSet(&arr, i, j, strdup(val));
      ASSERT(0 == strcmp(val, StrArray2DGet(&arr, i, j)));
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char val[10];
      sprintf(val, "%d-%d", j, i);  // reverse order (j, i)
      StrArray2DSet(&arr, i, j, strdup(val));
      ASSERT(0 == strcmp(val, StrArray2DGet(&arr, i, j)));
    }
  }
  StrArray2DDestroy(&arr);
  return true;
}

void CountElements(void* aux, const void* elem, int i, int j) {
  *(int*)aux += 1;
}

bool StrArray2D_Remove() {
  StrArray2D arr;
  StrArray2DInit(&arr, 2, 2);
  StrArray2DSet(&arr, 0, 0, strdup("foo"));
  StrArray2DSet(&arr, 0, 1, strdup("foo"));
  StrArray2DSet(&arr, 1, 0, strdup("foo"));
  StrArray2DSet(&arr, 1, 1, strdup("foo"));
  // Assert all elements are set
  int count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT(4 == count);
  // Remove (0, 0)
  ASSERT(StrArray2DRemove(&arr, "foo"));
  ASSERT(0 == strcmp("foo", StrArray2DGet(&arr, 0, 1)));
  ASSERT(0 == strcmp("foo", StrArray2DGet(&arr, 1, 0)));
  ASSERT(0 == strcmp("foo", StrArray2DGet(&arr, 1, 1)));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT(3 == count);
  // Remove (0, 1)
  ASSERT(StrArray2DRemove(&arr, "foo"));
  ASSERT(0 == strcmp("foo", StrArray2DGet(&arr, 1, 0)));
  ASSERT(0 == strcmp("foo", StrArray2DGet(&arr, 1, 1)));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT(2 == count);
  // Remove (1, 0)
  StrArray2DRemove(&arr, "foo");
  ASSERT(0 == strcmp("foo", StrArray2DGet(&arr, 1, 1)));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT(1 == count);
  // Remove (1, 1)
  ASSERT(StrArray2DRemove(&arr, "foo"));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT(0 == count);
  // Nothing to remove
  ASSERT(!StrArray2DRemove(&arr, "foo"));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT(0 == count);
  StrArray2DDestroy(&arr);
  return true;
}

bool StrArray2D_Overwrite_Remove() {
  int n = 100, m = 100;
  StrArray2D arr;
  StrArray2DInit(&arr, n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char val[10];
      sprintf(val, "%d-%d", i, j);
      StrArray2DSet(&arr, i, j, strdup(val));
      ASSERT(0 == strcmp(val, StrArray2DGet(&arr, i, j)));
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char val[10];
      if (i % 2 == 0 || j % 2 == 0) {
	sprintf(val, "%d-%d", i, j);
	ASSERT(StrArray2DRemove(&arr, val));
      } else {
	sprintf(val, "%d-%d", j, i);  // reverse order (j, i)
	StrArray2DSet(&arr, i, j, strdup(val));
      }
    }
  }
  int count = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, CountElements, &count);
  ASSERT(n * m / 4 == count);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i % 2 != 0 && j % 2 != 0) {
	char val[10];
	sprintf(val, "%d-%d", j, i);  // (j, i)
	ASSERT(0 == strcmp(val, StrArray2DGet(&arr, i, j)));
      }
    }
  }
  StrArray2DDestroy(&arr);
  return true;
}

int main(int argc, char** argv) {
  // Array2D
  TEST(Array2D_Integers_2x2_Get_Set);
  TEST(Array2D_Integers_2x2_Get_Set_Overwrite);
  TEST(Array2D_Integers_5x20_Iterate);
  TEST(Array2D_Doubles_5x20_Iterate_Remove_Iterate);
  TEST(Array2D_Bools_100x100_Grow_Iterate)
  TEST(Array2D_Strings_5x5_Overwrite);
  // StrArray2D
  TEST(StrArray2D_Get_Set);
  TEST(StrArray2D_Get_Set_Overwrite);
  TEST(StrArray2D_Remove);
  TEST(StrArray2D_Overwrite_Remove);
  return 0;
}
