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

#ifndef DASC_VECTOR_H
#define DASC_VECTOR_H

#include <stddef.h>

//! Resizable 1D float array.
typedef struct vector
{
  //! Number of allocated components.
  size_t size;

  //! Data array.
  double *data;
} vector;

//! Allocates empty `vector`.
/*!
 * The internal data vector will be set to `NULL` (ready for application of
 * `push_back()` or `resize()`).
 *
 * Exits on allocation failure.
 *
 * @return Pointer to the allocated `vector`.
 */
vector *init_vector();

//! Adds new component at the back of `vector`.
/*!
 * Exits on reallocation failure.
 *
 * @param vec The `vector` to expand.
 * @param val The value to add.
 */
void push_back(vector *vec, const double val);

//! Resize internal data array in `vector`.
/*!
 * Exits on reallocation failure.
 *
 * @param vec The `vector` to resize.
 * @param size The new size.
 */
void resize(vector *vec, const size_t size);

//! Frees memory associated to a `vector` object.
/*!
 * @param vec The `vector` to clear.
 */
void clear_vector(vector *vec);

#endif
