#include "das-c/ave.h"
#include "test.h"
#include <stdlib.h>

void test_simple()
{
  // Parsing all 3 fields, skipping 20%
  clargs args;
  args.n_fields = 4;
  args.skip = 20;
  args.verbose = false;
  args.filename = "../resources/10.ave.dat";

  args.fields = NULL;

  ave_results *res = ave(&args);

  assert(res->rows == 11430);
  assert(res->kept == 8192);

  assert(res->cols == 4);
  assert(res->nsizes == 5);

  assert(res->fields[0] == 0);
  assert(res->fields[1] == 1);
  assert(res->fields[2] == 2);
  assert(res->fields[3] == 3);

  assert(res->nbins[0] == 1024);
  assert(res->nbins[1] == 512);
  assert(res->nbins[2] == 256);
  assert(res->nbins[3] == 128);
  assert(res->nbins[4] == 64);

  assert(res->bsizes[0] == 8);
  assert(res->bsizes[1] == 16);
  assert(res->bsizes[2] == 32);
  assert(res->bsizes[3] == 64);
  assert(res->bsizes[4] == 128);

  assert_double_eq(res->ave[0][0], -4.9939577524414064e-01);
  assert_double_eq(res->ave[1][0], -4.9939577524414064e-01);
  assert_double_eq(res->ave[2][0], -4.9939577524414064e-01);
  assert_double_eq(res->ave[3][0], -4.9939577524414064e-01);
  assert_double_eq(res->ave[4][0], -4.9939577524414064e-01);

  assert_double_eq(res->sem[0][0], 3.1401888194855531e-04);
  assert_double_eq(res->sem[1][0], 3.3808303695512639e-04);
  assert_double_eq(res->sem[2][0], 3.5030395417364921e-04);
  assert_double_eq(res->sem[3][0], 3.4232343321790963e-04);
  assert_double_eq(res->sem[4][0], 3.5305213819014896e-04);

  assert_double_eq(res->ave[0][1], -7.2499651749267571e+00);
  assert_double_eq(res->ave[1][1], -7.2499651749267571e+00);
  assert_double_eq(res->ave[2][1], -7.2499651749267588e+00);
  assert_double_eq(res->ave[3][1], -7.2499651749267580e+00);
  assert_double_eq(res->ave[4][1], -7.2499651749267588e+00);

  assert_double_eq(res->sem[0][1], 2.6789673488109868e-04);
  assert_double_eq(res->sem[1][1], 2.8983955387047803e-04);
  assert_double_eq(res->sem[2][1], 2.9752864857246638e-04);
  assert_double_eq(res->sem[3][1], 2.9772060642180461e-04);
  assert_double_eq(res->sem[4][1], 3.0613447645833156e-04);

  assert_double_eq(res->ave[0][2], -7.7493609515380859e+00);
  assert_double_eq(res->ave[1][2], -7.7493609515380859e+00);
  assert_double_eq(res->ave[2][2], -7.7493609515380868e+00);
  assert_double_eq(res->ave[3][2], -7.7493609515380859e+00);
  assert_double_eq(res->ave[4][2], -7.7493609515380859e+00);

  assert_double_eq(res->sem[0][2], 1.2273929145102075e-04);
  assert_double_eq(res->sem[1][2], 1.2761969492805497e-04);
  assert_double_eq(res->sem[2][2], 1.2973440370577806e-04);
  assert_double_eq(res->sem[3][2], 1.2165830747142403e-04);
  assert_double_eq(res->sem[4][2], 1.2166715931519173e-04);

  assert_double_eq(res->ave[0][3], -7.2499651749267571e+00);
  assert_double_eq(res->ave[1][3], -7.2499651749267571e+00);
  assert_double_eq(res->ave[2][3], -7.2499651749267588e+00);
  assert_double_eq(res->ave[3][3], -7.2499651749267580e+00);
  assert_double_eq(res->ave[4][3], -7.2499651749267588e+00);

  assert_double_eq(res->sem[0][3], 2.6789673488109868e-04);
  assert_double_eq(res->sem[1][3], 2.8983955387047803e-04);
  assert_double_eq(res->sem[2][3], 2.9752864857246638e-04);
  assert_double_eq(res->sem[3][3], 2.9772060642180461e-04);
  assert_double_eq(res->sem[4][3], 3.0613447645833156e-04);

  clear_ave_results(res);
  deinit_clargs(&args);
}

void test_multiple_fields()
{
  // Parsing last 2 fields, skipping 20%
  clargs args;
  args.n_fields = 2;
  args.skip = 20;
  args.verbose = false;
  args.filename = "../resources/10.ave.dat";

  args.fields = malloc(2 * sizeof(size_t));
  args.fields[0] = 2;
  args.fields[1] = 3;

  ave_results *res = ave(&args);

  assert(res->rows == 11430);
  assert(res->kept == 8192);

  assert(res->cols == 2);
  assert(res->nsizes == 5);

  assert(res->fields[0] == 2);
  assert(res->fields[1] == 3);

  assert(res->nbins[0] == 1024);
  assert(res->nbins[1] == 512);
  assert(res->nbins[2] == 256);
  assert(res->nbins[3] == 128);
  assert(res->nbins[4] == 64);

  assert(res->bsizes[0] == 8);
  assert(res->bsizes[1] == 16);
  assert(res->bsizes[2] == 32);
  assert(res->bsizes[3] == 64);
  assert(res->bsizes[4] == 128);

  assert_double_eq(res->ave[0][0], -7.7493609515380859e+00);
  assert_double_eq(res->ave[1][0], -7.7493609515380859e+00);
  assert_double_eq(res->ave[2][0], -7.7493609515380868e+00);
  assert_double_eq(res->ave[3][0], -7.7493609515380859e+00);
  assert_double_eq(res->ave[4][0], -7.7493609515380859e+00);

  assert_double_eq(res->sem[0][0], 1.2273929145102075e-04);
  assert_double_eq(res->sem[1][0], 1.2761969492805497e-04);
  assert_double_eq(res->sem[2][0], 1.2973440370577806e-04);
  assert_double_eq(res->sem[3][0], 1.2165830747142403e-04);
  assert_double_eq(res->sem[4][0], 1.2166715931519173e-04);

  assert_double_eq(res->ave[0][1], -7.2499651749267571e+00);
  assert_double_eq(res->ave[1][1], -7.2499651749267571e+00);
  assert_double_eq(res->ave[2][1], -7.2499651749267588e+00);
  assert_double_eq(res->ave[3][1], -7.2499651749267580e+00);
  assert_double_eq(res->ave[4][1], -7.2499651749267588e+00);

  assert_double_eq(res->sem[0][1], 2.6789673488109868e-04);
  assert_double_eq(res->sem[1][1], 2.8983955387047803e-04);
  assert_double_eq(res->sem[2][1], 2.9752864857246638e-04);
  assert_double_eq(res->sem[3][1], 2.9772060642180461e-04);
  assert_double_eq(res->sem[4][1], 3.0613447645833156e-04);

  clear_ave_results(res);
  deinit_clargs(&args);
}

void test_field_skip()
{
  // Parsing boundary fields, skipping 20%
  clargs args;
  args.n_fields = 2;
  args.skip = 20;
  args.verbose = false;
  args.filename = "../resources/10.ave.dat";

  args.fields = malloc(2 * sizeof(size_t));
  args.fields[0] = 0;
  args.fields[1] = 3;

  ave_results *res = ave(&args);

  assert(res->rows == 11430);
  assert(res->kept == 8192);

  assert(res->cols == 2);
  assert(res->nsizes == 5);

  assert(res->fields[0] == 0);
  assert(res->fields[1] == 3);

  assert(res->nbins[0] == 1024);
  assert(res->nbins[1] == 512);
  assert(res->nbins[2] == 256);
  assert(res->nbins[3] == 128);
  assert(res->nbins[4] == 64);

  assert(res->bsizes[0] == 8);
  assert(res->bsizes[1] == 16);
  assert(res->bsizes[2] == 32);
  assert(res->bsizes[3] == 64);
  assert(res->bsizes[4] == 128);

  assert_double_eq(res->ave[0][0], -4.9939577524414064e-01);
  assert_double_eq(res->ave[1][0], -4.9939577524414064e-01);
  assert_double_eq(res->ave[2][0], -4.9939577524414064e-01);
  assert_double_eq(res->ave[3][0], -4.9939577524414064e-01);
  assert_double_eq(res->ave[4][0], -4.9939577524414064e-01);

  assert_double_eq(res->sem[0][0], 3.1401888194855531e-04);
  assert_double_eq(res->sem[1][0], 3.3808303695512639e-04);
  assert_double_eq(res->sem[2][0], 3.5030395417364921e-04);
  assert_double_eq(res->sem[3][0], 3.4232343321790963e-04);
  assert_double_eq(res->sem[4][0], 3.5305213819014896e-04);

  assert_double_eq(res->ave[0][1], -7.2499651749267571e+00);
  assert_double_eq(res->ave[1][1], -7.2499651749267571e+00);
  assert_double_eq(res->ave[2][1], -7.2499651749267588e+00);
  assert_double_eq(res->ave[3][1], -7.2499651749267580e+00);
  assert_double_eq(res->ave[4][1], -7.2499651749267588e+00);

  assert_double_eq(res->sem[0][1], 2.6789673488109868e-04);
  assert_double_eq(res->sem[1][1], 2.8983955387047803e-04);
  assert_double_eq(res->sem[2][1], 2.9752864857246638e-04);
  assert_double_eq(res->sem[3][1], 2.9772060642180461e-04);
  assert_double_eq(res->sem[4][1], 3.0613447645833156e-04);

  clear_ave_results(res);
  deinit_clargs(&args);
}

void test_single_field()
{
  // Parsing middle field, skipping 20%
  clargs args;
  args.n_fields = 1;
  args.skip = 20;
  args.verbose = false;
  args.filename = "../resources/10.ave.dat";

  args.fields = malloc(1 * sizeof(size_t));
  args.fields[0] = 1;

  ave_results *res = ave(&args);

  assert(res->rows == 11430);
  assert(res->kept == 8192);

  assert(res->cols == 1);
  assert(res->nsizes == 5);

  assert(res->fields[0] == 1);

  assert(res->nbins[0] == 1024);
  assert(res->nbins[1] == 512);
  assert(res->nbins[2] == 256);
  assert(res->nbins[3] == 128);
  assert(res->nbins[4] == 64);

  assert(res->bsizes[0] == 8);
  assert(res->bsizes[1] == 16);
  assert(res->bsizes[2] == 32);
  assert(res->bsizes[3] == 64);
  assert(res->bsizes[4] == 128);

  assert_double_eq(res->ave[0][0], -7.2499651749267571e+00);
  assert_double_eq(res->ave[1][0], -7.2499651749267571e+00);
  assert_double_eq(res->ave[2][0], -7.2499651749267588e+00);
  assert_double_eq(res->ave[3][0], -7.2499651749267580e+00);
  assert_double_eq(res->ave[4][0], -7.2499651749267588e+00);

  assert_double_eq(res->sem[0][0], 2.6789673488109868e-04);
  assert_double_eq(res->sem[1][0], 2.8983955387047803e-04);
  assert_double_eq(res->sem[2][0], 2.9752864857246638e-04);
  assert_double_eq(res->sem[3][0], 2.9772060642180461e-04);
  assert_double_eq(res->sem[4][0], 3.0613447645833156e-04);

  clear_ave_results(res);
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
