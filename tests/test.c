#include "test.h"
#include <stdlib.h>

// Tracks `resources/08.valid.dat`.
const double example_data[64] = {
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

// Tracks `resources/09.valid_with_comments.dat`.
const double example_data_with_comments[59] = {
    0.52911939, 0.73394662, 0.92435968, 0.53180354, 0.84267985, 0.38490556,
    0.05959652, 0.42611364, 0.17004642, 0.43721467, 0.14169525, 0.62928515,
    0.95840482, 0.53496401, 0.17849541, 0.47191324, 0.00865848, 0.4684624,
    0.39706694, 0.57045578, 0.63760862, 0.52515024, 0.13985747, 0.61936499,
    0.61601736, 0.86266411, 0.80413608, 0.03856856, 0.48135218, 0.66714598,
    0.854229,   0.50132497, 0.51403939, 0.99461874, 0.56004771, 0.06519901,
    0.62426497, 0.87148802, 0.353082,   0.22394679, 0.99101708, 0.74189269,
    0.66470523, 0.9989759,  0.63068782, 0.93758205, 0.99700637, 0.90916311,
    0.92651339, 0.45752617, 0.89428355, 0.54739519, 0.72269107, 0.2213911,
    0.50991921, 0.76931588, 0.90287561, 0.38108331, 0.2658589,
};

void test_too_many_fields(clargs args, parsing_func parse)
{
  args.filename = "../resources/05.too_many_fields.dat";
  parse_info *info = alloc_parse_info(&args);

  table tab;
  assert(parse(&tab, info) == 3);

  deinit_table(&tab);
  free_parse_info(info);
  deinit_clargs(&args);
}

void test_invalid_field(clargs args, parsing_func parse)
{
  args.filename = "../resources/06.invalid_field.dat";
  parse_info *info = alloc_parse_info(&args);

  table tab;
  assert(parse(&tab, info) == 2);

  deinit_table(&tab);
  free_parse_info(info);
  deinit_clargs(&args);
}

void test_too_few_fields(clargs args, parsing_func parse)
{
  args.filename = "../resources/07.too_few_fields.dat";
  parse_info *info = alloc_parse_info(&args);

  table tab;
  assert(parse(&tab, info) == 4);

  deinit_table(&tab);
  free_parse_info(info);
  deinit_clargs(&args);
}

void test_valid_full(clargs args, parsing_func parse)
{
  args.filename = "../resources/08.valid.dat";
  parse_info *info = alloc_parse_info(&args);

  table tab;
  assert(!parse(&tab, info));

  assert(tab.cols == 4);
  for (size_t ic = 0; ic < tab.cols; ++ic)
  {
    assert(tab.rows == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(tab.data[ir][ic], (double)(ic) + example_data[ir]);
  }

  deinit_table(&tab);
  free_parse_info(info);
  deinit_clargs(&args);
}

void test_filtering(clargs args, parsing_func parse)
{
  args.filename = "../resources/08.valid.dat";
  args.n_fields = 2;
  args.fields = malloc(2 * sizeof(size_t));
  args.fields[0] = 2;
  args.fields[1] = 3;
  parse_info *info = alloc_parse_info(&args);

  table tab;
  assert(!parse(&tab, info));

  assert(tab.cols == 2);
  for (size_t ic = 0; ic < tab.cols; ++ic)
  {
    assert(tab.rows == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(
          tab.data[ir][ic], (double)(ic) + 1.0 + example_data[ir]
      );
  }

  deinit_table(&tab);
  free_parse_info(info);
  deinit_clargs(&args);
}

void test_valid_full_with_comments(clargs args, parsing_func parse)
{
  args.filename = "../resources/09.valid_with_comments.dat";
  parse_info *info = alloc_parse_info(&args);

  table tab;
  assert(!parse(&tab, info));

  assert(tab.cols == 4);
  for (size_t ic = 0; ic < tab.cols; ++ic)
  {
    assert(tab.rows == 59);

    // Checking each component
    for (size_t ir = 0; ir < 59; ++ir)
      assert_double_eq(
          tab.data[ir][ic], (double)(ic) + example_data_with_comments[ir]
      );
  }

  deinit_table(&tab);
  free_parse_info(info);
  deinit_clargs(&args);
}

void test_4_threads(clargs args, parsing_func parse)
{
  args.n_threads = 4;
  args.filename = "../resources/08.valid.dat";
  parse_info *info = alloc_parse_info(&args);

  table tab;
  assert(!parse(&tab, info));

  assert(tab.cols == 4);
  for (size_t ic = 0; ic < tab.cols; ++ic)
  {
    assert(tab.rows == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(tab.data[ir][ic], (double)(ic) + example_data[ir]);
  }

  deinit_table(&tab);
  free_parse_info(info);
  deinit_clargs(&args);
}

void test_imperfect_splitting(clargs args, parsing_func parse)
{
  args.n_threads = 3;
  args.filename = "../resources/08.valid.dat";
  parse_info *info = alloc_parse_info(&args);

  table tab;
  assert(!parse(&tab, info));

  assert(tab.cols == 4);
  for (size_t ic = 0; ic < tab.cols; ++ic)
  {
    assert(tab.rows == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(tab.data[ir][ic], (double)(ic) + example_data[ir]);
  }

  deinit_table(&tab);
  free_parse_info(info);
  deinit_clargs(&args);
}
