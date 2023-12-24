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

#include "das-c/file_info.h"
#include "das-c/mask.h"
#include "das-c/table.h"
#include <stdio.h>
#include <string.h>

// Adds the contents of the fields of `line`, filtered by `msk`,
// to a new line in the columns of `tab`.
// Returns:
// - 0 if successful
// - 3 if too many fields (compared to `mask`)
// - 4 if too many active fields (compared to `tab`)
// - 5 if field cannot be converted to double
// - 6 if too few fields (compared to `mask`)
// - 7 if too few active fields (compared to `tab`)
int parse_line(table *tab, char *line, const mask *msk)
{
  size_t field = 0, active_field = 0;

  char *tok = strtok(line, DASC_SEPARATORS);
  while (tok)
  {
    ++field;
    if (field > msk->n_fields)
      return 3;

    if (msk->bits[field])
    {
      ++active_field;
      if (active_field > tab->size)
        return 4;

      char *end;
      const double buffer = strtod(tok, &end);
      if (end == tok)
        return 5;

      push_back(&tab->columns[active_field], buffer);
    }

    tok = strtok(NULL, DASC_SEPARATORS);
  }

  if (field != msk->n_fields)
    return 6;

  if (active_field != tab->size)
    return 7;

  return 0;
}

int init_table_parse(table *tab, file_info *info, const mask *msk)
{
  if (!tab)
    return 1;

  char line[DASC_MAX_LINE_LENGTH];

  if (init_table_empty(tab, msk->n_active))
    return 2;

  do
  {
    // Parse line, interrupt if EOF
    if (!fgets(line, DASC_MAX_LINE_LENGTH, info->file))
      break;

    ++info->rows;

    if (is_comment(line))
      continue;

    const int res = parse_line(tab, line, msk);
    if (res)
      return res;

    ++info->data_rows;
  } while (true);

  return 0;
}
