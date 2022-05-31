#pragma once
#include <vector>
#include <iostream>

namespace commander::example2 {
class Number {
public:

  auto Double(int& value)->void {
    value *= 2;
  }
};

class Command {
public:

  virtual ~Command()               = default;
  virtual auto Execute(int&)->void = 0;
};

class SimpleCommand
  : public Command {
  typedef void (Number::*Action)(int&);
  Number *receiver;
  Action action;

public:

  SimpleCommand(Number *rec, Action act)
    : receiver{rec}
    , action{act} {}

  virtual auto Execute(int& num)->void override {
    (receiver->*action)(num);
  }
};

class MacroCommand
  : public Command {
  vector<Command *>list;

public:

  auto Add(Command *cmd)->void {
    list.push_back(cmd);
  }

  virtual auto Execute(int& num)->void override
  {
    for (uint32_t i = 0; i < list.size(); i++) list[i]->Execute(num);
  }
};

inline auto Run()->void
{
  Number   object;
  Command *commands[3];

  commands[0] = &SimpleCommand(&object, &Number::Double);

  MacroCommand two;
  two.Add(commands[0]);
  two.Add(commands[0]);
  commands[1] = &two;

  MacroCommand four;
  four.Add(&two);
  four.Add(&two);
  commands[2] = &four;

  int num, index;

  while (true) {
    cout << "Enter number selection (0=2x 1=4x 2=16x): ";
    cin >> num >> index;

    if (num == 0000) break;
    commands[index]->Execute(num);
    cout << "   " << num << '\n';
  }
}
}
