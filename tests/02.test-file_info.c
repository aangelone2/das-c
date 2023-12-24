#include "das-c/file_info.h"
#include "test.h"

void test_missing_file()
{
  file_info info;

  char *file1 = "../resources/missing.dat";
  assert(init_file_info(&info, file1) == 2);

  deinit_file_info(&info);
}

void test_empty_file()
{
  file_info info;

  char *file2 = "../resources/01.no_lines.dat";
  assert(init_file_info(&info, file2) == 3);

  deinit_file_info(&info);
}

void test_only_comment_file()
{
  file_info info;

  char *file3 = "../resources/02.only_comments.dat";
  assert(init_file_info(&info, file3) == 3);

  deinit_file_info(&info);
}

void testing_no_field_file()
{
  file_info info;

  char *file4 = "../resources/03.no_fields.dat";
  assert(init_file_info(&info, file4) == 4);

  deinit_file_info(&info);
}

void testing_regular_file()
{
  file_info info;

  char *file5 = "../resources/04.3_fields.dat";
  assert(!init_file_info(&info, file5));
  assert(info.cols == 3);
  assert(info.rows == 0);
  assert(info.data_rows == 0);

  deinit_file_info(&info);
}

int main()
{
  open_test();

  printf("  Testing missing file...\n");
  test_missing_file();

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
