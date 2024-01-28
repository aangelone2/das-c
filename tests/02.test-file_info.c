#include "das-c/common.h"
#include "test.h"

void test_empty_file()
{
  FILE *file = fopen("../resources/01.no_lines.dat", "r");
  assert(!count_fields_file(file));

  fclose(file);
}

void test_only_comment_file()
{
  FILE *file = fopen("../resources/02.only_comments.dat", "r");
  assert(!count_fields_file(file));

  fclose(file);
}

void testing_no_field_file()
{
  FILE *file = fopen("../resources/03.no_fields.dat", "r");
  assert(!count_fields_file(file));

  fclose(file);
}

void testing_regular_file()
{
  FILE *file = fopen("../resources/04.3_fields.dat", "r");
  assert(count_fields_file(file) == 3);

  fclose(file);
}

int main()
{
  open_test();

  printf("  Testing empty file...\n");
  test_empty_file();

  printf("  Testing file with only comments...\n");
  test_only_comment_file();

  printf("  Testing file with no fields...\n");
  testing_no_field_file();

  printf("  Testing regular file...\n");
  testing_regular_file();

  close_test();
}
