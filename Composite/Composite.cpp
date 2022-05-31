#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

// 2. Create an "interface" (lowest common denominator)
class Component {
public:

  virtual ~Component()          = default;
  virtual auto Traverse()->void = 0;
};


class Leaf
  : public Component {
  // 1. Scalar class   3. "isa" relationship
  int value;

public:

  explicit Leaf(int val)
    : value{val}
  {}

  virtual auto Traverse()->void  override {
    cout << value << ' ';
  }

  virtual ~Leaf() override = default;
};


class Composite
  : public Component {
  // 1. Vector class   3. "is a" relationship
  vector<Component *>children; // 4. "container" coupled to the interface

public:

  // 4. "container" class coupled to the interface
  auto Add(Component *ele)->void {
    children.push_back(ele);
  }

  virtual auto Traverse()->void override
  {
    // 5. Use polymorphism to delegate to children
    for (auto i = 0; i < children.size(); i++) children[i]->Traverse();
  }

  virtual ~Composite() override = default;
};

auto main()->int
{
  Composite containers[4];

  for (auto i = 0; i < 4; i++) {
    for (auto j = 0; j < 3; j++) {
      containers[i].Add(new Leaf(i * 3 + j));
    }
  }

  for (auto i = 1; i < 4; i++) {
    containers[0].Add(&(containers[i]));
  }

  for (auto i = 0; i < 4; i++) {
    containers[i].Traverse();
    cout << endl;
  }

  getchar();
  return EXIT_SUCCESS;
}
