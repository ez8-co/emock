# mockcpp - Changelog

## Current Release

### [2017/12/30] mock++ 2.7 @ [orca.zhang](https://github.com/orca-zhang)

- Remove boost dependency:
  1. use equivalent way to fit `typeof` used scenarios.
  2. solved `BOOST_TYPE_OF` cannot recognize user-defined type at default problem.
- Support for mocking non-virtual method using `MOCKER`.
- Fix `TestNG++` generator's compatibility for python 3.

## Previous Releases

### [2011/10/02] mock++ 2.6 @ sinojelly

- Support both IA32 & IA64 platform (MSVC & GCC).
- Support using parameter directly while setting an `eq()` constraint.
- Changes: 
  1. reduce lib file size.
  2. fix compile error when compile for cppunit.
  3. add default mocker for mockable.

### [2011/03/26] mock++ 2.5 @ sinojelly

- Add mem_checker & fix mem leaks.
- Support 64-bit x86 arch.
- Support `__stdcall` functions for MSVC.
- Add `lt()`, `gt()`, `spy()` constraints.
- Working with various xUnit frameworks, including googleTest, CppUTest.

### [2010/03/16] mock++ 2.4 @ darwin.yuan

- Added support for mocking free functions & static class methods without using macro `MOCKABLE` (only for MSVC).
- Fully switched the building system to `CMake`.
- Changed some implementation to work with `TestNG++`.

### [2009/11/16] mock++ 2.3 @ darwin.yuan

- Automatic type inference of integer types (`long`/`unsigned long`, `int`/`unsigned int`, `short`/`unsigned short`, `char`/`unsigned char`) is supported.
- Using `CMake` as the building system, rather than putting MSVC project files into repository directly.

### [2009/09/02] mock++ 2.2 @ darwin.yuan

- MSVC 2008 is supported, except for the RTTI capabilities (which means `dynamic_cast` does not work correctly, basically, it always returns 0).
- Supported cygwin (tested under cygwin 1.5.25-15 with g++ 3.4.4).
- Advanced Guide (English Version).

### [2009/08/26] mock++ 2.1 @ darwin.yuan

- Down cast by `dynamic_cast` is supported.
- Able to specifing the life cycle of a mock object, and a mock object could be performed delete operation(not `::operator delete`) safely.
- Const reference type of return value of a mocked method is fully supported.
- `ignoreReturnValue()` is deprecated. Actually it's not allowed to use it any longer. Instead, you should always specify - the return behavior in a mock specification.
- Added some configure parameters to change the default settings.
- Some minor bugs were fixed.

### [2008/05/10] mock++ 2.0 @ darwin.yuan

- Define mock classes for interfaces is not required any longer (Only working with g++ so far).
- Refactored some concepts to make them more clear and easy to understand.
- Supporting mocking C function easily (g++ > 3 / MSVC > 6).
- Added `.then(stub)` after `.will(stub)` to make specifying complex invocation behavior much easier.
- Allow specifying more order-related constraints by using multiple `before()`/`after()`.
- Added some useful extensions (`repeat()`, `increase()`, `throws()`, `startWith()`, `endWith()`, `contains()`, etc.).
