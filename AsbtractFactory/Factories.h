#pragma once
#include "Shapes.h"
#include "Factory.h"


class SimpleShapeFactory
  : public Factory {
public:

  auto CreateCurvedInstance()->Shape * override {
    return new shapes::Circle;
  }

  auto CreateStraightInstance()->Shape * override {
    return new shapes::Square;
  }

  virtual ~SimpleShapeFactory() override = default;
};


class RobustShapeFactory
  : public Factory {
public:

  auto CreateCurvedInstance()->Shape * override {
    return new shapes::Ellipse;
  }

  auto CreateStraightInstance()->Shape * override {
    return new shapes::Rectangle;
  }

  virtual ~RobustShapeFactory() override = default;
};

#if defined(SIMPLE)
Factory *factory = new SimpleShapeFactory;
#elif defined(ROBUST)
Factory *factory = new RobustShapeFactory;
#else define DEFAULT
Factory *factory = new SimpleShapeFactory;
#endif // if defined(SIMPLE)
