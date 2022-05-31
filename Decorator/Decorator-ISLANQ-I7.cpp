#include <iostream>
using std::cout;

// 1. "lowest common denominator"
class Widget {
public:
  virtual auto Draw()->void = 0;
  virtual ~Widget() = default;
};

class TextField
  : public Widget {
  // 3. "Core" class & "is a"
  int width, height;

public:

  TextField(int w, int h)
    : width{w}
    , height{h} {}

  virtual auto Draw()->void override {
    cout << "TextField: " << width << ", " << height << '\n';
  }

  virtual ~TextField() override = default;
};

// 2. 2nd level base class
class Decorator
  : public Widget // 4. "is a" relationship
{
  Widget *wid;    // 4. "has a" relationship

public:

  explicit Decorator(Widget *w)
    : wid{w} {}

  virtual auto Draw()->void override {
    wid->Draw();
  }

  virtual ~Decorator() override = default;

  // 5. Delegation
};

class BorderDecorator
  : public Decorator {
public:

  // 6. Optional embellishment
  explicit BorderDecorator(Widget *w)
    : Decorator{w} {}

  virtual auto Draw()->void override
  {
    // 7. Delegate to base class and add extra stuff
    Decorator::Draw();
    cout << "   BorderDecorator" << '\n';
  }

  virtual ~BorderDecorator() override = default;
};

class ScrollDecorator
  : public Decorator {
public:

  // 6. Optional embellishment
  explicit ScrollDecorator(Widget *w)
    : Decorator{w} {}

  virtual auto Draw()->void override
  {
    // 7. Delegate to base class and add extra stuff
    Decorator::Draw();
    cout << "   ScrollDecorator" << '\n';
  }

  virtual ~ScrollDecorator() override = default;
};

auto main()->int
{
  // 8. Client has the responsibility to compose desired configurations
  Widget *widget =
    new BorderDecorator(
      new BorderDecorator(
        new ScrollDecorator(
          new TextField(80, 24)
          )
        )
      );

  widget->Draw();
  delete widget;

  getchar();
  return EXIT_SUCCESS;
}
