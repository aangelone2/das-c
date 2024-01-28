#include "das-c/table.h"
#include "test.h"

mask *common_mask()
{
  mask *msk = init_mask(3);
  // Parsing all fields
  set_all(msk);

  return msk;
}

void test_too_many_fields()
{
  mask *msk = common_mask();
  FILE *file = fopen("../resources/05.too_many_fields.dat", "r");

  table *tab = init_table(msk->n_active);
  assert(parse(tab, file, msk) == 1);
  clear_table(tab);

  fclose(file);
  clear_mask(msk);
}

void test_invalid_field()
{
  mask *msk = common_mask();
  FILE *file = fopen("../resources/06.invalid_field.dat", "r");

  table *tab = init_table(msk->n_active);
  assert(parse(tab, file, msk) == 2);
  clear_table(tab);

  fclose(file);
  clear_mask(msk);
}

void test_too_few_fields()
{
  mask *msk = common_mask();
  FILE *file = fopen("../resources/07.too_few_fields.dat", "r");

  table *tab = init_table(msk->n_active);
  assert(parse(tab, file, msk) == 3);
  clear_table(tab);

  fclose(file);
  clear_mask(msk);
}

void test_valid_full()
{
  // Setting 4-4 field mask
  mask *msk = init_mask(4);
  set_all(msk);

  FILE *file = fopen("../resources/08.valid.dat", "r");

  table *tab = init_table(msk->n_active);
  assert(!parse(tab, file, msk));

  assert(tab->size == 4);
  for (size_t ic = 0; ic < tab->size; ++ic)
  {
    assert(tab->columns[ic]->size == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(
          tab->columns[ic]->data[ir], (double)(ic) + example_data[ir]
      );
  }

  clear_table(tab);

  fclose(file);
  clear_mask(msk);
}

void test_filtering()
{
  // Setting 2-4 field mask
  mask *msk = init_mask(4);
  set_field(msk, 1);
  set_field(msk, 2);

  FILE *file = fopen("../resources/08.valid.dat", "r");

  table *tab = init_table(msk->n_active);
  assert(!parse(tab, file, msk));

  assert(tab->size == 2);
  for (size_t ic = 0; ic < tab->size; ++ic)
  {
    assert(tab->columns[ic]->size == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(
          tab->columns[ic]->data[ir], (double)(ic) + 1.0 + example_data[ir]
      );
  }

  clear_table(tab);

  fclose(file);
  clear_mask(msk);
}

int main()
{
  open_test();

  printf("  Testing too many fields...\n");
  test_too_many_fields();

  printf("  Testing invalid field...\n");
  test_invalid_field();

  printf("  Testing too few fields...\n");
  test_too_few_fields();

  printf("  Testing valid file, all fields...\n");
  test_valid_full();

  printf("  Testing valid file, filtering...\n");
  test_filtering();

  close_test();
}
