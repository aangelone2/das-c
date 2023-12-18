#include "das-c/file_info.h"
#include "test.h"

int main()
{
  open_test();

  file_info info;
  size_t fields[2] = {1, 2};

  printf("  Testing missing file...\n");
  char *file1 = "../resources/missing.dat";
  assert(init_file_info(&info, file1, fields, 2) == 2);

  printf("  Testing empty file...\n");
  char *file2 = "../resources/no_lines.dat";
  assert(init_file_info(&info, file2, fields, 2) == 3);

  printf("  Testing file with only comments...\n");
  char *file3 = "../resources/only_comments.dat";
  assert(init_file_info(&info, file3, fields, 2) == 3);

  printf("  Testing file with no fields...\n");
  char *file4 = "../resources/no_fields.dat";
  assert(init_file_info(&info, file4, fields, 2) == 4);

  close_test();
}
