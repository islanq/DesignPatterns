#pragma once

class Color {};
class Point {};
class Graphics {};

class CircleData {
  double radius;
  Color *color;
  Point *origin;

public:

  CircleData(double radius,
             Color *color,
             Point *origin);
  auto GetRadius() const->const double&;
  auto GetColor() const->Color *;
  auto GetOrigin() const->Point *;

private:

  auto InitializeInstanceFields()->void;
};
