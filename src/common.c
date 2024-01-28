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

#include "das-c/common.h"
#include <stdlib.h>
#include <string.h>

size_t count_fields(char *row)
{
  size_t fields = 0;

  char *tok = strtok(row, DASC_SEPARATORS);
  while (tok)
  {
    ++fields;
    tok = strtok(NULL, DASC_SEPARATORS);
  }

  return fields;
}

size_t count_fields_file(FILE *file)
{
  char line[DASC_MAX_LINE_LENGTH];
  do
  {
    if (!fgets(line, DASC_MAX_LINE_LENGTH, file))
    {
      rewind(file);
      return 0;
    }
  } while (is_comment(line));

  rewind(file);
  return count_fields(line);
}

size_t *parse_sizet_array(char *buffer, size_t *size)
{
  size_t *res = NULL;
  *size = 0;

  char *tok = strtok(buffer, ",");
  while (tok)
  {
    char *end;
    const size_t val = strtoul(tok, &end, 10);
    if (end == tok)
    {
      free(res);
      return NULL;
    }

    size_t *res2 = realloc(res, (*size + 1) * sizeof(size_t));
    check(res2, "reallocation failure in parse_sizet_array()");

    res = res2;
    res[*size] = val;

    ++(*size);
    tok = strtok(NULL, ",");
  }

  return res;
}
