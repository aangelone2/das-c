#include "das-c/statistics.h"
#include "das-c/vector.h"
#include "test.h"

int main()
{
  open_test();

  vector vec;
  init_vector(&vec);

  push_back(&vec, 0.1);
  push_back(&vec, 0.2);
  push_back(&vec, 0.3);
  push_back(&vec, 0.4);
  push_back(&vec, 0.5);
  push_back(&vec, 0.6);

  printf("  Testing average...\n");
  assert_double_eq(average(&vec, 0), 0.35);
  assert_double_eq(average(&vec, 2), 0.45);
  assert_double_eq(average(&vec, 6), 0.00);
  assert_double_eq(average(&vec, 8), 0.00);

  printf("  Testing SEM...\n");
  assert_double_eq(sem(&vec, 0, average(&vec, 0)), 0.07637626);
  assert_double_eq(sem(&vec, 2, average(&vec, 2)), 0.05270463);
  assert_double_eq(sem(&vec, 6, average(&vec, 6)), 0.00);
  assert_double_eq(sem(&vec, 8, average(&vec, 8)), 0.00);

  deinit_vector(&vec);

  close_test();
}
