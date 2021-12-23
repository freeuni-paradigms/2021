#include "../array2d.h"
#include "../str_array2d.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gl/lunit/lunit.h"

// Array2D

TEST(Array2D_Integers_2x2_Get_Set) {
  int n = 2, m = 2;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(int), /*free_fn=*/NULL);
  int count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Array2DSet(&arr, i, j, &count);
      ASSERT_INT_EQ(count, *(int*)Array2DGet(&arr, i, j));
      --count;
    }
  }
  Array2DDestroy(&arr);
}

TEST(Array2D_Integers_2x2_Get_Set_Overwrite) {
  int n = 2, m = 2;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(int), /*free_fn=*/NULL);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Array2DSet(&arr, i, j, &j);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ASSERT_INT_EQ(j, *(int*)Array2DGet(&arr, i, j));
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int x = 1000 + i * m + j;
      Array2DSet(&arr, i, j, &x);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int x = 1000 + i * m + j;
      ASSERT_INT_EQ(x, *(int*)Array2DGet(&arr, i, j));
    }
  }
  Array2DDestroy(&arr);
}

void Add(void* sum, const void* elem, int i, int j) {
  *(int*)sum += *(const int*)elem;
}

TEST(Array2D_Integers_5x20_Iterate) {
  int n = 100, m = 200;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(int), /*free_fn=*/NULL);
  int count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Array2DSet(&arr, i, j, &count);
      ASSERT_INT_EQ(count, *(int*)Array2DGet(&arr, i, j));
      --count;
    }
  }
  int sum = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, Add, &sum);
  ASSERT_INT_EQ(sum, -19999 * 20000 / 2);
  Array2DDestroy(&arr);
}

void AddDouble(void* sum, const void* elem, int i, int j) {
  *(int*)sum += *(const double*)elem;
}

TEST(Array2D_Doubles_5x20_Iterate_Remove_Iterate) {
  int n = 5, m = 20;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(double), /*free_fn=*/NULL);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      double x = 1000 + i * m + j;
      Array2DSet(&arr, i, j, &x);
      ASSERT_DOUBLE_EQ(x,  *(double*)Array2DGet(&arr, i, j));
    }
  }
  int sum = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, AddDouble, &sum);
  ASSERT_INT_EQ(sum, 1000 * n * m + 99 * 100 / 2);
  int new_sum = sum;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i % 2 == 0 && j % 3 == 0) {
	Array2DRemove(&arr, i, j);
	new_sum -= 1000 + i * m + j;
      }
    }
  }
  sum = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, AddDouble, &sum);
  ASSERT_INT_EQ(new_sum, sum);
  Array2DDestroy(&arr);
}

void CheckIfTrue(void* aux, const void* elem, int i, int j) {
  if (*(bool*)elem) {
    *(int*)aux += 1;
  }
}

TEST(Array2D_Bools_100x100_Grow_Iterate) {
  int n = 100, m = 100;
  Array2D arr;
  Array2DInit(&arr, n, m, sizeof(bool), /*free_fn=*/NULL);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      bool x = (i % 2 == 0 || j % 2 == 0);
      if (x) {
	Array2DSet(&arr, i, j, &x);
      }
    }
  }
  int count_trues = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, CheckIfTrue, &count_trues);
  ASSERT_INT_EQ(n * m - n * m / 4, count_trues);
  Array2DGrow(&arr, n + 20, m + 30);
  count_trues = 0;
  Array2DIterate(&arr, 0, 0, n + 19, m + 29, CheckIfTrue, &count_trues);
  ASSERT_INT_EQ(n * m - n * m / 4, count_trues);
  Array2DDestroy(&arr);
}

void StrFree(void* elem) {
  free(*(char**)elem);
}

TEST(Array2D_Strings_5x5_Overwrite) {
  Array2D arr;
  Array2DInit(&arr, 5, 5, sizeof(char*), StrFree);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      char val[10];
      sprintf(val, "%d+%d", j, i);
      char* x = strdup(val);
      Array2DSet(&arr, i, j, &x);
    }
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      char val[10];
      sprintf(val, "%d+%d", j, i);
      const void* x = Array2DGet(&arr, i, j);
      ASSERT_STR_EQ(val, *(char**)x);
    }
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      char val[10];
      sprintf(val, "%d+%d", i, j);  // reverse j, i order
      char* x = strdup(val);
      Array2DSet(&arr, i, j, &x);
    }
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      char val[10];
      sprintf(val, "%d+%d", i, j);
      const void* x = Array2DGet(&arr, i, j);
      ASSERT_STR_EQ(val, *(char**)x);
    }
  }
  Array2DDestroy(&arr);
}

// StrArray2D

TEST(StrArray2D_Get_Set) {
  int n = 10, m = 10;
  StrArray2D arr;
  StrArray2DInit(&arr, n, m);
  for (int i = 0; i < n / 2; ++i) {
    for (int j = 0; j < m / 2; ++j) {
      char val[10];
      sprintf(val, "%d+%d", j, i);
      StrArray2DSet(&arr, i, j, strdup(val));
      ASSERT_STR_EQ(val, StrArray2DGet(&arr, i, j));
    }
  }
  StrArray2DDestroy(&arr);
}

TEST(StrArray2D_Get_Set_Overwrite) {
  int n = 10, m = 10;
  StrArray2D arr;
  StrArray2DInit(&arr, n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char val[10];
      sprintf(val, "%d+%d", j, i);
      StrArray2DSet(&arr, i, j, strdup(val));
      ASSERT_STR_EQ(val, StrArray2DGet(&arr, i, j));
    }
  }
  for (int i = n-1; i >= 0; --i) {
    for (int j = m-1; j >= 0; --j) {
      char val[10];
      sprintf(val, "%d+%d", i, j);  // reverse order (j, i)
      StrArray2DSet(&arr, i, j, strdup(val));
      ASSERT_STR_EQ(val, StrArray2DGet(&arr, i, j));
    }
  }
  StrArray2DDestroy(&arr);
}

void CountElements(void* aux, const void* elem, int i, int j) {
  *(int*)aux += 1;
}

TEST(StrArray2D_Remove) {
  StrArray2D arr;
  StrArray2DInit(&arr, 2, 2);
  StrArray2DSet(&arr, 0, 0, strdup("bar"));
  StrArray2DSet(&arr, 0, 1, strdup("bar"));
  StrArray2DSet(&arr, 1, 0, strdup("bar"));
  StrArray2DSet(&arr, 1, 1, strdup("bar"));
  // Assert all elements are set
  int count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT_INT_EQ(count, 4);
  // Remove (0, 0)
  ASSERT_TRUE(StrArray2DRemove(&arr, "bar"));
  ASSERT_STR_EQ("bar", StrArray2DGet(&arr, 0, 1));
  ASSERT_STR_EQ("bar", StrArray2DGet(&arr, 1, 0));
  ASSERT_STR_EQ("bar", StrArray2DGet(&arr, 1, 1));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT_INT_EQ(3, count);
  // Remove (0, 1)
  ASSERT_TRUE(StrArray2DRemove(&arr, "bar"));
  ASSERT_STR_EQ("bar", StrArray2DGet(&arr, 1, 0));
  ASSERT_STR_EQ("bar", StrArray2DGet(&arr, 1, 1));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT_INT_EQ(2, count);
  // Remove (1, 0)
  ASSERT_TRUE(StrArray2DRemove(&arr, "bar"));
  ASSERT_STR_EQ("bar", StrArray2DGet(&arr, 1, 1));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT_INT_EQ(1, count);
  // Remove (1, 1)
  ASSERT_TRUE(StrArray2DRemove(&arr, "bar"));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT_INT_EQ(0, count);
  // Nothing to remove
  ASSERT_FALSE(StrArray2DRemove(&arr, "bar"));
  count = 0;
  Array2DIterate(&arr, 0, 0, 1, 1, CountElements, &count);
  ASSERT_INT_EQ(0, count);
  StrArray2DDestroy(&arr);
}

TEST(StrArray2D_Overwrite_Remove) {
  int n = 100, m = 100;
  StrArray2D arr;
  StrArray2DInit(&arr, n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char val[10];
      sprintf(val, "%d+%d", j, i);
      StrArray2DSet(&arr, i, j, strdup(val));
      ASSERT_STR_EQ(val, StrArray2DGet(&arr, i, j));
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char val[10];
      if (i % 2 == 0 && j % 2 == 0) {
	sprintf(val, "%d+%d", j, i);
	ASSERT_TRUE(StrArray2DRemove(&arr, val));
      } else {
	sprintf(val, "%d+%d", i, j);  // reverse order (j, i)
	StrArray2DSet(&arr, i, j, strdup(val));
      }
    }
  }
  int count = 0;
  Array2DIterate(&arr, 0, 0, n - 1, m - 1, CountElements, &count);
  ASSERT_INT_EQ(n * m - n * m / 4, count);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i % 2 != 0 || j % 2 != 0) {
	char val[10];
	sprintf(val, "%d+%d", i, j);  // (j, i)
	ASSERT_STR_EQ(val, StrArray2DGet(&arr, i, j));
      }
    }
  }
  StrArray2DDestroy(&arr);
}

int main(int argc, char** argv) {
  LUnitOpts opts;
  LUnitOptsInit(&opts, argc, argv);

  TEST_SUITE_WITH_WEIGHT(gen, 0.7);
  TEST_SUITE_WITH_WEIGHT(str, 0.3);

  // Array2D
  ADD_TEST(gen, Array2D_Integers_2x2_Get_Set);
  ADD_TEST(gen, Array2D_Integers_2x2_Get_Set_Overwrite);
  ADD_TEST(gen, Array2D_Integers_5x20_Iterate);
  ADD_TEST(gen, Array2D_Doubles_5x20_Iterate_Remove_Iterate);
  ADD_TEST(gen, Array2D_Bools_100x100_Grow_Iterate)
  ADD_TEST(gen, Array2D_Strings_5x5_Overwrite);
  // StrArray2D
  ADD_TEST(str, StrArray2D_Get_Set);
  ADD_TEST(str, StrArray2D_Get_Set_Overwrite);
  ADD_TEST(str, StrArray2D_Remove);
  ADD_TEST(str, StrArray2D_Overwrite_Remove);

  TestSuite *suites[] = {&gen, &str};
  ProcessTestSuites(2, suites, &opts);
  TestSuiteDispose(&gen);
  TestSuiteDispose(&str);
  return 0;
}
