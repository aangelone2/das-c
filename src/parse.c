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
#include "das-c/mask.h"
#include "das-c/table.h"
#include <stdlib.h>
#include <string.h>

// Counts the number of non-commented rows in the file.
// Resets the file on return.
size_t count_rows(FILE *file)
{
  size_t rows = 0;
  char line[DASC_MAX_LINE_LENGTH];

  while (fgets(line, DASC_MAX_LINE_LENGTH, file))
    if (!is_comment(line))
      ++rows;

  rewind(file);
  return rows;
}

// Writes the contents of the fields of `line`, filtered by `msk`,
// to the components of `data`.
// Returns:
// - 0 if successful
// - 1 if too many fields (compared to `msk`)
// - 2 if invalid fields found
// - 3 if too few fields (compared to `msk`)
int parse_line(double *data, char *line, const mask *msk)
{
  size_t field = 0, active_field = 0;

  char *tok = strtok(line, DASC_SEPARATORS);
  while (tok)
  {
    // Too many fields
    if (field >= msk->size)
      return 1;

    if (msk->bits[field])
    {
      char *end;
      const double buffer = strtod(tok, &end);

      // Invalid field found
      if (end == tok)
        return 2;

      data[active_field] = buffer;
      ++active_field;
    }

    tok = strtok(NULL, DASC_SEPARATORS);
    ++field;
  }

  // Too few fields
  if (field != msk->size)
    return 3;

  return 0;
}

int parse(table *tab, FILE *file, const mask *msk)
{
  const size_t rows = count_rows(file);
  init_table(tab, rows, msk->n_active);

  char line[DASC_MAX_LINE_LENGTH];

  size_t ir = 0;
  do
  {
    // Parse line, interrupt if EOF
    if (!fgets(line, DASC_MAX_LINE_LENGTH, file))
      break;

    if (is_comment(line))
      continue;

    // Failure in parse_line()
    const int res = parse_line(tab->data[ir], line, msk);
    if (res)
      return res;

    ++ir;
  } while (true);

  return 0;
}
