#include "CircleData.hpp"

CircleData::CircleData(double radius, Color *color, Point *origin)
{
  InitializeInstanceFields();
  this->radius = radius;
  this->color  = color;
  this->origin = origin;
}

auto CircleData::GetRadius() const->const double& {
  return this->radius;
}

auto CircleData::GetColor() const->Color * {
  return color;
}

auto CircleData::GetOrigin() const->Point * {
  return origin;
}

auto CircleData::InitializeInstanceFields()->void {
  radius = 0;
}
