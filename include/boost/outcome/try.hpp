/* Try operation macros
(C) 2017 Niall Douglas <http://www.nedproductions.biz/> (59 commits)
File Created: July 2017


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

#ifndef BOOST_OUTCOME_TRY_HPP
#define BOOST_OUTCOME_TRY_HPP

#include "success_failure.hpp"

BOOST_OUTCOME_V2_NAMESPACE_BEGIN

/*! Customisation point for changing what the `BOOST_OUTCOME_TRY` macros
do. This function defaults to returning `std::forward<T>(v).as_failure()`.
\effects Extracts any state apart from value into a `failure_type`.
\requires The input value to have a `.as_failure()` member function.
*/
template <class T> BOOST_OUTCOME_REQUIRES(requires(T &&v){{v.as_failure()}}) decltype(auto) try_operation_return_as(T &&v)
{
  return std::forward<T>(v).as_failure();
}

BOOST_OUTCOME_V2_NAMESPACE_END

#define BOOST_OUTCOME_TRY_GLUE2(x, y) x##y
#define BOOST_OUTCOME_TRY_GLUE(x, y) BOOST_OUTCOME_TRY_GLUE2(x, y)
#define BOOST_OUTCOME_TRY_UNIQUE_NAME BOOST_OUTCOME_TRY_GLUE(__t, __COUNTER__)

#define BOOST_OUTCOME_TRYV2(unique, m)                                                                                                                                                                                                                                                                                               \
  auto &&(unique) = (m);                                                                                                                                                                                                                                                                                                         \
  if(!(unique).has_value())                                                                                                                                                                                                                                                                                                      \
  return BOOST_OUTCOME_V2_NAMESPACE::try_operation_return_as(std::forward<decltype(unique)>(unique))
#define BOOST_OUTCOME_TRY2(unique, v, m)                                                                                                                                                                                                                                                                                             \
  BOOST_OUTCOME_TRYV2(unique, m);                                                                                                                                                                                                                                                                                                    \
  auto &&(v) = std::forward<decltype(unique)>(unique).value()

/*! If the outcome returned by expression *m* is not valued, propagate any
failure by immediately returning that failure state immediately
*/
#define BOOST_OUTCOME_TRYV(m) BOOST_OUTCOME_TRYV2(BOOST_OUTCOME_TRY_UNIQUE_NAME, m)

#if defined(__GNUC__) || defined(__clang__)

/*! If the outcome returned by expression *m* is not valued, propagate any
failure by immediately returning that failure state immediately, else become the
unwrapped value as an expression. This makes `BOOST_OUTCOME_TRYX(expr)` an expression
which can be used exactly like the `try` operator in other languages.

\note This macro makes use of a proprietary extension in GCC and clang and is not
portable. The macro is not made available on unsupported compilers,
so you can test for its presence using `#ifdef BOOST_OUTCOME_TRYX`.
*/
#define BOOST_OUTCOME_TRYX(m)                                                                                                                                                                                                                                                                                                        \
  ({                                                                                                                                                                                                                                                                                                                           \
    auto &&res = (m);                                                                                                                                                                                                                                                                                                          \
    if(!res.has_value())                                                                                                                                                                                                                                                                                                       \
      return BOOST_OUTCOME_V2_NAMESPACE::try_operation_return_as(std::forward<decltype(res)>(res));                                                                                                                                                                                                                                  \
    std::forward<decltype(res)>(res).value();                                                                                                                                                                                                                                                                                  \
  \
})
#endif

/*! If the outcome returned by expression *m* is not valued, propagate any
failure by immediately returning that failure immediately, else set *v* to the unwrapped value.
*/
#define BOOST_OUTCOME_TRY(v, m) BOOST_OUTCOME_TRY2(BOOST_OUTCOME_TRY_UNIQUE_NAME, v, m)

#endif
