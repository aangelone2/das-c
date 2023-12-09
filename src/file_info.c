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
#include "das-c/common.h"
#include <stdlib.h>

file_info *build_file_info(
    const char *filename, const size_t *fields, const size_t nfields
)
{
  file_info *finfo = (file_info *)malloc(sizeof(file_info));
  if (finfo == NULL)
    return NULL;

  // Opening file
  finfo->file = fopen(filename, "r");
  if (finfo->file == NULL)
    return NULL;

  // Extracting first non-commented line and getting number of fields
  char line[DASC_MAX_LINE_LENGTH];
  do
  {
    if (fgets(line, DASC_MAX_LINE_LENGTH, finfo->file) == NULL)
      return NULL;
  } while (!is_comment(line));

  const size_t cols = count_fields(line, DASC_SEPARATOR);
  if (cols == 0)
    return NULL;

  finfo->msk = build_mask(fields, nfields, cols);
  if (finfo->msk == NULL)
    return NULL;

  return finfo;
}

void free_file_info(file_info *finfo)
{
  free_mask(finfo->msk);
  fclose(finfo->file);
  free(finfo);
}
