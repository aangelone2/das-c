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
#include <string.h>

size_t count_fields(char *row, const char *sep)
{
  size_t fields = 0;

  char *tok = strtok(row, sep);
  while (tok)
  {
    ++fields;
    tok = strtok(NULL, sep);
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
  return count_fields(line, DASC_SEPARATORS);
}

size_t *parse_sizet_array(char *buffer, const size_t size)
{
  size_t *res = malloc(size * sizeof(size_t));
  check(res, "allocation failure in parse_sizet_array()");

  size_t f = 0;
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

    res[f] = val;
    ++f;
    tok = strtok(NULL, ",");
  }

  return res;
}
