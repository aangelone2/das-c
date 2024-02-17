#include "das-c/common.h"
#include "test.h"

void test_regular_field_counting()
{
  char test_1[] = "1.0 2.0 3.0 4.0";
  assert(count_fields(test_1, " ") == 4);
}

void test_field_counting_trailing_spaces()
{
  char test_2[] = "1.0 2.0 3.0 4.0  ";
  assert(count_fields(test_2, " ") == 4);
}

void test_field_counting_leading_trailing_spaces()
{
  char test_3[] = "   1.0 3.0 4.0  ";
  assert(count_fields(test_3, " ") == 3);
}

void test_field_counting_spurious_chars()
{
  char test_4[] = "1.0,3.0 4.0  ";
  assert(count_fields(test_4, " ") == 2);
}

void test_field_counting_only_separators()
{
  char test_5[] = "          ";
  assert(count_fields(test_5, " ") == 0);
}

int main()
{
  open_test();

  printf("  Testing regular field counting...\n");
  test_regular_field_counting();

  printf("  Testing field counting with trailing spaces...\n");
  test_field_counting_trailing_spaces();

  printf("  Testing field counting with leading/trailing spaces...\n");
  test_field_counting_leading_trailing_spaces();

  printf("  Testing field counting with spurious chars...\n");
  test_field_counting_spurious_chars();

  printf("  Testing field counting with only separators...\n");
  test_field_counting_only_separators();

  close_test();
}
