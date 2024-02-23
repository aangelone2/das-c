#include "das-c/ave.h"
#include "das-c/avs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void general_help()
{
  printf("\n");
  printf("positional arguments:\n");
  printf("  file                  file to analyze\n");
  printf("options:\n");
  printf("  -h, --help            show this help message and exit\n");
  printf("  -f FIELDS, --fields FIELDS\n");
  printf("                        comma-separated, 0-indexed fields to "
         "analyze (default = all)\n");
  printf("  -n THREADS            number of threads for parsing process "
         "(default = 1)\n");
  printf("  -o                    uses OpenMP threading (default = false)\n");
  printf("  -s SKIP, --skip SKIP  percentage (1-100) of rows to skip (default "
         "= 0)\n");
  printf("  -v, --verbose         verbose output\n");
}

// Should be called as `$ das [command] ...`
int main(int argc, char *argv[])
{
  clargs args;
  // Skipping `das`
  init_clargs(&args, argc - 1, &(argv[1]));

  if (!strcmp(argv[1], "ave"))
  {
    if (args.help)
    {
      printf("usage: das ave [-h] [-f FIELDS] [-n THREADS] [-o] [-s SKIP] "
             "[-v] file\n");
      printf("\n");
      printf("performs binsize scaling\n");

      general_help();
      goto cleanup;
    }

    ave_results *res = ave(&args);

    if (args.verbose)
      printf(
          "%s :: %zu/%zu rows :: %zu columns\n\n",
          args.filename,
          res->kept,
          res->rows,
          res->cols
      );

    for (size_t is = 0; is < res->nsizes; ++is)
    {
      printf("%zu %zu", res->nbins[is], res->bsizes[is]);
      for (size_t ic = 0; ic < res->cols; ++ic)
        printf(" %+.12e %.1e", res->ave[is][ic], res->sem[is][ic]);
      printf("\n");
    }

    clear_ave_results(res);
  }
  else if (!strcmp(argv[1], "avs"))
  {
    if (args.help)
    {
      printf("usage: das avs [-h] [-f FIELDS] [-n THREADS] [-o] [-s SKIP] "
             "[-v] file\n");
      printf("\n");
      printf("performs averages without rebinning\n");

      general_help();
      goto cleanup;
    }

    avs_results *res = avs(&args);

    if (args.verbose)
      printf(
          "%s :: %zu/%zu rows :: %zu columns\n\n",
          args.filename,
          res->kept,
          res->rows,
          res->cols
      );

    for (size_t ic = 0; ic < res->cols; ++ic)
      printf("%zu %+.12e %.1e\n", ic, res->ave[ic], res->sem[ic]);

    clear_avs_results(res);
  }
  else
  {
    fprintf(stderr, "error :: invalid subcommand name [ave, avs]\n");
    deinit_clargs(&args);
    return EXIT_FAILURE;
  }

cleanup:
  deinit_clargs(&args);
  return EXIT_SUCCESS;
}
