#include <iostream>
#include <algorithm>

using namespace std;
class ExecuteInterface {
public:

  // 1. Specify the new interface
  virtual ~ExecuteInterface() {}

  virtual auto execute()->void = 0;
};

// 2. Design a "wrapper" or "adapter" class
template<class TYPE>
class ExecuteAdapter
  : public ExecuteInterface {
public:

  ExecuteAdapter(TYPE *o, void(TYPE::*m)())
  {
    object = o;
    method = m;
  }

  // 4. The adapter/wrapper "maps" the new to the legacy implementation
  virtual auto execute()->void override {
    (object->*method)();
  } // the new

  ~ExecuteAdapter() {
    delete object;
  }

private:

  TYPE *object;                         // ptr-to-object attribute
  void (TYPE::*method)(); /* the old */ // ptr-to-member-function attribute
};


// The old: three totally incompatible classes
// no common base class,
class Fea {
public:

  // no hope of polymorphism
  auto DoThis()->void {
    cout << "Fea::DoThis()" << endl;
  }

  ~Fea() {
    cout << "Fea::dtor" << endl;
  }
};

class Feye {
public:

  auto DoThat()->void {
    cout << "Feye::doThat()" << endl;
  }

  ~Feye() {
    cout << "Feye::dtor" << endl;
  }
};

class Pheau {
public:

  auto DoTheOther()->void {
    cout << "Pheau::doTheOther()" << endl;
  }

  ~Pheau() {
    cout << "Pheau::dtor" << endl;
  }
};


/* the new is returned */
ExecuteInterface** initialize()
{
  ExecuteInterface **array = new ExecuteInterface *[3];

  /* the old is below */
  array[0] = new ExecuteAdapter<Fea>(new Fea(), &Fea::DoThis);
  array[1] = new ExecuteAdapter<Feye>(new Feye(), &Feye::DoThat);
  array[2] = new ExecuteAdapter<Pheau>(new Pheau(), &Pheau::DoTheOther);
  return array;
}

auto main()->int
{
  ExecuteInterface **objects = initialize();

  for (auto i = 0; i < 3; i++) objects[i]->execute();

  // 3. Client uses the new (polymorphism)
  for (auto i = 0; i < 3; i++) delete objects[i]; delete objects;
  return 0;
}
