[English README](./README_en.md)

# EMOCK     [![license](https://img.shields.io/badge/license-Apache%202-brightgreen.svg?style=flat)](https://github.com/ez8-co/emock/blob/master/LICENSE)  [![Build Status](https://orca-zhang.semaphoreci.com/badges/emock/branches/master.svg?style=shields&key=e50d1d29-31e5-4977-950f-3eff3da05650)](https://orca-zhang.semaphoreci.com/projects/emock) [![Build status](https://ci.appveyor.com/api/projects/status/7a64ewar9yoifug5?svg=true)](https://ci.appveyor.com/project/orca-zhang/emock)

- EMOCK是基于mockcpp核心改进的下一代C/C++跨平台mock库
  - **【使用简单】** 学习成本低，仅一个宏
  - **【没有依赖】** 除了STL和系统库函数
  - **【跨平台】**   支持主流32/64位系统（\*nix、Windows、MacOS）
  - **【完全支持】** 支持mock所有类型的函数
  - **【非侵入设计】** 不需要调整任何待测代码

## 正在开发
  - :cow: 类似反射功能支持，无需声明即可mock（支持不可见的静态全局函数和动态库内部函数）
    - linux下改用dwarf实现
    - 支持C语言声明的函数
  - 支持mock带有异常约束的函数
  - 默认单元测试框架改用gtest
  - 缺失的caller匹配功能

## 最新支持

- 统一的`EMOCK`宏（测试虚函数，不再需要用户添加控制反转支持）
- 支持mock可变参数函数，例如：`int test(int a, ...)`
- 支持mock重载的成员函数（Windows系统）
- 解决老的获取成员函数方法会有警告问题（Linux系统）
- 使用蹦床使得this指针可见（Windows系统）
- :clap: 使用短跳+蹦床的方法解决x64下非期望覆盖较小函数的问题

## 特性矩阵

#### 下面是和一些主流mock库的对比（如有错误，不吝指正）

<table style="text-align: center">
   <tr>
      <td></td>
      <td colspan="3">平台</td>
      <td colspan="3">成员函数</td>
      <td colspan="3">普通函数</td>
      <td>杂项</td>
   </tr>
   <tr>
      <td>库</td>
      <td>Linux</td>
      <td>Win</td>
      <td>Mac</td>
      <td>虚函数</td>
      <td>普通</td>
      <td>静态</td>
      <td>全局</td>
      <td>变参</td>
      <td>模板</td>
      <td>无需修改</td>
   </tr>
   <tr>
      <td><a href="https://github.com/ez8-co/emock"><strong>EMOCK</strong></a></td>
      <td>:white_check_mark:</td>
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
      <td>:x:</td>
      <td>:white_check_mark:</td>
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
      <td>:x:</td>
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
      <td>:x:</td>
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
      <td>:x:</td>
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

- 注:
  - <sup>[0]</sup>: 需要IoC接口，派生并实现待测类的虚成员函数
  - <sup>[1]</sup>: 需要定义接口（只有纯虚成员函数），不支持混合类（同时包含虚成员函数和普通成员函数的类）
  - <sup>[2]</sup>: 需要IoC接口，需要声明含有待测虚成员函数的派生类（相同参数列表和返回类型） 
  - <sup>[0]</sup><sup>[1]</sup><sup>[2]</sup>: 无法测试类内嵌对象或者引用

#### 与使用API HOOK技术的库对比

<table style="text-align: center">
   <tr>
      <td>库</td>
      <td>跳转安全</td>
      <td>this指针可见[Windows]</td>
      <td>备注</td>
   </tr>
   <tr>
      <td><a href="https://github.com/ez8-co/emock"><strong>EMOCK</strong></a></td>
      <td>:white_check_mark:</td>
      <td>:white_check_mark:</td>
      <td>使用蹦床将远跳变为短跳</td>
   </tr>
   <tr>
      <td><a href="https://github.com/sinojelly/mockcpp">mockcpp</a></td>
      <td>:x:</td>
      <td>:x:</td>
      <td>x64下直接使用14字节的远跳</td>
   </tr>
   <tr>
      <td><a href="https://github.com/gzc9047/CppFreeMock">CppFreeMock</a></td>
      <td>:x:</td>
      <td>:x:</td>
      <td>x64下直接使用14字节的远跳</td>
   </tr>
</table>

- EMOCK理论上也支持UNIX, Android和iOS等\*nix系统，但可能需要少量改动

## 快速概览

#### 全局函数

  ```cpp
      // 待测函数
      int foobar(int x) {
          return x;
      }

      // 测试时，像下面这样就可以mock
      EMOCK(foobar)
          .stubs()
          .with(any()) // 约束匹配任意输入
          .will(returnValue(1)); // 调用时返回1

      // 调用会返回1
      ASSERT_EQ(foobar(0), 1);
  ```

#### 成员函数

  ```cpp
      // 待测成员函数
      class Foo
      {
      public:
          void bar1(int);
          virtual void bar2(double);
          static int bar3();
      };

      ////////////////////////////////////

      // 指定调用的mock函数
      void EMOCK_API mock_bar1(Foo* obj, int) {
          // ...
      }
      void EMOCK_API mock_bar2(Foo* obj, double) {
          // ...
      }

      // 测试时，像下面这样就可以mock
      EMOCK(&Foo::bar1)
          .stubs()
          .will(invoke(mock_bar1)); // 指定调用自定义的函数而不是指定返回值
      EMOCK(&Foo::bar2) // 虚成员函数并不特别
          .stubs()
          .will(invoke(mock_bar2));
      EMOCK(Foo::bar3) // 静态函数类似全局函数，不需要&
          .stubs()
          .will(returnValue(1));
  ```

#### 重载函数

  ```cpp
      // 待测重载函数
      int foobar(int x) {
          return x;
      }
      double foobar(double x) {
          return x;
      }

      // 重载函数，像下面这样就可以mock
      EMOCK((int (*)(int))foobar)
          .stubs()
          .will(returnValue(1));
      EMOCK(static_cast<double (*)(double)>(foobar))
          .stubs()
          .will(returnValue(1.0));

      // 待测重载成员函数
      class Foo
      {
      public:
          void bar(int);
          void bar(double);
      };

      // 重载的成员函数，像下面这样就可以mock
      EMOCK((void (Foo::*)(int))&Foo::bar)
          .expects(once()); // 只会调用一次
      EMOCK(static_cast<void (Foo::*)(double)>(&Foo::bar))
          .expects(never()); // 不会被调用
  ```

## 实验功能（根据函数签名式mock）

   ```cpp
      EMOCK("foo::bar")
          .stubs()
          .will(returnValue(1));
   ```

   - 设计参考 [MSDN - SymEnumSymbols](https://docs.microsoft.com/zh-cn/windows/win32/api/dbghelp/nf-dbghelp-symenumsymbols?redirectedfrom=MSDN)

   - 使用规范：`[[__cdecl|__stdcall|__thiscall]#]|[!] [{<return_type>}] [<namespace>::] [<class>::] <function> [(<argument_list>)] [@<library>]`

   - 支持通配符，`*` 代表任意数量个字符，`?` 代表单个字符
   
   - `@` 后面为库名，`#` 前为调用约定，其中用`!`是`__stdcall#`的缩写， `{int}`代表返回值类型为`int`

   - 例如：`!{int}*::foo::bar(double)@x??`代表返回值为`int`类型，调用约定为`__stdcall`的方法`foo::bar`，命名空间任意匹配，库名`x??`代表`x`开头，且为三个字符

## 使用手册

- [访问wiki学习如何使用EMOCK（建设中，可以参考网上mockcpp的教程）](https://github.com/ez8-co/emock/wiki)

## 衷心感谢

- EMOCK是基于mockcpp完善而来的
- 向mockcpp的作者和主要贡献者致敬:
  - [Darwin Yuan: darwin.yuan@gmail.com](https://github.com/godsme)
  - [Chen Guodong: sinojelly@gmail.com](https://github.com/sinojelly)
- 最原始版本从[mockcpp@bitbucket](https://bitbucket.org/godsme/mockcpp)导入

## 已知问题

- 和`valgrind`一起使用
  - 请添加`--smc-check=all`选项禁用缓存来防止动态修改机器码（API HOOK技术）部分失效导致不可预期的错误
  - 因为`valgrind`的特殊处理，暂时无法mock系统调用相关函数 （例如 `gettimeofday`）

## 写在最后

- 欢迎使用EMOCK，并期待您的反馈！[创建issues](https://github.com/ez8-co/emock/issues/new)

## 请我喝一杯咖啡

<table style="text-align: center">
   <tr>
      <td width="33%">支付宝</td>
      <td width="33%">微信</td>
      <td width="33%">PayPal</td>
   </tr>
   <tr>
      <td><a href="HTTPS://QR.ALIPAY.COM/FKX02095IUNLWM3PSPWD5A"><img src="https://img.shields.io/badge/donate-alipay-blue.svg" /></a></td>
      <td><a href="http://ez8.co/wxpay.jpg"><img src="https://img.shields.io/badge/donate-wechat_pay-brightgreen.svg" /></a></td>
      <td><a href="http://www.paypal.me/orcazhang"><img src="https://img.shields.io/badge/donate-paypal-yellow.svg" /></a></td>
   </tr>
   <tr>
      <td><a href="HTTPS://QR.ALIPAY.COM/FKX02095IUNLWM3PSPWD5A"><img src="http://ez8.co/alipay.jpg" alt="支付宝二维码" align=center /></a></td>
      <td><a href="http://ez8.co/wxpay.jpg"><img src="http://ez8.co/wxpay.jpg" alt="微信二维码" align=center /></td>
      <td><a href="http://www.paypal.me/orcazhang"><img src="http://ez8.co/paypal.png" alt="PayPal二维码" align=center /></a></td>
   </tr>
</table>
