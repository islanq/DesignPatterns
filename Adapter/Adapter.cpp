#include <ostream>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

typedef int Coordinate;
typedef int Dimension;

// Desired interface
class Rectangle {
public:

  virtual ~Rectangle()      = default;
  virtual auto Draw()->void = 0;
};

// Legacy component
class LegacyRectangle {
public:

  LegacyRectangle(Coordinate x1, Coordinate y1,
                  Coordinate x2, Coordinate y2)
    : x1_{x1}
    , y1_{y1}
    , x2_{x2}
    , y2_{y2}
  {
    cout << "LegacyRectangle:  create.  ("
         << x1_ << "," << y1_ << ") => ("
         << x2_ << "," << y2_ << ")" << endl;
  }

  auto OldDraw() const->void
  {
    cout << "LegacyRectangle:  OldDraw.  ("
         << x1_ << "," << y1_
         << ") => ("
         << x2_ << "," << y2_
         << ")" << endl;
  }

private:

  Coordinate x1_,
             y1_,
             x2_,
             y2_;
};

// Adapter wrapper
class RectangleAdapter
  : public Rectangle,
    public LegacyRectangle {
public:

  RectangleAdapter(Coordinate x, Coordinate y,
                   Dimension w, Dimension h)
    : LegacyRectangle(x, y, x + w, y + h)
  {
    cout << "RectangleAdapter: create.  ("
         << x <<  ","     << y
         << "), width = " << w
         << ",  height = " << h << endl;
  }

  virtual auto Draw()->void override
  {
    cout << "RectangleAdapter: draw." << endl;
    OldDraw();
  }

  virtual ~RectangleAdapter() override = default;
};

auto main(int argc, char *argv[])->int
{
  auto rectangle = std::make_unique<RectangleAdapter>(120, 200, 60, 40);

  // Rectangle* r = new RectangleAdapter(120, 200, 60, 40);
  rectangle->Draw();

  getchar();
  return EXIT_SUCCESS;
}
