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
#include <stdlib.h>
#include <string.h>

size_t count_fields(char *row)
{
  size_t fields = 0;

  char *tok = strtok(row, DASC_SEPARATOR);
  while (tok)
  {
    ++fields;
    tok = strtok(NULL, DASC_SEPARATOR);
  }

  return fields;
}

int init_file_info(
    file_info *info,
    const char *filename,
    const size_t *fields,
    const size_t nfields
)
{
  // Null pointer
  if (!info)
    return 1;

  // Opening file
  info->file = fopen(filename, "r");
  // Failed opening
  if (!info->file)
    return 2;

  // Extracting first non-commented line and getting number of fields
  char line[DASC_MAX_LINE_LENGTH];
  do
  {
    // Empty file
    if (!fgets(line, DASC_MAX_LINE_LENGTH, info->file))
    {
      fclose(info->file);
      return 3;
    }
  } while (is_comment(line));

  rewind(info->file);

  const size_t cols = count_fields(line);
  // No valid fields in 1st row
  if (cols == 0)
  {
    fclose(info->file);
    return 4;
  }

  // Failed mask init
  if (init_mask(&info->msk, fields, nfields, cols))
  {
    fclose(info->file);
    return 5;
  }

  info->rows = 0;
  info->data_rows = 0;

  return 0;
}

void deinit_file_info(file_info *info)
{
  deinit_mask(&info->msk);
  fclose(info->file);
}
