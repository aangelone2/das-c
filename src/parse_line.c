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
#include <string.h>

int parse_line(double *data, char *line, const mask *msk)
{
  size_t field = 0, active_field = 0;
  char *saveptr;

  char *tok = strtok_r(line, DASC_SEPARATORS, &saveptr);
  while (tok)
  {
    // Too many fields
    if (field >= msk->size)
      return EXIT_FAILURE;

    if (msk->bits[field])
    {
      char *end;
      const double buffer = strtod(tok, &end);

      // Invalid field found
      if (end == tok)
        return EXIT_FAILURE;

      data[active_field] = buffer;
      ++active_field;
    }

    tok = strtok_r(NULL, DASC_SEPARATORS, &saveptr);
    ++field;
  }

  // Too few fields
  if (field != msk->size)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
