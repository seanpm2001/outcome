/* Type sugar for success and failure
(C) 2017-2019 Niall Douglas <http://www.nedproductions.biz/> (59 commits)
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

#ifndef BOOST_OUTCOME_SUCCESS_FAILURE_HPP
#define BOOST_OUTCOME_SUCCESS_FAILURE_HPP

#include "config.hpp"

BOOST_OUTCOME_V2_NAMESPACE_BEGIN

/*! Type sugar for implicitly constructing a `basic_result<>` with a successful state.
*/
template <class T> struct success_type
{
  //! The type of the successful state.
  using value_type = T;

private:
  //! The value of the successful state.
  value_type _value;

public:
  /// \output_section Default, copy/move constructors and assignment
  //! Default constructor
  success_type() = default;
  //! Copy constructor
  success_type(const success_type &) = default;
  //! Move constructor
  success_type(success_type &&) = default;  // NOLINT
  //! Copy assignment
  success_type &operator=(const success_type &) = default;
  //! Move assignment
  success_type &operator=(success_type &&) = default;  // NOLINT
  //! Destructor
  ~success_type() = default;
  /*! Initialising constructor

  \requires That `U` is not `success_type`.
  */
  BOOST_OUTCOME_TEMPLATE(class U)
  BOOST_OUTCOME_TREQUIRES(BOOST_OUTCOME_TPRED(!std::is_same<success_type, std::decay_t<U>>::value))
  constexpr explicit success_type(U &&v)
      : _value(static_cast<U &&>(v))
  {
  }

  /// \output_section Observers
  /*! Access value.
  \returns Reference to the held `value_type` according to overload.
  \group success_type_value
  */
  constexpr value_type &value() & { return _value; }
  /// \group success_type_value
  constexpr const value_type &value() const & { return _value; }
  /// \group success_type_value
  constexpr value_type &&value() && { return static_cast<value_type &&>(_value); }
  /// \group success_type_value
  constexpr const value_type &&value() const && { return static_cast<value_type &&>(_value); }
};
/*! Type sugar for implicitly constructing a `basic_result<>` with a successful state.
*/
template <> struct success_type<void>
{
  //! The type of the successful state.
  using value_type = void;
};
/*! Returns type sugar for implicitly constructing a `basic_result<T>` with a successful state,
default constructing `T` if necessary.
*/
inline constexpr success_type<void> success() noexcept
{
  return success_type<void>{};
}
/*! Returns type sugar for implicitly constructing a `basic_result<T>` with a successful state.
\effects Copies or moves the successful state supplied into the returned type sugar.
*/
template <class T> inline constexpr success_type<std::decay_t<T>> success(T &&v)
{
  return success_type<std::decay_t<T>>{static_cast<T &&>(v)};
}

/*! Type sugar for implicitly constructing a `basic_result<>` with a failure state of error code and exception.
*/
template <class EC, class E = void> struct failure_type
{
  //! The type of the error code
  using error_type = EC;
  //! The type of the exception
  using exception_type = E;

private:
  bool _have_error, _have_exception;
  //! The error code
  error_type _error;
  //! The exception
  exception_type _exception;

  struct error_init_tag
  {
  };
  struct exception_init_tag
  {
  };

public:
  /// \output_section Default, copy/move constructors and assignment
  //! Default constructor
  failure_type() = default;
  //! Copy constructor
  failure_type(const failure_type &) = default;
  //! Move constructor
  failure_type(failure_type &&) = default;  // NOLINT
  //! Copy assignment
  failure_type &operator=(const failure_type &) = default;
  //! Move assignment
  failure_type &operator=(failure_type &&) = default;  // NOLINT
  //! Destructor
  ~failure_type() = default;
  //! Initialising constructor
  template <class U, class V>
  constexpr explicit failure_type(U &&u, V &&v)
      : _have_error(true)
      , _have_exception(true)
      , _error(static_cast<U &&>(u))
      , _exception(static_cast<V &&>(v))
  {
  }
  /*! Initialising constructor for `error_type` only.
  */
  template <class U>
  constexpr explicit failure_type(in_place_type_t<error_type> /*unused*/, U &&u, error_init_tag /*unused*/ = error_init_tag())
      : _have_error(true)
      , _have_exception(false)
      , _error(static_cast<U &&>(u))
      , _exception()
  {
  }
  /*! Initialising constructor for `exception_type` only.
  */
  template <class U>
  constexpr explicit failure_type(in_place_type_t<exception_type> /*unused*/, U &&u, exception_init_tag /*unused*/ = exception_init_tag())
      : _have_error(false)
      , _have_exception(true)
      , _error()
      , _exception(static_cast<U &&>(u))
  {
  }

  /// \output_section Observers
  //! True if has error
  constexpr bool has_error() const { return _have_error; }
  //! True if has exception
  constexpr bool has_exception() const { return _have_exception; }

  /*! Access error.
  \returns Reference to the held `error_type` according to overload.
  \group failure_type_error
  */
  constexpr error_type &error() & { return _error; }
  /// \group failure_type_error
  constexpr const error_type &error() const & { return _error; }
  /// \group failure_type_error
  constexpr error_type &&error() && { return static_cast<error_type &&>(_error); }
  /// \group failure_type_error
  constexpr const error_type &&error() const && { return static_cast<error_type &&>(_error); }

  /*! Access exception.
  \returns Reference to the held `exception_type` according to overload.
  \group failure_type_exception
  */
  constexpr exception_type &exception() & { return _exception; }
  /// \group failure_type_exception
  constexpr const exception_type &exception() const & { return _exception; }
  /// \group failure_type_exception
  constexpr exception_type &&exception() && { return static_cast<exception_type &&>(_exception); }
  /// \group failure_type_exception
  constexpr const exception_type &&exception() const && { return static_cast<exception_type &&>(_exception); }
};
/*! Type sugar for implicitly constructing a `basic_result<>` with a failure state of error code.
*/
template <class EC> struct failure_type<EC, void>
{
  //! The type of the error code
  using error_type = EC;
  //! The type of the exception
  using exception_type = void;

private:
  //! The error code
  error_type _error;

public:
  /// \output_section Default, copy/move constructors and assignment
  //! Default constructor
  failure_type() = default;
  //! Copy constructor
  failure_type(const failure_type &) = default;
  //! Move constructor
  failure_type(failure_type &&) = default;  // NOLINT
  //! Copy assignment
  failure_type &operator=(const failure_type &) = default;
  //! Move assignment
  failure_type &operator=(failure_type &&) = default;  // NOLINT
  //! Destructor
  ~failure_type() = default;
  /*! Initialising constructor

  \requires That `U` is not `failure_type`.
  */
  BOOST_OUTCOME_TEMPLATE(class U)
  BOOST_OUTCOME_TREQUIRES(BOOST_OUTCOME_TPRED(!std::is_same<failure_type, std::decay_t<U>>::value))
  constexpr explicit failure_type(U &&u)
      : _error(static_cast<U &&>(u))
  {
  }

  /// \output_section Observers
  /*! Access error.
  \returns Reference to the held `error_type` according to overload.
  \group failure_type_error2
  */
  constexpr error_type &error() & { return _error; }
  /// \group failure_type_error2
  constexpr const error_type &error() const & { return _error; }
  /// \group failure_type_error2
  constexpr error_type &&error() && { return static_cast<error_type &&>(_error); }
  /// \group failure_type_error2
  constexpr const error_type &&error() const && { return static_cast<error_type &&>(_error); }
};
/*! Type sugar for implicitly constructing a `basic_result<>` with a failure state of exception.
*/
template <class E> struct failure_type<void, E>
{
  //! The type of the error code
  using error_type = void;
  //! The type of the exception
  using exception_type = E;

private:
  //! The exception
  exception_type _exception;

public:
  /// \output_section Default, copy/move constructors and assignment
  //! Default constructor
  failure_type() = default;
  //! Copy constructor
  failure_type(const failure_type &) = default;
  //! Move constructor
  failure_type(failure_type &&) = default;  // NOLINT
  //! Copy assignment
  failure_type &operator=(const failure_type &) = default;
  //! Move assignment
  failure_type &operator=(failure_type &&) = default;  // NOLINT
  //! Destructor
  ~failure_type() = default;
  /*! Initialising constructor

  \requires That `V` is not `failure_type`.
  */
  BOOST_OUTCOME_TEMPLATE(class V)
  BOOST_OUTCOME_TREQUIRES(BOOST_OUTCOME_TPRED(!std::is_same<failure_type, std::decay_t<V>>::value))
  constexpr explicit failure_type(V &&v)
      : _exception(static_cast<V &&>(v))
  {
  }

  /// \output_section Observers
  /*! Access exception.
  \returns Reference to the held `exception_type` according to overload.
  \group failure_type_exception2
  */
  constexpr exception_type &exception() & { return _exception; }
  /// \group failure_type_exception2
  constexpr const exception_type &exception() const & { return _exception; }
  /// \group failure_type_exception2
  constexpr exception_type &&exception() && { return static_cast<exception_type &&>(_exception); }
  /// \group failure_type_exception2
  constexpr const exception_type &&exception() const && { return static_cast<exception_type &&>(_exception); }
};
/*! Returns type sugar for implicitly constructing a `basic_result<T>` with a failure state.
\effects Copies or moves the failure state supplied into the returned type sugar.
*/
template <class EC> inline constexpr failure_type<std::decay_t<EC>> failure(EC &&v)
{
  return failure_type<std::decay_t<EC>>{static_cast<EC &&>(v)};
}
/*! Returns type sugar for implicitly constructing a `basic_result<T>` with a failure state.
\effects Copies or moves the failure state supplied into the returned type sugar.
*/
template <class EC, class E> inline constexpr failure_type<std::decay_t<EC>, std::decay_t<E>> failure(EC &&v, E &&w)
{
  return failure_type<std::decay_t<EC>, std::decay_t<E>>{static_cast<EC &&>(v), static_cast<E &&>(w)};
}

namespace detail
{
  template <class T> struct is_success_type
  {
    static constexpr bool value = false;
  };
  template <class T> struct is_success_type<success_type<T>>
  {
    static constexpr bool value = true;
  };
  template <class T> struct is_failure_type
  {
    static constexpr bool value = false;
  };
  template <class EC, class E> struct is_failure_type<failure_type<EC, E>>
  {
    static constexpr bool value = true;
  };
}  // namespace detail

//! True if the type is a success type
template <class T> static constexpr bool is_success_type = detail::is_success_type<std::decay_t<T>>::value;

//! True if the type is a failure type
template <class T> static constexpr bool is_failure_type = detail::is_failure_type<std::decay_t<T>>::value;

BOOST_OUTCOME_V2_NAMESPACE_END

#endif
