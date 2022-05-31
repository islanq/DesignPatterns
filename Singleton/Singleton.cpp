#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Number {
public:

  // 2. Define a public static accessors func
  static auto Instance()->Number *;
  static auto SetType(string t)->void
  {
    type = t;
    delete inst;
    inst = nullptr;
  }

  virtual auto SetValue(int in)->void {
    value = in;
  }

  virtual auto GetValue()->int {
    return value;
  }

  virtual ~Number() = default;

protected:

  int value;

  // 4. Define all ctors to be protected
  Number() : value{0} {
    cout << ":ctor: ";
  }

  // 1. Define a private static attribute

private:

  static string type;
  static Number *inst;
};

string  Number::type = "decimal";
Number *Number::inst = nullptr;

class Octal : public Number {
  // 6. Inheritance can be supported

public:

  friend class Number;
  virtual auto SetValue(int in)->void override
  {
    char buf[10];

    sprintf(buf, "%o", in);
    sscanf(buf, "%d", &value);
  }

protected:

  Octal() {}

public:

  virtual ~Octal() override = default;
};

auto Number::Instance()->Number * 
{
  // 3. Do "lazy initialization" in the accessors function
  if (!inst) {
    inst = type == "octal"
           ? new Octal()
           : new Number();
  }
  return inst;
}

auto main(int argc, char *argv[])->int
{
  // Number  myInstance; - error: cannot access protected constructor
  // 5. Clients may only use the accessors function to manipulate the Singleton

  Number::Instance()->SetValue(42);
  cout << "value is " << Number::Instance()->GetValue() << endl;


  Number::SetType("octal");
  Number::Instance()->SetValue(64);
  cout << "value is " << Number::Instance()->GetValue() << endl;

  getchar();
  return EXIT_SUCCESS;
}
