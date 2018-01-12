## What is mockcpp?

- mockcpp is a generic easy-to-use C++ Mock Framework.

## Thanks to

- Original author/contributor:
  - [godsme(darwin.yuan)](https://github.com/godsme)
  - [sinojelly](https://github.com/sinojelly)
- Import from [bitbucket](https://bitbucket.org/godsme/mockcpp)

## Why use mockcpp?

- Easy to use: it's designed to be used without extra studies.
- No extra dependencies: unless STL and std c libraries.
- Cross platform: support popular OSs, and Linux & Windows tested.

## Work-In-Process

- all-in-one MOCKER macro (no-need to do IoC for virtual member functions)

## Acknowledged issues

### work with `valgrind`

- add `--smc-check=all` to avoid invalidation of dynamically-generated code (API hook).
- unable to mock `syscall` related functions (e.g. `gettimeofday`) yet.

### others

- unable to mock variadic arg function with ellipsis (known as `...`), e.g. `int test(int a, ...)`.

## Manual of mockcpp

### 1. Background

mockcpp is a C/C++ mocking framework. It's neither a reinvention of the wheel nor Yet Another C++ Mocking Framework.

Before we started developing mockcpp, the only framework we could find on the Internet was mockpp. And it's the only option when we were practicing agile. Though mockpp is an excellent framework, the long compilation time and obscure compilation error messages resulted from the use of over sophisticated template was playing a negative role in our TDD practice. In addition, some features we needed were missing in mockpp. Then we decided to develop a new framework after our failed attempt to extend it due to its complexity.

mockcpp tries to meet these goals:

- Using template as less as possible to promote compilation speed, reduce obscurity of error message.
- The error messages emitted from the framework should be easy to understand, complete to help developers identify the problems quickly.
- Mock objects are easy to create.
- Extensibility to meet unique needs.
- Ability to mock free function.
- mockcpp is largely inspired by mockpp, jmock.

### 2. Introcution

mockcpp currently supports following constraints/actions:

* Matching call count
  - `expects()`/`stubs()`
* Matching caller
  - `caller()`
* Expectation order
  - `before()`
* Matching arguments
  - `with()`
* Expectation order
  - `after()`
* Setting actions
  - `will()`/`then()`
* Assigning an identifier
  - `id()`
* Except for 
  - `expects()`/`stubs()`

other constraints/actions are optional and should appear in the order below:

```cpp
MOCK_METHOD(object, method)
	.expects(once())
	.before(anotherMock, "close")
	.with(eq(1), any(), neq(2.0))
	.after(anotherMock, "open")
	.will(returnValue(true))
	.then(throws(std::exception))
	.id("myMethod");
```

#### 2.1 Using Actions

##### Purpose

Actions play important roles in mocking framework and are the most fundamental value provided by mocking frameworks. Through actions, mocks act as stubs, yet in a better way.

##### Supported Actions

* Returning a value:
  - `returnValue(value)`
* Returning more than one values:
  - `returnObjectList(o1, o2, ...)`
* Throwing an exception:
  - `throws(exception)`
* Ignoring return value:
  - `ignoreReturnValue()`
* Delegating to a stub method:
  - `invoke(stubFucntion)`
* Returning a value repeatly:
  - `repeat(value, times)`
* Incrementing a value:
  - `increase(from, to)`/`increase(from)`

##### Usage

To specify actions, use `will(behavior)`/`then(behavior)`. `will()` must be called before `then()` and can be called only once whereas `then()` multiple times.

```cpp
MOCK_METHOD(mock, foo)
	.stubs()
	.will(returnValue(10))
	.then(repeat(20, 2))
	.then(throws(std::exception))
	.then(returnValue(5));
```

When using `will()`/`then()`, actions will take effect in the order specified. In case of the number of calls is greater than the number of actions, the last action will be used for any additional calls as long as the constraints are met. Given the mock above specification, for instance, the following assertions are true:

```cpp
ASSERT_EQ(10, mock->foo());
ASSERT_EQ(20, mock->foo());
ASSERT_EQ(20, mock->foo());
ASSERT_THROWS(mock->foo(), std::exception);
ASSERT_EQ(5, mock->foo());
ASSERT_EQ(5, mock->foo());
ASSERT_EQ(5, mock->foo());
```

`returnValue()` is used to set value to be returned when the mocked method is called. If it's the last action specified, the value will be returned on all method calls. Otherwise, that value will be used only once.

You might want to return different values for the same method call. To do this, use `returnObjectList()`. mockcpp will return each value specified in `returnObjectList()` in turn. If `returnObjectList()` is the last action, mockcpp will issue an error if the mocked method is called and the values have been used up. Otherwise, the action following it will take effect.

Currently the number of values supported by returnObjectList is limited. It might be a problem under some circumstance. To workaround this, use `then()` since it can be called any number of times.

To throw an exception, use `throws(exception)`.

When the method has return value, an action must be specified even the return value is uninterested.

##### Example

```cpp
// Interface on which AwkProcessor depends
struct ITextFileReader
{
	virtual void open(const char* name) = 0;
	virtual bool close() = 0;
	virtual String readLine() = 0;
	virtual ~ITextFile() {}
};

// Code under test
struct AwkProcessor
{
	AwkProcessor(ITextFileReader* fileReader);
	String process(const char* textFileName, String script); 
};

// Test case
void test_should_throw_exception_if_open_file_failed ()
{
	MockObject textFile;

	MOCK_METHOD(textFile, open)
		.stubs()
		.will(throwException(Exception( "File Not Exist" )));

	///////////////////////////////////////////////
	AwkProcessor awkProcessor(textFile);
	ASSERT_THROWS( awkProcessor.process("myFile.txt", "{print $2}"), Exception);
}
```

#### 2.2 Matching Arguments

##### Purpose

You can have multiple mock specification for the same method. When the mock method is called, mockcpp will find the mock specification whose argument matchers are all satisfied and execute the action specified (return a value, throw an exception, etc.). In this case argument matchers are actually acting as selectors instead of constraints.

mockcpp will fail the test case if it can't find a proper mock specification. In this case argument matchers act more like constraints.

For C/C++ supports output arguments(through reference/pointer), argument matchers are acting like stubs.

##### Matchers

Input Argument Matcher 
* Generic Comparison
	- `eq(value)`
	- `neq(value)`
* Memory Matchers
	- `mirror(object)`
	- `mirror(address, size)`
* String Matchers
	- `smirror(str)`
	- `startWith(str)`
	- `endWith(str)`
	- `contains(str)`
* Wildcard
	- `any()`

Output Argument Matcher
* Output through reference: `outBound(reference, constraint)`
* Output through pointer: `outBoundP(point, constraint)`

##### Usage

To specify arguments you are expecting, use `with(contraint1, contraint2, …)`, where the constraints should be in the same order as in the method prototype. You can also use `any()` to ignore a argument. Calls to `any()` following the last explict constraints can be omitted.

For `eq()` and `neq()`, an compilation error will occur if equality test is not supported by the given type. To fix this, Add this capability by overloading `==`.

`mirror()` is used to constrain the content of a memory block. size can be ignored if it's used in object content comparison.

Note that when comparing object content. the random padding bytes used to adjust object alignment can sometimes cause error. in C, you can use memset to set those bytes to 0. In C++, the same effect can be achieved by using `eq()` on object whose `==` operator is overloaded.

`startWith()`，`endWith()`, `contains()` are used to match a string. `startWith()` tests if a string starts with the specified prefix, `endWith()` tests if a string ends with the specified prefix. Now you can guess what `contains()` means.

`smirror()` is to test if a string equals to the specifed one. It's a case of `mirror()`. They only differ in that for `smirror()`, size can be calculated by mockcpp hence programmer is free from providing it. In addition, `smirror()` doesn't have the padding issue.

For output argument, `outBound()`/`outBoundP()` can be used to set output value and input constraint should be left unspecified. For inout argument, argument constraint can be specified in `outBound()`/`outBoundP()` or left unspecified if you don't care about the input value.

##### When to Use It

When the input value determines whether the implementation of the tested method is correct or not. i.e. No matter how the method implementation is refactored, the argument constraints are always valid or the implementation could be wrong once the constraints are removed.
When a method is called multiple times by the tested method and might return different values under different circumstances. (use `returnObjectList(…)` if the mocked method return value types)
When value is obtained through output argument

##### When to Avoid It

Argument value has nothing to do with the correctness of method implementation
Call to log or debug

#### 2.3 Cardinality

##### Purpose

Call count is important in many cases. In these cases, the number of calls reflect the correctness of the implementation. And the sole purpose of Cardinality is helping developer to do this type of validation.

##### Supported Constraints

The method is called exactly once:
- `once()`

The call is expected at least n times:
- `atLeast(n)`
- `atLeastOnce()`

The call is expected at most n times:
- `atMost(n)`
- `atMostOnce()`

The method will never be called:
- `never()`

##### Usage

To specify number of calls, use `expects(times)`, where times is the constraints, such as `once()`; Use `stubs()` if you do don't care about the number of calls.

##### When to Use It

If the method being called can modify the system state and the number of calls to it determines the correctness of the implementation. i.e. No matter how the tested method is refactored, the constraint of the number of calls to the mocked method is always true as long as the tested method is consuming some type of services through the mocked method.

##### When to Avoid It

The number of calls has nothing to do with the correctness of implementation
Calls to method which are irrelevant to the implementation, such debug, log
If the method being called is for query, then we'd better not to specify the precise number of calls. Use `atLeast()` instead to make sure it's called or simply ignore it

##### Example

```cpp
// Interface on which AwkProcessor depends 
struct ITextFileReader
{
    virtual void open(const char* name) = 0;
    virtual bool close() = 0;
    virtual String readLine() = 0;
    virtual ~ITextFile() {}
};
```

```cpp
// Code under test
struct AwkProcessor
{
    AwkProcessor(ITextFileReader* fileReader);
    String process(const char* textFileName, String script);
};
```

```cpp
// Test case
void test_should_be_able_to_process_a_text_file()
{
    MockObject textFile;
    String line1("1 A"); String line2("2 B"); String line3("3 C");
    char * fileName = "testFile";

    ///////////////////////////////////////////////
    MOCK_METHOD(textFile, open)
        .expects(atLeast(1))
        .with(endWith(fileName));

    MOCK_METHOD(textFile, close)
         .expects(atLeast(1))
          .will(ignoreReturnValue());

    MOCK_METHOD(textFile, readLine)
         .stubs()
          .will(returnObjectList(line1, line2, line3))
        .then(throws(EOFError));

    ///////////////////////////////////////////////
    AwkProcessor awkProcessor(textFile);
    String result = awkProcessor.process(fileName, "{print $2}");
    ASSERT_EQ("A\nB\nC\n", result);
}

```

#### 2.4 Expectation Order

##### Purpose

It shouldn't be the case very often. But there are times when you want to specify the order of messages sent to mocks to make sure that the interactions between the unit under test and mocks are correct.

##### Supported Orders

`before(id)`, `before(object, id)`
`after(id)`, `after(object, id)`

##### Related

`id(identifier)`

##### Usage

`before()`/`after()` can be used multiple times in mock specification:

```cpp
    MockObject mock;

    MOCK_METHOD(mock, foo)
        .stubs()
        .will(returnValue(10))
        .id("foo");

    MOCK_METHOD(mock, bar)
        .stubs()
        .will(returnValue(true))
        .id("bar");

    MOCK_METHOD(mock, fix)
        .stubs()
        .after("foo")
        .after("bar")
        .will(returnValue(true));
```

You can also use the overloaded version to specify a qualified id:

```cpp
    MockObject mock0;
    MockObject mock1;
    MockObject mock2;

    MOCK_METHOD(mock0, foo)
        .stubs()
        .will(returnValue(10))
        .id("foo");

    MOCK_METHOD(mock1, foo)
        .stubs()
        .will(returnValue(1))
        .id("foo");

    MOCK_METHOD(mock2, foo)
        .stubs()
        .after(mock0, "foo")
        .after(mock1, "foo")
        .will(returnValue(11));
```

##### When to Use It

It's a fast way to write fragile tests. Avoid using this when order doesn't matter to the implementation.

#### 2.5 Identifier

##### Purpose

In order to reference a mock specification in `before()`/`after()`, an id needs to be assigned to it.

##### Usage

Use `id(identifier)` where 'identifier' is a string.

##### When to Use It

Only in case of you wanting to specify expectation order `id()` should be used.

##### Example

```cpp
// Dependent interface
struct IUserValidator
{
    virtual bool validate(const User&) const = 0;
    virtual ~IUserValidator() {}
};
```

```cpp
// Code under test
struct SequenceUserValidator : public IUserValidator
{
    typedef std::list Validators;
    CompositeUserValidator(Validators*);
    bool validate(const User&) const;

private:
    Validators* validators;
};
```

```cpp
// Test case
void test_should_invoke_validators_in_order()
{
    MockObject validator0;
    MockObject validator1;
    MockObject validator2;

    ///////////////////////////////////////////////
    SequenceUserValidator::Validators validators;

    validators.push_back(validator0);
    validators.push_back(validator1);
    validators.push_back(validator2);

    ///////////////////////////////////////////////
    User user("darwin");

    ///////////////////////////////////////////////
    MOCK_METHOD(validator0, validate)
        .expects(atLeast(1))
        .before(validate1, "v")
        .with(eq(user))
        .will(returnValue(true));

    MOCK_METHOD(validator1, validate)
        .expects(atLeast(1))
        .with(eq(user))
        .will(returnValue(true))
        .id("v");

    MOCK_METHOD(validator2, validate)
        .expects(atLeast(1))
        .with(eq(user))
        .after(validate1, "v")
        .will(returnValue(true));

    ///////////////////////////////////////////////
    SequenceUserValidator validator(&validators);
    ASSERT_TRUE(validator.validate(user));
}
```

#### 2.6 Caller

##### Purpose

This feature is mainly used in C unit test/integration test. It can narrow the scope of mock specification for function which has more than one callers and can not be described by above selectors in a call flow.

##### Usage

Use `caller(function)` where 'function' is the name of the function in string form.

### 3. Troubleshooting

##### Purpose

When mock-related errors occur, the important goal of mockcpp is help programmers debug quickly.

mockcpp accomplishes this goal in a consistent and concise manner. The standard format of error messages is divided into two types:
1. Only the error message, in the form of text to inform the relevant error.
2. In addition to the error message, but also provides detailed information on the actual call of a method.

The error message is a text description, such as:

```expected invoking exactly 0 times, but it's actually invoked 1 times.```

The actual call of the detailed information is like a call specification, the basic format is:

```cpp
METHOD(<method name>)
	.expects(<number of calls specified in the specification>)
	.invoked(<number of actual calls>)
	.before(<reference object type>, <mock specification ID>)
	.with(<with actual parameter value>)
	.after(<reference object type>, <mock specification ID>)
	.will(<the behavior specification with the actual behavior value>)
	.id(<ID of this specification>)
```

The details of the actual call would be printed in according to the constraints listed by the user-defined mock specification.

##### Example:
```cpp
MOCK_METHOD(collector, startTestCase)
	.expects(exactly(0))
	.invoked(1)
	.before(testcpp::TestFixture, "setUp")
	.with(eq((testcpp::TestCaseInfoReader*)0x00304388))
	.id("startTestCase");
```

The user-defined mock specification corresponds to it in the test code:

```cpp
MOCK_METHOD(collector, startTestCase)
	.expects(exactly(0))
	.before(fixture, "setUp")
	.with(eq((TestCaseInfoReader*)testcase[0]))
	.id("startTestCase");
```

This detailed call information describes:

```
You expect the number of calls to be exact 0 (specified by `expects(once())`, but your actual number of calls is 1 (by `invoking(1)` to know the actual number of calls).
```

So, combined with the previous error message:

```expected invoking exactly 0 times, but it's actually invoked 1 times.```

You can know your mistake more accurately.

## What's more

- Please feel free to use mockcpp.
- If your project is using mockcpp, you can show your project or company here.
- Looking forward to your feeback, if you have any suggestions or questions, please [create new issues](https://github.com/ez8-co/mockcpp/issues/new).