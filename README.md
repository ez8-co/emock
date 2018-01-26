## What is `emock`?

- `emock` is a generic easy-to-use C++ Mock Framework.

## Why use `emock`?

- **[Easy to Use]** only one MACRO, without extra studies.
- **[No Dependencies]** unless STL and std C libraries.
- **[Cross Platform]** support popular OS (both x86 & x64).
- **[Fully Support]** support all kinds of functions.
- **[No Intrusions]** no need to modify any source code.

## Feature sheet

### some of the conclusion below may be not exactly, contact me to correct if there were mistakes

<table>
   <tr>
      <td></td>
      <td colspan="2">Platform</td>
      <td colspan="3">Member function</td>
      <td colspan="3">General function</td>
      <td>misc</td>
   </tr>
   <tr>
      <td>Library</td>
      <td>Linux</td>
      <td>Windows</td>
      <td>Virtual(IoC-less)</td>
      <td>Normal</td>
      <td>Static</td>
      <td>Global</td>
      <td>Variadic</td>
      <td>Template</td>
      <td>Intrusion-free</td>
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

### comparison of libraries those using api hook tech

<table>
   <tr>
      <td>Library</td>
      <td>jump-safe</td>
      <td>visible this pointer[Windows]</td>
      <td>comment</td>
   </tr>
   <tr>
      <td><a href="https://github.com/ez8-co/emock">emock</a></td>
      <td>:heavy_check_mark:</td>
      <td>:heavy_check_mark:</td>
      <td>use trampoline</td>
   </tr>
   <tr>
      <td><a href="https://github.com/sinojelly/mockcpp">mockcpp</a></td>
      <td>:x:</td>
      <td>:x:</td>
      <td>long jump only</td>
   </tr>
   <tr>
      <td><a href="https://github.com/gzc9047/CppFreeMock">CppFreeMock</a></td>
      <td>:x:</td>
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
      MOCKER(function)
        .stubs() / defaults() / expects(never() | once() | exactly(3) | atLeast(3) | atMost(3) )
        [.before("some-mocker-id")]
        [.with( any() | eq(3) | neq(3) | gt(3) | lt(3) | spy(var_out) | check(check_func)
                | outBound(var_out) | outBoundP(var_out_addr, var_size) | mirror(var_in_addr, var_size)
                | smirror(string) | contains(string) | startWith(string) | endWith(string) )]
        [.after("some-mocker-id")]
        .will( returnValue(1) | repeat(1, 20) | returnObjectList(r1, r2)
                | invoke(func_stub) | ignoreReturnValue()
                | increase(from, to) | increase(from) | throws(exception) | die(3))
        [.then(returnValue(2))]
        [.id("some-mocker-id")]
  ```

## Manual

- [Visit wiki to see how to use `emock`](https://github.com/ez8-co/emock/wiki)

## Thanks

- `emock` is evolved from mockcpp
- credit to author & contributor of mockcpp:
  - [Darwin Yuan: darwin.yuan@gmail.com](https://github.com/godsme)
  - [Chen Guodong: sinojelly@gmail.com](https://github.com/sinojelly)
- inital version is imported from [mockcpp@bitbucket](https://bitbucket.org/godsme/mockcpp)

## Acknowledged issues

- work with `valgrind`
  - add `--smc-check=all` to avoid invalidation of dynamically-generated code (API hook).
  - unable to mock `syscall` related functions (e.g. `gettimeofday`) yet.

## What's more

- Please feel free to use `emock`.
- Looking forward to your feeback.[create new issues](https://github.com/ez8-co/emock/issues/new).