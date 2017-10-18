/* Policies for result and outcome
(C) 2017 Niall Douglas <http://www.nedproductions.biz/> (59 commits)
File Created: Oct 2017


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

#ifndef BOOST_OUTCOME_POLICY_DETAIL_COMMON_HPP
#define BOOST_OUTCOME_POLICY_DETAIL_COMMON_HPP

#include "../../config.hpp"

BOOST_OUTCOME_V2_NAMESPACE_EXPORT_BEGIN

namespace policy
{
  namespace detail
  {
    struct base
    {
    private:
      static void _ub()
      {
#if defined(__GNUC__) || defined(__clang__)
        __builtin_unreachable();
#endif
      }

    public:
      /*! Performs a narrow check of state, used in the assume_value() functions.
      \effects None.
      */
      template <class Impl> static constexpr void narrow_value_check(Impl *self) noexcept
      {
        if((self->_state._status & BOOST_OUTCOME_V2_NAMESPACE::detail::status_have_value) == 0)
        {
          _ub();
        }
      }
      /*! Performs a narrow check of state, used in the assume_error() functions
      \effects None.
      */
      template <class Impl> static constexpr void narrow_error_check(Impl *self) noexcept
      {
        if((self->_state._status & BOOST_OUTCOME_V2_NAMESPACE::detail::status_have_error) == 0)
        {
          _ub();
        }
      }
      /*! Performs a narrow check of state, used in the assume_payload() functions
      \effects None.
      */
      template <class Impl> static constexpr void narrow_payload_check(Impl *self) noexcept
      {
        if((self->_state._status & BOOST_OUTCOME_V2_NAMESPACE::detail::status_have_payload) == 0)
        {
          _ub();
        }
      }
      /*! Performs a narrow check of state, used in the assume_exception() functions
      \effects None.
      */
      template <class Impl> static constexpr void narrow_exception_check(Impl *self) noexcept
      {
        if((self->_state._status & BOOST_OUTCOME_V2_NAMESPACE::detail::status_have_exception) == 0)
        {
          _ub();
        }
      }
    };
  }  // namespace detail
}  // namespace policy

BOOST_OUTCOME_V2_NAMESPACE_END

#endif
