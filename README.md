# Function

## Description

实现一个仿std::function的类，支持绑定函数和调用函数, 支持绑定函数对象、函数指针、lambda表达式。


## Example

```cpp

#include <iostream>
#include "Function.h"

int foo(int a, int b) {
  std::cout << "foo(" << a << ", " << b << ")" << std::endl;
  return a + b;
}

int main() {
    using ccutil::Function;
  // function pointer
  Function<int(int, int)> f = foo;
  int res = f(1, 2);
  std::cout << "res = " << res << std::endl;

  // lambda
  f = [](int a, int b) {
    std::cout << "lambda(" << a << ", " << b << ")" << std::endl;
    return a * b;
  };
  res = f(3, 4);
  std::cout << "res = " << res << std::endl;

  // function object
  struct Bar {
    int operator()(int a, int b) {
      std::cout << "Bar::operator()(" << a << ", " << b << ")" << std::endl;
      return a - b;
    }
  };

  f = Bar();
  res = f(5, 6);
  std::cout << "res = " << res << std::endl;

    return 0;
}

```