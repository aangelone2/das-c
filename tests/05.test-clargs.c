#include "das-c/clargs.h"
#include "test.h"
#include <string.h>

void test_no_options()
{
  clargs args;

  const int argc = 2;
  char *argv[3] = {"test", "file"};

  assert(!init_clargs(&args, argc, argv));
  assert(!args.nfields);
  assert(!args.fields);
  assert(!args.skip);
  assert(!args.verbose);
  assert(!strcmp(args.filename, "file"));

  deinit_clargs(&args);
}

void test_verbose()
{
  clargs args;

  const int argc = 3;
  char *argv[3] = {"test", "-v", "file"};

  assert(!init_clargs(&args, argc, argv));
  assert(!args.nfields);
  assert(!args.fields);
  assert(!args.skip);
  assert(args.verbose);
  assert(!strcmp(args.filename, "file"));

  deinit_clargs(&args);
}

void test_skip_verbose()
{
  clargs args;

  const int argc = 5;
  char *argv[] = {"test", "-s", "20", "-v", "file"};

  assert(!init_clargs(&args, argc, argv));
  assert(!args.nfields);
  assert(!args.fields);
  assert(args.skip == 20);
  assert(args.verbose);
  assert(!strcmp(args.filename, "file"));

  deinit_clargs(&args);
}

void test_fields()
{
  clargs args;

  const int argc = 5;
  char *argv[] = {"test", "-f", "1,2,3", "-v", "file2"};

  assert(!init_clargs(&args, argc, argv));
  assert(args.nfields == 3);
  assert(args.fields[0] == 1);
  assert(args.fields[1] == 2);
  assert(args.fields[2] == 3);
  assert(!args.skip);
  assert(args.verbose);
  assert(!strcmp(args.filename, "file2"));

  deinit_clargs(&args);
}

void test_missing_skip()
{
  clargs args;

  const int argc = 4;
  char *argv[4] = {"test", "-s", "-v", "file"};

  assert(init_clargs(&args, argc, argv) == 3);

  deinit_clargs(&args);
}

void test_invalid_option()
{
  clargs args;

  const int argc = 4;
  char *argv[4] = {"test", "-q", "-v", "file"};

  assert(init_clargs(&args, argc, argv) == 3);

  deinit_clargs(&args);
}

void test_missing_file()
{
  clargs args;

  const int argc = 2;
  char *argv[2] = {"test", "-v"};

  assert(init_clargs(&args, argc, argv) == 4);

  deinit_clargs(&args);
}

void test_invalid_fields()
{
  clargs args;

  const int argc = 5;

  char *argv1[] = {"test", "-f", "1,,3", "-v", "file2"};
  assert(!init_clargs(&args, argc, argv1));
  assert(args.nfields == 2);
  assert(args.fields[0] == 1);
  assert(args.fields[1] == 3);
  assert(!args.skip);
  assert(args.verbose);
  assert(!strcmp(args.filename, "file2"));

  char *argv2[] = {"test", "-f", "1,a,3", "-v", "file2"};
  assert(init_clargs(&args, argc, argv2) == 3);

  deinit_clargs(&args);
}

int main()
{
  open_test();

  printf("  Testing no options...\n");
  test_no_options();

  printf("  Testing verbose...\n");
  test_verbose();

  printf("  Testing skip + verbose...\n");
  test_skip_verbose();

  printf("  Testing `fields`...\n");
  test_fields();

  printf("  Testing missing value...\n");
  test_missing_skip();

  printf("  Testing invalid option...\n");
  test_invalid_option();

  printf("  Testing missing file...\n");
  test_missing_file();

  printf("  Testing invalid field values...\n");
  test_invalid_fields();

  close_test();
}
