## What is mockcpp?

- mockcpp is a generic easy-to-use C++ Mock Framework.

## Why use mockcpp?

- **[Easy to use]** it's designed to be used without extra studies.
- **[No dependencies]** unless STL and std C libraries.
- **[Cross platform]** support x86 & x64 popular OSs.

## Recently supported

- all-in-one MOCKER macro (no-need to do IoC for virtual member functions)
- support mocking variadic arg function, e.g. `int test(int a, ...)`
- support mocking overloaded member functions under Windows
- reduce warning of getting address of virtual method under Linux
- **[Windows ONLY]** trampoline that extend `this` pointer as first argument for member functions
- :clap: `near jump + trampoline` under x64 avoid unexcepted coverage by long jump

## Acknowledged issues

### work with `valgrind`

- add `--smc-check=all` to avoid invalidation of dynamically-generated code (API hook).
- unable to mock `syscall` related functions using valgrind (e.g. `gettimeofday`) yet.

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

- [wiki](https://github.com/ez8-co/mockcpp/wiki)

## Thanks to

- Original author/contributor of mockcpp:
  - [godsme(darwin.yuan)](https://github.com/godsme)
  - [sinojelly](https://github.com/sinojelly)
- Import from [bitbucket](https://bitbucket.org/godsme/mockcpp)

## What's more

- Please feel free to use mockcpp.
- If your project is using mockcpp, you can show your project or company here.
- Looking forward to your feeback, if you have any suggestions or questions, please [create new issues](https://github.com/ez8-co/mockcpp/issues/new).