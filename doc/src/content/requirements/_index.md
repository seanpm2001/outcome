+++
title = "Prerequisites"
weight = 2
+++

Outcome is a header-only C++ 14 library known to work well on the latest
point releases of these compiler-platform combinations or better:

- clang 4.0.1 (LLVM) [FreeBSD, Linux, OS X]
- GCC 6.5 [Linux]
- Visual Studio 2017.9 [Windows]
- XCode 9 [MacOS]

It is worth turning on C++ 17 if you can, as there are many usability and
performance improvements. If your compiler implements the Concepts TS, it
is worth turning support on. Support is automatically
detected and used.


Partially working compilers (this was last updated January 2019):

- clang 3.5 - 3.9 can compile varying degrees of the test suite, the
problem is lack of complete and unbuggy C++ 14 language support.
- GCC's 7 and 8 have internal compiler error bugs in their constexpr
implementation which tend to be triggered by using Outcome in constexpr.
If you don't use Outcome in constexpr, you won't see these problems.
GCC 6 also seems to be more reliable. clang and Visual Studio work
correctly, if you need an alternative. 
- Early editions of Visual Studio 2017 have many corner case problems.
The latest point release, VS2017.9, only has a few known problems,
and should be relatively unsurprising for most use cases.