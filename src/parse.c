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
#include "das-c/table.h"
#include <stdio.h>

int parse_line(table *tab, const char *line, const mask *msk)
{
  size_t valid_field = 0;
  for (size_t field = 0; field < msk->l; ++field)
  {
    if (msk->bits[field])
    {
      double buffer;
      if (sscanf(line, "%lf", &buffer) != 1)
        return 1;

      if (push_back(&tab->columns[valid_field], buffer))
        return 2;

      ++valid_field;
    }
    else
    {
      if (sscanf(line, "%*f") != 1)
        return 1;
    }
  }

  if (sscanf(line, "%*f") != EOF)
    return 3;

  return 0;
}

int init_table_parse(table *tab, file_info *info)
{
  char line[DASC_MAX_LINE_LENGTH];

  if (init_table_empty(tab, info->msk.n))
    return 1;

  do
  {
    // Parse line, interrupt if EOF
    if (!fgets(line, DASC_MAX_LINE_LENGTH, info->file))
      break;

    ++info->rows;

    if (is_comment(line))
      continue;

    if (parse_line(tab, line, &info->msk))
      return 2;

    ++info->data_rows;
  } while (true);

  return 0;
}
