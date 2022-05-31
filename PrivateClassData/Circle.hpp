#pragma once

// .h file code:

#define _USE_MATH_DEFINES
#include <cmath>
#include "CircleData.hpp"

class Graphics;
class Point;
class Color;

class Circle {
  CircleData *circleData;

public:

  Circle(double radius,
         Color *color,
         Point *origin);
  const double& GetCircumference() const;
  const double& GetDiameter() const;
  static void   Draw(Graphics *graphics);
};
