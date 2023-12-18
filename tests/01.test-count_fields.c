#include "das-c/file_info.h"
#include "test.h"

int main()
{
  printf("  Testing regular field counting...\n");
  char test_1[] = "1.0 2.0 3.0 4.0";
  assert(count_fields(test_1) == 4);

  printf("  Testing field counting with trailing spaces...\n");
  char test_2[] = "1.0 2.0 3.0 4.0  ";
  assert(count_fields(test_2) == 4);

  printf("  Testing field counting with leading/trailing spaces...\n");
  char test_3[] = "   1.0 3.0 4.0  ";
  assert(count_fields(test_3) == 3);

  printf("  Testing field counting with spurious chars...\n");
  char test_4[] = "1.0,3.0 4.0  ";
  assert(count_fields(test_4) == 2);

  close_test();
}
