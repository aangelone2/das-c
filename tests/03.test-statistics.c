#include "das-c/statistics.h"
#include "das-c/vector.h"
#include "test.h"

vector init_short_vec()
{
  vector vec;
  init_vector(&vec);

  push_back(&vec, 0.1);
  push_back(&vec, 0.2);
  push_back(&vec, 0.3);
  push_back(&vec, 0.4);
  push_back(&vec, 0.5);
  push_back(&vec, 0.6);

  return vec;
}

void test_average()
{
  vector vec = init_short_vec();

  assert_double_eq(average(&vec, 0), 0.35);
  assert_double_eq(average(&vec, 2), 0.45);
  assert_double_eq(average(&vec, 6), 0.00);
  assert_double_eq(average(&vec, 8), 0.00);

  deinit_vector(&vec);
}

void test_sem()
{
  vector vec = init_short_vec();

  assert_double_eq(sem(&vec, 0, average(&vec, 0)), 0.0763762615826);
  assert_double_eq(sem(&vec, 2, average(&vec, 2)), 0.0645497224368);
  assert_double_eq(sem(&vec, 6, average(&vec, 6)), 0.00);
  assert_double_eq(sem(&vec, 8, average(&vec, 8)), 0.00);

  deinit_vector(&vec);
}

double data[64] = {
    0.52911939, 0.73394662, 0.92435968, 0.53180354, 0.84267985, 0.38490556,
    0.28976747, 0.05959652, 0.42611364, 0.17004642, 0.43721467, 0.14169525,
    0.62928515, 0.95840482, 0.53496401, 0.17849541, 0.47191324, 0.00865848,
    0.4684624,  0.48311395, 0.39706694, 0.57045578, 0.63760862, 0.52515024,
    0.13985747, 0.61936499, 0.61601736, 0.86266411, 0.80413608, 0.03856856,
    0.48135218, 0.66714598, 0.854229,   0.50132497, 0.51403939, 0.99461874,
    0.56004771, 0.06519901, 0.62426497, 0.87148802, 0.353082,   0.22394679,
    0.99101708, 0.74189269, 0.66470523, 0.9989759,  0.63068782, 0.93758205,
    0.99700637, 0.56564222, 0.82990681, 0.90916311, 0.92651339, 0.45752617,
    0.89428355, 0.54739519, 0.72269107, 0.2213911,  0.50991921, 0.76931588,
    0.90287561, 0.45814077, 0.38108331, 0.2658589,
};

vector init_long_vector()
{
  vector vec;
  init_vector(&vec);

  for (size_t i = 0; i < 64; ++i)
    push_back(&vec, data[i]);

  return vec;
}

void test_rebin()
{
  vector vec = init_long_vector();

  assert(!rebin(&vec, 0, 8));
  assert(vec.size == 8);
  assert_double_eq(vec.data[0], 0.53702232875);
  assert_double_eq(vec.data[1], 0.43452742125);
  assert_double_eq(vec.data[2], 0.44530370625);
  assert_double_eq(vec.data[3], 0.52863834125);
  assert_double_eq(vec.data[4], 0.62315147625);
  assert_double_eq(vec.data[5], 0.69273619500);
  assert_double_eq(vec.data[6], 0.76592960125);
  assert_double_eq(vec.data[7], 0.52890948125);

  assert(!rebin(&vec, 0, 4));
  assert(vec.size == 4);
  assert_double_eq(vec.data[0], 0.485774875000);
  assert_double_eq(vec.data[1], 0.486971023750);
  assert_double_eq(vec.data[2], 0.657943835625);
  assert_double_eq(vec.data[3], 0.647419541250);

  assert(!rebin(&vec, 0, 2));
  assert(vec.size == 2);
  assert_double_eq(vec.data[0], 0.4863729493750);
  assert_double_eq(vec.data[1], 0.6526816884375);

  deinit_vector(&vec);
}

vector init_long_vector_skip_4()
{
  vector vec;
  init_vector(&vec);

  for (size_t i = 0; i < 60; ++i)
    push_back(&vec, data[i + 4]);

  return vec;
}

void test_rebin_skipping()
{
  vector long_skip = init_long_vector_skip_4();

  // Explicit and automatic skipping
  assert(!rebin(&long_skip, 6, 10));
  assert(long_skip.size == 10);
  assert_double_eq(long_skip.data[0], 0.3324987080000);
  assert_double_eq(long_skip.data[1], 0.5226791060000);
  assert_double_eq(long_skip.data[2], 0.6084080020000);
  assert_double_eq(long_skip.data[3], 0.5085241380000);
  assert_double_eq(long_skip.data[4], 0.5516339640000);
  assert_double_eq(long_skip.data[5], 0.6362853160000);
  assert_double_eq(long_skip.data[6], 0.8457914740000);
  assert_double_eq(long_skip.data[7], 0.7377503400000);
  assert_double_eq(long_skip.data[8], 0.5791360240000);
  assert_double_eq(long_skip.data[9], 0.5554548940000);

  // Only explicit skipping
  assert(!rebin(&long_skip, 2, 4));
  assert(long_skip.size == 4);
  assert_double_eq(long_skip.data[0], 0.5584660700000);
  assert_double_eq(long_skip.data[1], 0.5939596400000);
  assert_double_eq(long_skip.data[2], 0.7917709070000);
  assert_double_eq(long_skip.data[3], 0.5672954590000);

  vector short_vec = init_short_vec();
  push_back(&short_vec, 0.7);

  // Only automatic skipping
  assert(!rebin(&short_vec, 0, 2));
  assert(short_vec.size == 2);
  assert_double_eq(short_vec.data[0], 0.3);
  assert_double_eq(short_vec.data[1], 0.6);

  // Only automatic skipping, trivial bins
  assert(!rebin(&long_skip, 0, 3));
  assert(long_skip.size == 3);
  assert_double_eq(long_skip.data[0], 0.5939596400000);
  assert_double_eq(long_skip.data[1], 0.7917709070000);
  assert_double_eq(long_skip.data[2], 0.5672954590000);

  deinit_vector(&short_vec);
  deinit_vector(&long_skip);
}

void test_rebin_invalid()
{
  vector long_skip = init_long_vector_skip_4();

  // Rebinning for subsequent tests
  assert(!rebin(&long_skip, 0, 3));
  assert(long_skip.size == 3);
  assert_double_eq(long_skip.data[0], 0.4307799210000);
  assert_double_eq(long_skip.data[1], 0.5762128550000);
  assert_double_eq(long_skip.data[2], 0.6795331830000);

  // Invalid skipping, no change
  assert(rebin(&long_skip, 5, 3) == 1);
  assert(long_skip.size == 3);
  assert_double_eq(long_skip.data[0], 0.4307799210000);
  assert_double_eq(long_skip.data[1], 0.5762128550000);
  assert_double_eq(long_skip.data[2], 0.6795331830000);

  // Invalid bin number, no change
  assert(rebin(&long_skip, 0, 5) == 1);
  assert(long_skip.size == 3);
  assert_double_eq(long_skip.data[0], 0.4307799210000);
  assert_double_eq(long_skip.data[1], 0.5762128550000);
  assert_double_eq(long_skip.data[2], 0.6795331830000);

  // Invalid bin number given skip, no change
  assert(rebin(&long_skip, 1, 3) == 1);
  assert(long_skip.size == 3);
  assert_double_eq(long_skip.data[0], 0.4307799210000);
  assert_double_eq(long_skip.data[1], 0.5762128550000);
  assert_double_eq(long_skip.data[2], 0.6795331830000);

  deinit_vector(&long_skip);
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

  printf("  Testing invalid rebinnings...\n");
  test_rebin_invalid();

  close_test();
}
