#include "Circle.hpp"

Circle::Circle(double radius, Color *color, Point *origin) {
  this->circleData = new CircleData(radius, color, origin);
}

auto Circle::GetCircumference() const->const double&
{
  return this->circleData->GetRadius() * M_PI;
}

auto Circle::GetDiameter() const->const double&
{
  return this->circleData->GetRadius() * 2;
}

auto Circle::Draw(Graphics *graphics)->void { // ...
}
