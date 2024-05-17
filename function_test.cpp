
#include "Function.h"

#include <iostream>

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

  // copy
  Function<int(int, int)> g = f;
  res = g(7, 8);
  std::cout << "res = " << res << std::endl;

  // move
  Function<int(int, int)> h = std::move(g);
  res = h(9, 10);
  std::cout << "res = " << res << std::endl;

  // reset
  f.reset();
  if (!f) {
    std::cout << "f is empty" << std::endl;
  }

  return 0;
}
