#pragma once
#include "Shape.h"
#include <iostream>

namespace shapes {
class Circle
  : public Shape {
public:

  virtual auto Draw()->void override {
    std::cout << "circle " << id_ << ": draw" << std::endl;
  }

  virtual ~Circle() override = default;
};


class Square
  : public Shape {
public:

  virtual auto Draw()->void override {
    std::cout << "square " << id_ << ": draw" << std::endl;
  }

  virtual ~Square() override = default;
};


class Ellipse
  : public Shape {
public:

  virtual auto Draw()->void override {
    std::cout << "ellipse " << id_ << ": draw" << std::endl;
  }

  virtual ~Ellipse() override = default;
};


class Rectangle
  : public Shape {
public:

  virtual auto Draw()->void override {
    std::cout << "rectangle " << id_ << ": draw" << std::endl;
  }

  virtual ~Rectangle() override;
};
}
