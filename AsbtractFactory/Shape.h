#pragma once

class Shape {
public:

  Shape()
    : id_{total_++}
  {}

  virtual auto Draw()->void = 0;
  virtual ~Shape()          = default;

protected:

  int id_;
  static int total_;
};

int Shape::total_ = 0;
