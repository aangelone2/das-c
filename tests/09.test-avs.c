#include "das-c/avs.h"
#include "test.h"
#include <stdlib.h>

void test_simple()
{
  // Parsing all 3 fields, skipping 20%
  clargs args;
  args.n_fields = 4;
  args.skip = 20;
  // Different parallelism mode tested in parsing
  args.mode = DASC_PARALLEL_MODE_THR;
  args.n_threads = 1;
  args.verbose = false;
  args.filename = "../resources/10.avs.dat";

  args.fields = NULL;

  avs_results *res = avs(&args);

  assert(res->rows == 3257);
  assert(res->kept == 2606);

  assert(res->cols == 3);

  assert(res->fields[0] == 0);
  assert(res->fields[1] == 1);
  assert(res->fields[2] == 2);

  assert_double_eq(res->ave[0], 0.5151493365490240);
  assert_double_eq(res->ave[1], 0.4957831770435258);
  assert_double_eq(res->ave[2], 0.4985958686429482);

  assert_double_eq(res->sem[0], 0.005629016022953843);
  assert_double_eq(res->sem[1], 0.005625131381536439);
  assert_double_eq(res->sem[2], 0.005691438181690310);

  clear_avs_results(res);
  deinit_clargs(&args);
}

void test_multiple_fields()
{
  // Parsing last 2 fields, skipping 20%
  clargs args;
  args.n_fields = 2;
  args.skip = 20;
  // Different parallelism mode tested in parsing
  args.mode = DASC_PARALLEL_MODE_THR;
  args.n_threads = 1;
  args.verbose = false;
  args.filename = "../resources/10.avs.dat";

  args.fields = malloc(2 * sizeof(size_t));
  args.fields[0] = 1;
  args.fields[1] = 2;

  avs_results *res = avs(&args);

  assert(res->rows == 3257);
  assert(res->kept == 2606);

  assert(res->cols == 2);

  assert(res->fields[0] == 1);
  assert(res->fields[1] == 2);

  assert_double_eq(res->ave[0], 0.4957831770435258);
  assert_double_eq(res->ave[1], 0.4985958686429482);

  assert_double_eq(res->sem[0], 0.005625131381536439);
  assert_double_eq(res->sem[1], 0.005691438181690310);

  clear_avs_results(res);
  deinit_clargs(&args);
}

void test_field_skip()
{
  // Parsing boundary fields, skipping 20%
  clargs args;
  args.n_fields = 2;
  args.skip = 20;
  // Different parallelism mode tested in parsing
  args.mode = DASC_PARALLEL_MODE_THR;
  args.n_threads = 1;
  args.verbose = false;
  args.filename = "../resources/10.avs.dat";

  args.fields = malloc(2 * sizeof(size_t));
  args.fields[0] = 0;
  args.fields[1] = 2;

  avs_results *res = avs(&args);

  assert(res->rows == 3257);
  assert(res->kept == 2606);

  assert(res->cols == 2);

  assert(res->fields[0] == 0);
  assert(res->fields[1] == 2);

  assert_double_eq(res->ave[0], 0.5151493365490240);
  assert_double_eq(res->ave[1], 0.4985958686429482);

  assert_double_eq(res->sem[0], 0.005629016022953843);
  assert_double_eq(res->sem[1], 0.005691438181690310);

  clear_avs_results(res);
  deinit_clargs(&args);
}

void test_single_field()
{
  // Parsing middle field, skipping 20%
  clargs args;
  args.n_fields = 1;
  args.skip = 20;
  // Different parallelism mode tested in parsing
  args.mode = DASC_PARALLEL_MODE_THR;
  args.n_threads = 1;
  args.verbose = false;
  args.filename = "../resources/10.avs.dat";

  args.fields = malloc(1 * sizeof(size_t));
  args.fields[0] = 1;

  avs_results *res = avs(&args);

  assert(res->rows == 3257);
  assert(res->kept == 2606);

  assert(res->cols == 1);

  assert(res->fields[0] == 1);

  assert_double_eq(res->ave[0], 0.4957831770435258);

  assert_double_eq(res->sem[0], 0.005625131381536439);

  clear_avs_results(res);
  deinit_clargs(&args);
}

int main()
{
  open_test();

  printf("  Testing simple averaging...\n");
  test_simple();

  printf("  Testing multiple-field averaging...\n");
  test_multiple_fields();

  printf("  Testing field skip...\n");
  test_field_skip();

  printf("  Testing single field...\n");
  test_single_field();

  close_test();
}
