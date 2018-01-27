- [简体中文](./README.md)

## What is EMOCK?

- EMOCK is a generic easy-to-use C++ Mock Library based on mockcpp.

- Work-in-process features
  - :cow: reflection-like support: declaration free, support mocking invisible static global function & functions inside dynamic libraries.
  - support mocking functions with `throw` specifications
  - provide best practice of `malloc` mocking

## Why use EMOCK?

- **[Easy to Use]** only one MACRO, without extra studies.
- **[No Dependencies]** unless STL and std C libraries.
- **[Cross Platform]** support popular OS (both x86 & x64).
- **[Fully Support]** support all kinds of functions.
- **[No Intrusions]** no need to modify any source code.

## Feature matrix

### comparision with popular mock libraries

- some of the conclusion below may be not exactly, contact me to correct if there were mistakes

<table style="text-align: center">
   <tr>
      <td></td>
      <td colspan="2">Platform</td>
      <td colspan="3">Member function</td>
      <td colspan="3">General function</td>
      <td>Misc</td>
   </tr>
   <tr>
      <td>Library</td>
      <td>Linux</td>
      <td>Windows</td>
      <td>Virtual</td>
      <td>Normal</td>
      <td>Static</td>
      <td>Global</td>
      <td>Variadic</td>
      <td>Template</td>
      <td>Intrusion-free</td>
   </tr>
   <tr>
      <td><a href="https://github.com/ez8-co/emock"><strong>emock</strong></a></td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
   </tr>
   <tr>
      <td><a href="https://github.com/cpputest/cpputest">CppUMock</a></td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:(:x:<sup>[0]</sup>)</td>
      <td>:x:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:x:<sup>[0]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/sinojelly/mockcpp">mockcpp</a></td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:x:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:x:</td>
      <td>:white_check_mark:</td>
      <td>:x:<sup>[1]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/google/googletest/tree/master/googlemock">googlemock</a></td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:<sup>[2]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/tpounds/mockitopp">mockitopp</a></td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:<sup>[1]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/hjagodzinski/C-Mock">C-Mock</a></td>
      <td>:white_check_mark:</td>
      <td>:x:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:<sup>[1]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/gzc9047/CppFreeMock">CppFreeMock</a></td>
      <td>:white_check_mark:</td>
      <td>:x:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>:x:<sup>[1]</sup></td>
   </tr>
</table>

- NOTES:
  - <sup>[0]</sup>: need IoC setter and override virtual functions of base class
  - <sup>[1]</sup>: need declarartion of interface(with pure virtual funtions), not support hybrid class (virtual & normal mem_fun at same time)
  - <sup>[2]</sup>: need IoC setter(cannot test embedded object or reference) and declaration of mock interface contains mem_fun with same arg list and return type that to be tested

### comparison with libraries those using api hook tech

<table style="text-align: center">
   <tr>
      <td>Library</td>
      <td>Jump-safe</td>
      <td>Visible of this pointer[Windows]</td>
      <td>Comment</td>
   </tr>
   <tr>
      <td><a href="https://github.com/ez8-co/emock"><strong>emock</strong></a></td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>Use trampoline (5 bytes)</td>
   </tr>
   <tr>
      <td><a href="https://github.com/sinojelly/mockcpp">mockcpp</a></td>
      <td>:x:</td>
      <td>:x:</td>
      <td>Long jump under x64 (14 bytes)</td>
   </tr>
   <tr>
      <td><a href="https://github.com/gzc9047/CppFreeMock">CppFreeMock</a></td>
      <td>:x:</td>
      <td>:x:</td>
      <td>Long jump under x64 (14 bytes)</td>
   </tr>
</table>

- EMOCK should also work under \*nix(UNIX, Android, MacOS and iOS), or maybe need minor adaptation.

## Recently supported

- all-in-one `MOCKER` macro (no-need to do IoC for virtual member functions)
- support mocking variadic function, e.g. `int test(int a, ...)`
- support mocking overloaded member functions under Windows
- reduce warning of getting address of virtual method under Linux
- trampoline that extend `this` pointer as first argument for member functions under Windows
- :clap: `near jump + trampoline` under x64 avoid unexcepted coverage by long jump

## Quick view

  ```cpp
      // function to be tested
      int target_func(int x);

      // how to mock
      MOCKER(target_func)
        .stubs()
        .with(any())
        .will(returnValue(1));
  ```

## Manual

- [Visit wiki to see how to use EMOCK](https://github.com/ez8-co/emock/wiki)

## Thanks

- EMOCK is evolved from mockcpp
- credit to author & contributor of mockcpp:
  - [Darwin Yuan: darwin.yuan@gmail.com](https://github.com/godsme)
  - [Chen Guodong: sinojelly@gmail.com](https://github.com/sinojelly)
- initial version is imported from [mockcpp@bitbucket](https://bitbucket.org/godsme/mockcpp)

## Acknowledged issues

- work with `valgrind`
  - add `--smc-check=all` to avoid invalidation of dynamically-generated code (API hook).
  - unable to mock `syscall` related functions (e.g. `gettimeofday`) yet.

## What's more

- Please feel free to use EMOCK.
- Looking forward to your feeback.[create new issues](https://github.com/ez8-co/emock/issues/new).