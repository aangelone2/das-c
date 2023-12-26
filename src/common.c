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

int parse_sizet_array(char *buffer, size_t **array, size_t *size)
{
  size_t *tmp = NULL;
  *size = 0;

  char *tok = strtok(buffer, ",");
  while (tok)
  {
    char *end;
    const size_t val = strtoul(tok, &end, 10);
    if (end == tok)
      return 2;

    size_t *tmp2 = realloc(tmp, (*size + 1) * sizeof(size_t));
    if (!tmp2)
      return 1;

    tmp = tmp2;
    tmp[*size] = val;

    ++(*size);
    tok = strtok(NULL, ",");
  }

  *array = tmp;
  return 0;
}
