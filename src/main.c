#include "das-c/ave.h"
#include "das-c/avs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Should be called as `$ das [command] ...`
int main(int argc, char *argv[])
{
  clargs args;
  // Skipping `das`
  init_clargs(&args, argc - 1, &(argv[1]));

  if (!strcmp(argv[1], "ave"))
  {
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

  deinit_clargs(&args);
  return EXIT_SUCCESS;
}
