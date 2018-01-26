## What is `emock`?

- `emock` is a generic easy-to-use C++ Mock Framework.

## Why use `emock`?

- **[Easy to Use]** only one MACRO, without extra studies.
- **[No Dependencies]** unless STL and std C libraries.
- **[Cross Platform]** support popular OS both x86 & x64.
- **[Fully Support]** support all kinds of functions.
- **[No Intrusions]** no need to modify any source code.

## Feature sheet

### some of the conclusion below may be not exactly, contact me to fix if there were mistakes

<table>
   <tr>
      <td>Library</td>
      <td colspan="2">platform</td>
      <td colspan="3">member function</td>
      <td colspan="3">normal function</td>
      <td>misc</td>
   </tr>
   <tr>
      <td></td>
      <td>Linux</td>
      <td>Windows</td>
      <td>virtual(IoC-less)</td>
      <td>normal</td>
      <td>static</td>
      <td>global</td>
      <td>variadic</td>
      <td>template</td>
      <td>intrusion-free</td>
   </tr>
   <tr>
      <td><a href="https://github.com/ez8-co/emock">emock</a></td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:(:heavy_check_mark:)</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
   </tr>
   <tr>
      <td><a href="https://github.com/cpputest/cpputest">CppUMock</a></td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:(:x:<sup>[0]</sup>)</td>
      <td>:x:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:grey_exclamation:<sup>[0]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/sinojelly/mockcpp">mockcpp</a></td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:(:x:<sup>[1]</sup>)</td>
      <td>:x:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:x:</td>
      <td>:heavy_check_mark:</td>
      <td>:grey_exclamation:<sup>[1]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/google/googletest/tree/master/googlemock">googlemock</a></td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:(:x:<sup>[2]</sup>)</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:grey_exclamation:<sup>[2]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/tpounds/mockitopp">mockitopp</a></td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:(:x:<sup>[1]</sup>)</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:grey_exclamation:<sup>[1]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/hjagodzinski/C-Mock">C-Mock</a></td>
      <td>:heavy_check_mark:</td>
      <td>:x:</td>
      <td>:heavy_check_mark:(:x:<sup>[1]</sup>)</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:x:</td>
      <td>:x:</td>
      <td>:grey_exclamation:<sup>[1]</sup></td>
   </tr>
   <tr>
      <td><a href="https://github.com/gzc9047/CppFreeMock">CppFreeMock</a></td>
      <td>:heavy_check_mark:</td>
      <td>:x:</td>
      <td>:heavy_check_mark:(:x:<sup>[1]</sup>)</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>:grey_exclamation:<sup>[1]</sup></td>
   </tr>
</table>

- NOTES:
  - [0]: need IoC setter and override virtual functions of base class
  - [1]: need declarartion of interface(with pure virtual funtions), not support hybrid class (virtual & normal mem_fun at same time)
  - [2]: need IoC setter(cannot test embedded object or reference) and declaration of mock interface contains mem_fun with same arg list and return type that to be tested

### comparison of libraries those use api hook tech

<table>
   <tr>
      <td></td>
      <td>jump-safe</td>
      <td>comment</td>
   </tr>
   <tr>
      <td><a href="https://github.com/ez8-co/emock">emock</a></td>
      <td>:heavy_check_mark:</td>
      <td>use trampoline</td>
   </tr>
   <tr>
      <td><a href="https://github.com/sinojelly/mockcpp">mockcpp</a></td>
      <td>:x:</td>
      <td>long jump only</td>
   </tr>
   <tr>
      <td><a href="https://github.com/gzc9047/CppFreeMock">CppFreeMock</a></td>
      <td>:x:</td>
      <td>long jump only</td>
   </tr>
</table>

- `emock` should also work under UNIX, Android, MacOS and iOS, or maybe need minor adaptation.

## Recently supported

- all-in-one MOCKER macro (no-need to do IoC for virtual member functions)
- support mocking variadic function, e.g. `int test(int a, ...)`
- support mocking overloaded member functions under Windows
- reduce warning of getting address of virtual method under Linux
- trampoline that extend `this` pointer as first argument for member functions under Windows
- :clap: `near jump + trampoline` under x64 avoid unexcepted coverage by long jump

## Quick view

  ```cpp
      MOCKER(<function name>)
        .expects(<number of calls specified in the specification>)
        .invoked(<number of actual calls>)
        .before(<reference object type>, <mock specification ID>)
        .with(<with actual parameter value>)
        .after(<reference object type>, <mock specification ID>)
        .will(<the behavior specification with the actual behavior value>)
        .id(<ID of this specification>);
  ```

## Manual

- [Visit wiki to see how to use `emock`](https://github.com/ez8-co/emock/wiki)

## Thanks

- `emock` is evolved from mockcpp
- credit to author & contributor of mockcpp:
  - [godsme(darwin.yuan)](https://github.com/godsme)
  - [sinojelly](https://github.com/sinojelly)
- inital version is imported from [mockcpp@bitbucket](https://bitbucket.org/godsme/mockcpp)

## Acknowledged issues

- work with `valgrind`
  - add `--smc-check=all` to avoid invalidation of dynamically-generated code (API hook).
  - unable to mock `syscall` related functions (e.g. `gettimeofday`) yet.

## What's more

- Please feel free to use `emock`.
- Looking forward to your feeback.[create new issues](https://github.com/ez8-co/emock/issues/new).