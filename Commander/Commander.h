#pragma once
#include <iostream>
#include <string>


using namespace std; 

namespace commander::example {
class Person;
class Command {
  // 1. Create a class that encapsulates an object and a member function
  // a pointer to a member function (the attribute's name is "method")

  // void (Person::*method)();
  typedef void (Person::*method_ptr_)();
  using person_method_ptr = void (Person::*)();
  person_method_ptr method;
  Person *object; //

public:

  explicit Command(Person           *obj = nullptr,
                   person_method_ptr meth = nullptr)
    : method{meth}
    , object{obj}
  {}

  auto Execute() const->void {
    // invoke the method on the object
    (object->*method)();
  }
};

class Person {
  // cmd is a "black box", it is a method invocation
  string name;

  // promoted to "full object status"
  Command cmd;

public:

  Person(string n, Command c)
    : name{std::move(n)}
    , cmd{c} {}


  auto Talk() const ->void
  {
    // "this" is the sender, cmd has the receiver
    cout << name << " is talking" << endl;

    // ask the "black box" to callback the receiver
    cmd.Execute();
  }

  auto PassOn() const ->void
  {
    cout << name << " is passing on" << endl;

    // 4. When the sender is ready to callback to the receiver,
    // it calls execute()
    cmd.Execute();
  }

  auto Gossip() const ->void
  {
    cout << name << " is gossiping" << endl;
    cmd.Execute();
  }

  // ReSharper disable once CppMemberFunctionMayBeConst
  auto Listen()->void {
    cout << name << " is listening" << endl;
  }
};

inline auto Run()->void
{
  // Fred will "execute" Barney which will result in a call to passOn()
  // Barney will "execute" Betty which will result in a call to gossip()
  // Betty will "execute" Wilma which will result in a call to listen()
  Person wilma("Wilma", Command());

  // 2. Instantiate an object for each "callback"
  // 3. Pass each object to its future "sender"
  Person betty("Betty", Command(&wilma, &Person::Listen));
  Person barney("Barney", Command(&betty, &Person::Gossip));
  Person fred("Fred", Command(&barney, &Person::PassOn));

  fred.Talk();

  getchar();
}
}
