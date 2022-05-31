#include "Factories.h"
#include "Shape.h"
#include <iostream>

#define ROBUST

auto main()->int
{
  Shape *shapes[3];

  shapes[0] = factory->CreateCurvedInstance();   // shapes[0] = new Ellipse;
  shapes[1] = factory->CreateStraightInstance(); // shapes[1] = new Rectangle;
  shapes[2] = factory->CreateCurvedInstance();   // shapes[2] = new Ellipse;

  for (const auto shape : shapes) {
    shape->Draw();
  }

  getchar();
  return EXIT_SUCCESS;
}
