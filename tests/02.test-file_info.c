#include "das-c/file_info.h"
#include "test.h"

int main()
{
  open_test();

  file_info info;

  printf("  Testing missing file...\n");
  char *file1 = "../resources/missing.dat";
  assert(init_file_info(&info, file1) == 2);

  printf("  Testing empty file...\n");
  char *file2 = "../resources/no_lines.dat";
  assert(init_file_info(&info, file2) == 3);

  printf("  Testing file with only comments...\n");
  char *file3 = "../resources/only_comments.dat";
  assert(init_file_info(&info, file3) == 3);

  printf("  Testing file with no fields...\n");
  char *file4 = "../resources/no_fields.dat";
  assert(init_file_info(&info, file4) == 4);

  printf("  Testing regular file...\n");
  char *file5 = "../resources/3_fields.dat";
  assert(!init_file_info(&info, file5));
  assert(info.cols == 3);
  assert(info.rows == 0);
  assert(info.data_rows == 0);

  deinit_file_info(&info);

  close_test();
}
