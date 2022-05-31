#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class Base {
  static auto A()->void {
    cout << "a  ";
  }

  static auto C()->void {
    cout << "c  ";
  }

  static auto E()->void {
    cout << "e  ";
  }

  // 2. Steps requiring peculiar implementations are "placeholders" in base
  // class
  virtual auto Ph1()->void = 0;
  virtual auto Ph2()->void = 0;

public:

  // 1. Standardize the skeleton of an algorithm in a base class "template
  // method"
  void execute()
  {
    A();
    Ph1();
    C();
    Ph2();
    E();
  }

  virtual ~Base() = default;
};

class One
  : public Base {
  // 3. Derived classes implement placeholder methods

  virtual auto Ph1()->void override {
    cout << "b  ";
  }

  virtual auto Ph2()->void override {
    cout << "d  ";
  }
};

class Two
  : public Base {
  virtual auto Ph1()->void override {
    cout << "2  ";
  }

  virtual auto Ph2()->void override {
    cout << "4  ";
  }
};

auto main()->int
{
  One one;
  Two two;

  Base *array[] { &one, &two };

  for (const auto i: array) {
    i->execute();
    cout << endl;
  }

  getchar();
  return EXIT_SUCCESS;
}
