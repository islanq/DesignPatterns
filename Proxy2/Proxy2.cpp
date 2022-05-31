#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

class Person {
  string nameString;
  static string list[];
  static int next;

public:

  Person() {
    nameString = list[next++];
  }

  auto Name() const->string {
    return nameString;
  }
};
string Person::list[] { "Tom", "Dick", "Harry", "Bubba" };
int    Person::next = 0;

class PettyCashProtected {
  int balance;

public:

  PettyCashProtected()
    : balance{balance = 500}
  {}

  auto Withdraw(int amount)->bool
  {
    if (amount > balance) return false; balance -= amount;
    return true;
  }

  auto GetBalance() const->int {
    return balance;
  }
};

class PettyCash {
  PettyCashProtected realThing;

public:

  auto Withdraw(Person& p, int amount)->bool
  {
    return p.Name() == "Tom"   ||
           p.Name() == "Harry" ||
           p.Name() == "Bubba"
           ? realThing.Withdraw(amount)
           : false;
  }

  auto GetBalance() const->int {
    return realThing.GetBalance();
  }
};

auto main()->int
{
  PettyCash pc;
  Person    workers[4];

  for (auto i = 0, amount = 100; i < 4; i++, amount += 100)
    (!pc.Withdraw(workers[i], amount)
     ? cout << "No money for "
      : cout << amount << " dollars for ")
      << workers[i].Name() << '\n';

  cout << "Remaining balance is " << pc.GetBalance() << '\n';
}
