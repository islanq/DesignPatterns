#pragma once
#include <iostream>

namespace visitor::before {
class Color {
public:

  virtual auto Count()->void = 0;
  virtual auto Call()->void  = 0;
  static auto  report_num()->void {
    cout << "Reds " << s_num_red << ", Blus " << s_num_blu <<
      '\n';
  }

  virtual ~Color() = default;

protected:

  static int s_num_red, s_num_blu;
};
int Color::s_num_red = 0;
int Color::s_num_blu = 0;

class Red
  : public Color {
public:

  virtual auto Count()->void override {
    ++s_num_red;
  }

  virtual auto Call()->void override {
    Eye();
  }

  static  auto Eye()->void {
    cout << "Red::eye\n";
  }

  ~Red()  override = default;
};

class Blu
  : public Color {
public:

  virtual auto Count()->void override {
    ++s_num_blu;
  }

  virtual auto Call()->void override {
    Sky();
  }

  static  auto Sky()->void {
    cout << "Blu::sky\n";
  }

  ~Blu()  override = default;
};

inline auto Run()->void
{
  Color *color_set[] =
  {
    // ReSharper disable CppNonReclaimedResourceAcquisition
    new Red, new Blu, new Blu, new Red, new Red, nullptr
  };

  for (auto color:color_set) {
    if (color) {
      color->Count();
      color->Call();
      delete color;
    }
  }
  Color::report_num();
}
}
