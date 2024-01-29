/* Copyright (c) 2023 Adriano Angelone
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * This file is part of das-c.
 *
 * This file may be used under the terms of the GNU General Public License
 * version 3.0 as published by the Free Software Foundation and appearing in
 * the file LICENSE included in the packaging of this file. Please review the
 * following information to ensure the GNU General Public License version 3.0
 * requirements will be met:
 * http://www.gnu.org/copyleft/gpl.html.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE. */

#include "das-c/clargs.h"
#include "das-c/common.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init_clargs(clargs *args, int argc, char *argv[])
{
  // Default values
  args->n_fields = 0;
  args->fields = NULL;
  args->skip = 0;
  args->verbose = false;

  char *options = "f:s:v";
  int opt;

  // Resetting, for multiple calls
  optind = 1;
  while ((opt = getopt(argc, argv, options)) != -1)
  {
    if (opt == 'f')
    {
      char *fields = malloc((strlen(optarg) + 1) * sizeof(char));
      strcpy(fields, optarg);

      args->fields = parse_sizet_array(fields, &args->n_fields);
      if (!args->fields)
      {
        free(fields);
        deinit_clargs(args);
        fprintf(stderr, "error :: invalid field value\n");
        return 1;
      }

      free(fields);
    }
    else if (opt == 's')
    {
      char *end;
      args->skip = strtoul(optarg, &end, 10);

      if (end == optarg)
      {
        deinit_clargs(args);
        fprintf(
            stderr, "error :: invalid value '%s' for option '-s'\n", optarg
        );
        return 2;
      }
    }
    else if (opt == 'v')
      args->verbose = true;
    else
    {
      if (optopt == 'f' || optopt == 's')
      {
        deinit_clargs(args);
        fprintf(
            stderr, "error :: option '-%c' requires an argument\n", optopt
        );
        return 3;
      }
      else
      {
        deinit_clargs(args);
        fprintf(stderr, "error :: unknown option '%c'\n", optopt);
        return 3;
      }
    }
  }

  if (optind != argc - 1)
  {
    deinit_clargs(args);
    fprintf(stderr, "error :: missing or multiple filenames\n");
    return 4;
  }

  args->filename = argv[optind];

  return 0;
}

void deinit_clargs(clargs *args) { free(args->fields); }
