/* C interface for result
(C) 2017-2019 Niall Douglas <http://www.nedproductions.biz/> (59 commits)
File Created: Aug 2017


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef BOOST_OUTCOME_RESULT_H
#define BOOST_OUTCOME_RESULT_H

/// \file
/// \output_name result_c

//! A C struct representation of `std::error_code`.
struct cxx_error_code
{
  int code;
  void *category;
};

/*! Declares a C struct representation of `result<R, S>`.

\param R The unique postfix for `struct result_##R##_##S`.
\param RD The declaration for the `R` type.
\param S The unique postfix for
\param SD The declaration for the `S` type.
*/
#define CXX_DECLARE_RESULT(R, RD, S, SD)                                                                                                                                                                                                                                                                                       \
  struct result_##R##_##S                                                                                                                                                                                                                                                                                                      \
  {                                                                                                                                                                                                                                                                                                                            \
    RD value;                                                                                                                                                                                                                                                                                                                  \
    unsigned flags;                                                                                                                                                                                                                                                                                                            \
    SD error;                                                                                                                                                                                                                                                                                                                  \
  }
/*! Declares a C struct representation of `result<R, std::error_code>`.

\param R The unique postfix for `struct result_##R##_##S`.
\param RD The declaration for the `R` type.
*/
#define CXX_DECLARE_RESULT_EC(R, RD) CXX_DECLARE_RESULT(R, RD, errorcode, struct cxx_error_code)
//! A reference to a previously declared struct by `CXX_DECLARE_RESULT(R, RD, S, SD)`
#define CXX_RESULT(R, S) struct result_##R##_##S
//! A reference to a previously declared struct by `CXX_DECLARE_RESULT_EC(R, RD)`
#define CXX_RESULT_EC(R) struct result_##R##_errorcode
//! True if a result struct has a valid value
#define CXX_RESULT_HAS_VALUE(r) (((r).flags & 1U) == 1U)
//! True if a result struct has a valid error
#define CXX_RESULT_HAS_ERROR(r) (((r).flags & 2U) == 2U)
//! True if a result struct's `error` or `code` is an `errno` domain code suitable for setting `errno` with.
#define CXX_RESULT_ERROR_IS_ERRNO(r) (((r).flags & (1U << 4U)) == (1U << 4U))
//! C11 generic selecting a result struct's `error` or `code` integer member.
#define CXX_RESULT_ERROR(r) _Generic((r).error, struct cxx_error_code : ((struct cxx_error_code *) &(r).error)->code, default : (r).error)
//! Convenience macro setting `errno` to a result struct's `errno` compatible error if present, or `EAGAIN` if errored but incompatible.
#define CXX_RESULT_SET_ERRNO(r) (errno = CXX_RESULT_HAS_ERROR(r) ? (CXX_RESULT_ERROR_IS_ERRNO(r) ? CXX_RESULT_ERROR(r) : EAGAIN) : 0)

#endif
