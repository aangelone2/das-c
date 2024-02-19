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

/**
 * @file parse_info.h
 *
 * `parse_info` struct and related utilities, which hold the necessary
 * information to parse a file.
 */
#ifndef DASC_PARSE_INFO_H
#define DASC_PARSE_INFO_H

#include "das-c/clargs.h"
#include "das-c/mask.h"

//! Struct holding file and thread load information.
typedef struct
{
  //! Filename.
  char *filename;

  //! Total number of rows in the file.
  size_t rows;
  //! Mask specifying the fields to access.
  mask *msk;

  //! Thread number.
  size_t n_threads;
  //! Thread load (number of rows to parse) array.
  size_t *chunks;
  //! Thread file position array.
  long int *pos;
} parse_info;

//! Initializes `parse_info` from the passed CL arguments.
/*!
 * Exits on allocation failure.
 *
 * @param args CL arguments holding init information.
 *
 * @return Pointer to the allocated `parse_info`.
 */
parse_info *alloc_parse_info(const clargs *args);

//! Frees memory associated to a `parse_info` object.
/*!
 * @param msk The `parse_info` to clear.
 */
void free_parse_info(parse_info *info);

#endif
