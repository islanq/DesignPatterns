#include <iostream>
#include <string>

class Number;

class Memento {
public:

  explicit Memento(int val)
    : _state{val}
  {}

private:

  friend class Number; // not essential, but p287 suggests this
  int _state;
};

class Number {
public:

  explicit Number(int value)
    : _value{value}
  {}

  auto Dubble()->void     {
    _value = 2 * _value;
  }

  auto Half()->void     {
    _value = _value / 2;
  }

  auto GetValue() const->int      {
    return _value;
  }

  auto createMemento() const->Memento * {
    return new Memento(_value);
  }

  void ReinstateMemento(Memento *mem) {
    _value = mem->_state;
  }

private:

  int _value;
};

class Command {
public:

  virtual ~Command() = default;
  typedef void (Number::*Action)();
  Command(Number *receiver, Action action)
    : _receiver{receiver}, _action{action}
  {}

  virtual auto Execute()->void
  {
    _mementoList[_numCommands] = _receiver->createMemento();
    _commandList[_numCommands] = this;

    if (_numCommands > _highWater) {
      _highWater = _numCommands;
    }
    _numCommands++;
    (_receiver->*_action)();
  }

  static auto Undo()->void
  {
    if (_numCommands == 0) {
      std::cout << "*** Attempt to run off the end!! ***" << std::endl;
      return;
    }
    _commandList[_numCommands -
                 1]->_receiver->ReinstateMemento(_mementoList[_numCommands - 1]);
    _numCommands--;
  }

  static auto Redo()->void
  {
    if (_numCommands > _highWater) {
      std::cout << "*** Attempt to run off the end!! ***" << std::endl;
      return;
    }
    (_commandList[_numCommands]->_receiver->*_commandList[_numCommands]->_action)();
    _numCommands++;
  }

protected:

  Number *_receiver;
  Action _action;
  static Command *_commandList[20];
  static Memento *_mementoList[20];
  static int _numCommands;
  static int _highWater;
};

Command *Command::_commandList[];
Memento *Command::_mementoList[];
int Command::_numCommands = 0;
int Command::_highWater   = 0;

auto main()->int
{
  int choice;

  std::cout << "Integer: ";
  std::cin >> choice;
  auto object = new Number(choice);

  Command *commands[3];
  commands[1] = new Command(object, &Number::Dubble);
  commands[2] = new Command(object, &Number::Half);

  auto display_choices = "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";

  std::cout << display_choices;
  std::cin >> choice;

  while (choice) {
    try {
      auto triggered = false;

      if      (choice == 3) Command::Undo();
      else if (choice == 4) Command::Redo();
      else if (choice < 5) commands[choice]->Execute(); else {  triggered = true;
                                                                std
                                                                ::cout <<
        "\n-----Invalid number, try again!-----\n\n"; }

      if (!triggered) std::cout << "   " << object->GetValue() << std::endl;
      std::cout << display_choices;
      std::cin  >> choice;

      if (choice > 254) throw "Number too large!";
    } catch (decltype(choice) error) {
      std::cout << error << std::endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
