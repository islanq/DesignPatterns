#include <iostream>
#include <vector>
#include <ctime>
using std::cout;

class Base {
  Base *next; // 1. "next" pointer in the base class

public:

  Base()
    : next{nullptr} {}

  auto SetNext(Base *n)->void {
    next = n;
  }

  auto Add(Base *n)->void {
    next ? next->Add(n) : next = n;
  }

  virtual auto Handle(int i)->void {
    next->Handle(i);
  } // 2. The "chain" method in the base class always delegates to the next obj

  virtual ~Base() = default;
};

class Handler1
  : public Base {
public:

  virtual auto Handle(int i)->void override
  {
    if (rand() % 3) {  // 3. Don't handle requests 3 times out of 4
      cout << "H1 passed " << i << "  ";
      Base::Handle(i); // 3. Delegate to the base class
    } else cout << "H1 handled " << i << "  ";
  }

  virtual ~Handler1() override = default;
};

class Handler2
  : public Base {
public:

  virtual auto Handle(int i)->void override
  {
    if (rand() % 3) {
      cout << "H2 passed " << i << "  ";
      Base::Handle(i);
    } else cout << "H2 handled " << i << "  ";
  }

  virtual ~Handler2() override = default;
};

class Handler3
  : public Base {
public:

  virtual auto Handle(int i)->void override
  {
    if (rand() % 3) {
      cout << "H3 passed " << i << "  ";
      Base::Handle(i);
    } else cout << "H3 handled " << i << "  ";
  }

  virtual ~Handler3() override = default;
};

auto main()->int
{
  srand(time(0));
  Handler1 root;
  Handler2 two;
  Handler3 thr;
  root.Add(&two);
  root.Add(&thr);
  thr.SetNext(&root);

  for (auto i = 1; i < 10; i++) {
    root.Handle(i);
    cout << std::endl;
  }

  getchar();
  return EXIT_SUCCESS;
}
