#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace visitor::infotype {
class Visitor {
public:

  virtual ~Visitor() = default;
  virtual auto Visit(class Primitive *, class Component *)->void = 0;
  virtual auto Visit(class Composite *, Component *)->void = 0;
};

class Component {
  int value;

public:

  explicit Component(int val) : value{val} {}

  virtual auto Traverse()->void {
    cout << value << " ";
  }

  // Having add() here sacrifices safety, but it supports
  // transparency
  // virtual void add( Component* ) { }
  virtual auto Accept(Visitor&,
                      Component *)->void = 0;
  virtual ~Component() = default;
};

class Primitive
  : public Component {
public:

  explicit Primitive(int val)
    : Component{val} {}

  virtual auto Accept(Visitor& v, Component *c)->void override {
    v.Visit(this, c);
  }
};

class Composite
  : public Component {
  vector<Component *>children;

public:

  explicit Composite(int val)
    : Component{val} {}

  auto Add(Component *ele)->void {
    children.push_back(ele);
  }

  virtual auto Accept(Visitor& v, Component *c)->void override {
    v.Visit(this, c);
  }

  virtual auto Traverse()->void override
  {
    Component::Traverse();

    for (auto i = 0; i < children.size();
         i++) children[i]->Traverse();
  }
};

class AddVisitor
  : public Visitor {
public:

  virtual auto Visit(Primitive *, Component *)->void override
  { /* does
       not
       make
       sense
     */
  }

  virtual auto Visit(Composite *node, Component *c)->void override {
    node->Add(c);
  }
};

inline auto Run()->void
{
  Component *nodes[3];


  /// <memo>
  /// The type of Composite* is "lost" when the object is
  /// assigned to a
  /// Component*
  /// </memo>
  nodes[0] = new Composite(1);
  nodes[1] = new Composite(2);
  nodes[2] = new Composite(3);

  /// <memo>
  /// If add() were in class Component, this would work
  ///     nodes[0]->add(nodes[1]);
  /// If it is NOT in Component, and only in Composite, you
  /// get the error -
  /// no member function `Component::add(Component *)' defined
  /// Instead of sacrificing safety, we use a Visitor to
  /// support add()
  /// </memo>
  AddVisitor addVisitor;
  nodes[0]->Accept(addVisitor, nodes[1]);
  nodes[0]->Accept(addVisitor, nodes[2]);
  nodes[0]->Accept(addVisitor, new Primitive(4));
  nodes[1]->Accept(addVisitor, new Primitive(5));
  nodes[1]->Accept(addVisitor, new Primitive(6));
  nodes[2]->Accept(addVisitor, new Primitive(7));

  for (auto node : nodes) {
    node->Traverse();
    cout << endl;
  }
}//! class visitor
}//! namespace visitor::typeinfo
