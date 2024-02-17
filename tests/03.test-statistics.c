#include "das-c/statistics.h"
#include "das-c/table.h"
#include "test.h"
#include <stdlib.h>

table short_table_6()
{
  table tab;
  init_table(&tab, 6, 1);

  double content[6] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6};

  for (size_t ir = 0; ir < 6; ++ir)
    tab.data[ir][0] = content[ir];

  return tab;
}

void test_average()
{
  table tab = short_table_6();

  double *res;

  // No skipping
  res = average(&tab, 0);
  assert_double_eq(res[0], 0.35);
  free(res);

  // Skipping 2 rows
  res = average(&tab, 2);
  assert_double_eq(res[0], 0.45);
  free(res);

  deinit_table(&tab);
}

void test_sem()
{
  table tab = short_table_6();

  double *ave;
  double *res;

  // No skipping
  ave = average(&tab, 0);
  res = sem(&tab, 0, ave);
  assert_double_eq(res[0], 0.0763762615826);
  free(res);
  free(ave);

  // Skipping 2 rows
  ave = average(&tab, 2);
  res = sem(&tab, 2, ave);
  assert_double_eq(res[0], 0.0645497224368);
  free(res);
  free(ave);

  deinit_table(&tab);
}

table long_table()
{
  table tab;
  init_table(&tab, 64, 1);

  for (size_t ir = 0; ir < 64; ++ir)
    tab.data[ir][0] = example_data[ir];

  return tab;
}

void test_rebin()
{
  table tab = long_table();

  rebin(&tab, 0, 8);
  assert(tab.rows == 8);
  assert_double_eq(tab.data[0][0], 0.53702232875);
  assert_double_eq(tab.data[1][0], 0.43452742125);
  assert_double_eq(tab.data[2][0], 0.44530370625);
  assert_double_eq(tab.data[3][0], 0.52863834125);
  assert_double_eq(tab.data[4][0], 0.62315147625);
  assert_double_eq(tab.data[5][0], 0.69273619500);
  assert_double_eq(tab.data[6][0], 0.76592960125);
  assert_double_eq(tab.data[7][0], 0.52890948125);

  rebin(&tab, 0, 4);
  assert(tab.rows == 4);
  assert_double_eq(tab.data[0][0], 0.485774875000);
  assert_double_eq(tab.data[1][0], 0.486971023750);
  assert_double_eq(tab.data[2][0], 0.657943835625);
  assert_double_eq(tab.data[3][0], 0.647419541250);

  rebin(&tab, 0, 2);
  assert(tab.rows == 2);
  assert_double_eq(tab.data[0][0], 0.4863729493750);
  assert_double_eq(tab.data[1][0], 0.6526816884375);

  deinit_table(&tab);
}

table long_vector_skip_4()
{
  table tab;
  init_table(&tab, 60, 1);

  for (size_t ir = 0; ir < 60; ++ir)
    tab.data[ir][0] = example_data[ir + 4];

  return tab;
}

table short_table_7()
{
  table tab;
  init_table(&tab, 7, 1);

  double content[7] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7};

  for (size_t ir = 0; ir < 7; ++ir)
    tab.data[ir][0] = content[ir];

  return tab;
}

void test_rebin_skipping()
{
  table long_skip = long_vector_skip_4();

  // Explicit and automatic skipping
  rebin(&long_skip, 6, 10);
  assert(long_skip.rows == 10);
  assert_double_eq(long_skip.data[0][0], 0.3324987080000);
  assert_double_eq(long_skip.data[1][0], 0.5226791060000);
  assert_double_eq(long_skip.data[2][0], 0.6084080020000);
  assert_double_eq(long_skip.data[3][0], 0.5085241380000);
  assert_double_eq(long_skip.data[4][0], 0.5516339640000);
  assert_double_eq(long_skip.data[5][0], 0.6362853160000);
  assert_double_eq(long_skip.data[6][0], 0.8457914740000);
  assert_double_eq(long_skip.data[7][0], 0.7377503400000);
  assert_double_eq(long_skip.data[8][0], 0.5791360240000);
  assert_double_eq(long_skip.data[9][0], 0.5554548940000);

  // Only explicit skipping
  rebin(&long_skip, 2, 4);
  assert(long_skip.rows == 4);
  assert_double_eq(long_skip.data[0][0], 0.5584660700000);
  assert_double_eq(long_skip.data[1][0], 0.5939596400000);
  assert_double_eq(long_skip.data[2][0], 0.7917709070000);
  assert_double_eq(long_skip.data[3][0], 0.5672954590000);

  // Only automatic skipping, trivial bins
  rebin(&long_skip, 0, 3);
  assert(long_skip.rows == 3);
  assert_double_eq(long_skip.data[0][0], 0.5939596400000);
  assert_double_eq(long_skip.data[1][0], 0.7917709070000);
  assert_double_eq(long_skip.data[2][0], 0.5672954590000);

  table short_tab = short_table_7();

  // Only automatic skipping
  rebin(&short_tab, 0, 2);
  assert(short_tab.rows == 2);
  assert_double_eq(short_tab.data[0][0], 0.3);
  assert_double_eq(short_tab.data[1][0], 0.6);

  deinit_table(&short_tab);
  deinit_table(&long_skip);
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
