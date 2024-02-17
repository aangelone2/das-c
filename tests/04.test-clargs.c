#include "das-c/clargs.h"
#include "das-c/common.h"
#include "test.h"
#include <string.h>

char *prepare(char *buffer)
{
  char *res = malloc((strlen(buffer) + 1) * sizeof(char));
  strcpy(res, buffer);

  return res;
}

void test_parse_sizet_array()
{
  size_t size;
  size_t *arr;
  char *fields;

  // Regular parsing
  fields = prepare("1,2,3");
  arr = parse_sizet_array(fields, &size);
  free(fields);

  assert(size == 3);
  assert(arr[0] == 1);
  assert(arr[1] == 2);
  assert(arr[2] == 3);
  free(arr);

  // Single component
  fields = prepare("4");
  arr = parse_sizet_array(fields, &size);
  free(fields);

  assert(size == 1);
  assert(arr[0] == 4);
  free(arr);

  // Empty component
  fields = prepare("5,,6");
  arr = parse_sizet_array(fields, &size);
  free(fields);

  assert(size == 2);
  assert(arr[0] == 5);
  assert(arr[1] == 6);
  free(arr);

  // Trailing comma
  fields = prepare("7,");
  arr = parse_sizet_array(fields, &size);
  free(fields);

  assert(size == 1);
  assert(arr[0] == 7);
  free(arr);

  // Invalid component
  fields = prepare("8,a,9");
  arr = parse_sizet_array(fields, &size);
  free(fields);

  assert(!arr);
  free(arr);
}

void test_no_options()
{
  clargs args;

  const int argc = 2;
  char *argv[3] = {"test", "file"};

  assert(!init_clargs(&args, argc, argv));
  assert(!args.n_fields);
  assert(!args.fields);
  assert(!args.skip);
  assert(args.mode == DASC_PARALLEL_MODE_SER);
  assert(args.n_threads == 1);
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
  assert(!args.n_fields);
  assert(!args.fields);
  assert(!args.skip);
  assert(args.mode == DASC_PARALLEL_MODE_SER);
  assert(args.n_threads == 1);
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
  assert(!args.n_fields);
  assert(!args.fields);
  assert(args.skip == 20);
  assert(args.mode == DASC_PARALLEL_MODE_SER);
  assert(args.n_threads == 1);
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
  assert(args.n_fields == 3);
  assert(args.fields[0] == 1);
  assert(args.fields[1] == 2);
  assert(args.fields[2] == 3);
  assert(!args.skip);
  assert(args.mode == DASC_PARALLEL_MODE_SER);
  assert(args.n_threads == 1);
  assert(args.verbose);
  assert(!strcmp(args.filename, "file2"));

  deinit_clargs(&args);
}

void test_missing_skip()
{
  clargs args;

  const int argc = 4;
  char *argv[4] = {"test", "-s", "-v", "file"};

  assert(init_clargs(&args, argc, argv) == 2);

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
  assert(args.n_fields == 2);
  assert(args.fields[0] == 1);
  assert(args.fields[1] == 3);
  assert(!args.skip);
  assert(args.mode == DASC_PARALLEL_MODE_SER);
  assert(args.n_threads == 1);
  assert(args.verbose);
  assert(!strcmp(args.filename, "file2"));

  char *argv2[] = {"test", "-f", "1,a,3", "-v", "file2"};
  assert(init_clargs(&args, argc, argv2) == 1);

  deinit_clargs(&args);
}

void test_parallel_options()
{
  clargs args;

  const int argc = 5;

  char *argv1[] = {"test", "-n", "2", "-m", "c", "file"};
  assert(!init_clargs(&args, argc, argv1));
  assert(!args.n_fields);
  assert(!args.fields);
  assert(!args.skip);
  assert(args.mode == DASC_PARALLEL_MODE_CPU);
  assert(args.n_threads == 2);
  assert(!args.verbose);
  assert(!strcmp(args.filename, "file"));

  char *argv2[] = {"test", "-m", "q", "file2"};
  assert(init_clargs(&args, argc, argv2) == 2);

  deinit_clargs(&args);
}

int main()
{
  open_test();

  printf("  Testing field parsing...\n");
  test_parse_sizet_array();

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
