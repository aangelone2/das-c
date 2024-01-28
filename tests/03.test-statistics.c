#include "das-c/statistics.h"
#include "das-c/vector.h"
#include "test.h"

vector *short_vector()
{
  vector *vec = init_vector();

  push_back(vec, 0.1);
  push_back(vec, 0.2);
  push_back(vec, 0.3);
  push_back(vec, 0.4);
  push_back(vec, 0.5);
  push_back(vec, 0.6);

  return vec;
}

void test_average()
{
  vector *vec = short_vector();

  assert_double_eq(average(vec, 0), 0.35);
  assert_double_eq(average(vec, 2), 0.45);

  clear_vector(vec);
}

void test_sem()
{
  vector *vec = short_vector();

  assert_double_eq(sem(vec, 0, average(vec, 0)), 0.0763762615826);
  assert_double_eq(sem(vec, 2, average(vec, 2)), 0.0645497224368);

  clear_vector(vec);
}

vector *long_vector()
{
  vector *vec = init_vector();

  for (size_t i = 0; i < 64; ++i)
    push_back(vec, example_data[i]);

  return vec;
}

void test_rebin()
{
  vector *vec = long_vector();

  rebin(vec, 0, 8);
  assert(vec->size == 8);
  assert_double_eq(vec->data[0], 0.53702232875);
  assert_double_eq(vec->data[1], 0.43452742125);
  assert_double_eq(vec->data[2], 0.44530370625);
  assert_double_eq(vec->data[3], 0.52863834125);
  assert_double_eq(vec->data[4], 0.62315147625);
  assert_double_eq(vec->data[5], 0.69273619500);
  assert_double_eq(vec->data[6], 0.76592960125);
  assert_double_eq(vec->data[7], 0.52890948125);

  rebin(vec, 0, 4);
  assert(vec->size == 4);
  assert_double_eq(vec->data[0], 0.485774875000);
  assert_double_eq(vec->data[1], 0.486971023750);
  assert_double_eq(vec->data[2], 0.657943835625);
  assert_double_eq(vec->data[3], 0.647419541250);

  rebin(vec, 0, 2);
  assert(vec->size == 2);
  assert_double_eq(vec->data[0], 0.4863729493750);
  assert_double_eq(vec->data[1], 0.6526816884375);

  clear_vector(vec);
}

vector *long_vector_skip_4()
{
  vector *vec = init_vector();

  for (size_t i = 0; i < 60; ++i)
    push_back(vec, example_data[i + 4]);

  return vec;
}

void test_rebin_skipping()
{
  vector *long_skip = long_vector_skip_4();

  // Explicit and automatic skipping
  rebin(long_skip, 6, 10);
  assert(long_skip->size == 10);
  assert_double_eq(long_skip->data[0], 0.3324987080000);
  assert_double_eq(long_skip->data[1], 0.5226791060000);
  assert_double_eq(long_skip->data[2], 0.6084080020000);
  assert_double_eq(long_skip->data[3], 0.5085241380000);
  assert_double_eq(long_skip->data[4], 0.5516339640000);
  assert_double_eq(long_skip->data[5], 0.6362853160000);
  assert_double_eq(long_skip->data[6], 0.8457914740000);
  assert_double_eq(long_skip->data[7], 0.7377503400000);
  assert_double_eq(long_skip->data[8], 0.5791360240000);
  assert_double_eq(long_skip->data[9], 0.5554548940000);

  // Only explicit skipping
  rebin(long_skip, 2, 4);
  assert(long_skip->size == 4);
  assert_double_eq(long_skip->data[0], 0.5584660700000);
  assert_double_eq(long_skip->data[1], 0.5939596400000);
  assert_double_eq(long_skip->data[2], 0.7917709070000);
  assert_double_eq(long_skip->data[3], 0.5672954590000);

  vector *short_vec = short_vector();
  push_back(short_vec, 0.7);

  // Only automatic skipping
  rebin(short_vec, 0, 2);
  assert(short_vec->size == 2);
  assert_double_eq(short_vec->data[0], 0.3);
  assert_double_eq(short_vec->data[1], 0.6);

  // Only automatic skipping, trivial bins
  rebin(long_skip, 0, 3);
  assert(long_skip->size == 3);
  assert_double_eq(long_skip->data[0], 0.5939596400000);
  assert_double_eq(long_skip->data[1], 0.7917709070000);
  assert_double_eq(long_skip->data[2], 0.5672954590000);

  clear_vector(short_vec);
  clear_vector(long_skip);
}

int main()
{
  open_test();

  printf("  Testing average...\n");
  test_average();

  printf("  Testing SEM...\n");
  test_sem();

  printf("  Testing rebinning...\n");
  test_rebin();

  printf("  Testing rebinning with skipping...\n");
  test_rebin_skipping();

  close_test();
}
