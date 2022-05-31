#pragma once
#include <iostream>
#include <memory>

namespace visitor::after {
class Color {
public:

  virtual auto Accept(class Visitor *)->void = 0;
  virtual ~Color() = default;
};

class Red
  : public Color {
public:

  virtual auto Accept(Visitor *)->void override;
  static auto  Eye()->void {
    cout << "Red::eye" << endl;
  }

  virtual ~Red() override = default;
};

class Blu
  : public Color {
public:

  virtual auto Accept(Visitor *)->void override;
  static auto  Sky()->void {
    cout << "Blu::sky" << endl;
  }

  virtual ~Blu() override = default;
};

class Visitor {
public:

  virtual auto Visit(Red *)->void = 0;
  virtual auto Visit(Blu *)->void = 0;
  virtual ~Visitor()              = default;
};

class CountVisitor
  : public Visitor {
public:

  CountVisitor()
    : m_num_red{0}
    , m_num_blu{0}
  {}

  auto report_num() const->void
  {
    cout << "Reds " << m_num_red << " ,"
         << "Blus " << m_num_blu << endl;
  }

  virtual auto Visit(Red *)->void override {
    m_num_red++;
  }

  virtual auto Visit(Blu *)->void override {
    m_num_blu++;
  }

  ~CountVisitor() override = default;

private:

  int m_num_red, m_num_blu;
};

class CallVisitor
  : public Visitor {
public:

  virtual auto Visit(Red *r)->void override {
    r->Eye();
  }

  virtual auto Visit(Blu *b)->void override {
    b->Sky();
  }

  ~CallVisitor() override = default;
};

inline auto Red::Accept(Visitor *v)->void {
  v->Visit(this);
}

inline auto Blu::Accept(Visitor *v)->void {
  v->Visit(this);
}

inline auto Run()->void
{
  Color *color_set[] =
  {
    // ReSharper disable CppNonReclaimedResourceAcquisition
    new Red(),
    new Blu(),
    new Blu(),
    new Red(),
    new Red(),
    0
  };

  CountVisitor count_operation;
  CallVisitor  call_operation;

  for (auto color: color_set) {
    if (color) {
      color->Accept(&count_operation);
      color->Accept(&call_operation);
      delete color;
    }
  }
  count_operation.report_num();
}
}
