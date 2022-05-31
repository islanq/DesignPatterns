#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

namespace visitor::primary {
// 1. Add an accept(Visitor) method to the "element" hierarchy
class Element {
public:

  virtual auto Accept(class Visitor& v)->void = 0;
  virtual ~Element() = default;
};

class This
  : public Element {
public:

  virtual auto Accept(Visitor& v)->void override;
  static auto  Thiss()->string {
    return "This";
  }

  virtual ~This() override = default;
};

class That
  : public Element {
public:

  virtual auto Accept(Visitor& v)->void override;
  static auto  Thatt()->string {
    return "That";
  }

  virtual ~That() override = default;
};

class TheOther
  : public Element {
public:

  virtual auto Accept(Visitor& v)->void override;
  static auto  TheOtherr()->string {
    return "TheOther";
  }

  virtual ~TheOther() override = default;
};

// 2. Create a "visitor" base class w/ a visit() method for every "element" type
class Visitor {
public:

  virtual auto visit(This *e)->void     = 0;
  virtual auto visit(That *e)->void     = 0;
  virtual auto visit(TheOther *e)->void = 0;
  virtual ~Visitor()                    = default;
};

inline auto This::Accept(Visitor& v)->void {
  v.visit(this);
}

inline auto That::Accept(Visitor& v)->void {
  v.visit(this);
}

inline auto TheOther::Accept(Visitor& v)->void {
  v.visit(this);
}

// 3. Create a "visitor" derived class for each "operation" to do on "elements"
class UpVisitor
  : public Visitor {
  virtual auto visit(This *e)->void override {
    cout << "do Up on " + e->Thiss() << endl;
  }

  virtual auto visit(That *e)->void override {
    cout << "do Up on " + e->Thatt() << endl;
  }

  virtual auto visit(TheOther *e)->void override {
    cout << "do Up on " + e->TheOtherr() << endl;
  }

public:

  virtual ~UpVisitor() override = default;
};

class DownVisitor
  : public Visitor {
  virtual auto visit(This *e)->void override {
    cout << "do Down on " + e->Thiss() << endl;
  }

  virtual auto visit(That *e)->void override {
    cout << "do Down on " + e->Thatt() << endl;
  }

  virtual auto visit(TheOther *e)->void override {
    cout << "do Down on " + e->TheOtherr() << endl;
  }

public:

  virtual ~DownVisitor() override = default;
};

inline auto Run()->void
{
  Element *list[]
  {
    new This(),
    new That(),
    new TheOther()
  };

  UpVisitor   up;   // 4. Client creates
  DownVisitor down; // "visitor" objects

  for (auto element : list) {
    //  and passes each
    element->Accept(up);

    // to accept() calls
  }

  for (auto element : list) {
    element->Accept(down);

    if (element != nullptr) delete element;
  }
}
}
