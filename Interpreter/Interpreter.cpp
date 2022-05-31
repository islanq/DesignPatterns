#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <string.h>
#include <iostream>

class Thousand;
class Hundred;
class Ten;
class One;

class RNInterpreter {
public:

  RNInterpreter(); // ctor for client

  explicit RNInterpreter(int)
    : thousands{ nullptr }
    , hundreds{ nullptr }
    , tens{ nullptr }
    , ones{ nullptr } {}

  // ctor for subclasses, avoids infinite loop
  auto Interpret(char*) const -> int; // interpret() for client

  virtual auto Interpret(char* input, int& total) -> void
  {
    // for internal use
    auto index = 0;

    if (!strncmp(input, nine(), 2)) {
      total += 9 * multiplier();
      index += 2;
    } else if (!strncmp(input, four(), 2)) {
      total += 4 * multiplier();
      index += 2;
    } else {
      if (input[0] == five()) {
        total += 5 * multiplier();
        index = 1;
      } else index = 0;

      for (auto end = index + 3; index < end; index++)
        if (input[index] == one()) total += 1 * multiplier();
        else break;
    }
    strcpy(input, &input[index]);
  } // remove leading chars processed

  virtual ~RNInterpreter() = default;

protected:

  // cannot be pure virtual because client asks for instance
  virtual auto one() -> char { return 0; }

  virtual auto four() -> char* { return nullptr; }

  virtual auto five() -> char { return 0; }

  virtual auto nine() -> char* { return nullptr; }

  virtual auto multiplier() -> int { return 0; }

private:

  RNInterpreter* thousands;
  RNInterpreter* hundreds;
  RNInterpreter* tens;
  RNInterpreter* ones;
};

class Thousand
  : public RNInterpreter {
public:

  // provide 1-arg ctor to avoid infinite loop in base class ctor
  explicit Thousand(int) : RNInterpreter(1) {}

protected:

  virtual auto one() -> char override { return 'M'; }

  virtual auto four() -> char* override { return ""; }

  virtual auto five() -> char override { return '\0'; }

  virtual auto nine() -> char* override { return ""; }

  virtual auto multiplier() -> int override { return 1000; }

public:

  ~Thousand() override = default;
};

class Hundred
  : public RNInterpreter {
public:

  explicit Hundred(int)
    : RNInterpreter(1) {}

protected:

  virtual auto one() -> char override { return 'C'; }

  virtual auto four() -> char* override { return "CD"; }

  virtual auto five() -> char override { return 'D'; }

  virtual auto nine() -> char* override { return "CM"; }

  virtual auto multiplier() -> int override { return 100; }

public:

  ~Hundred() override = default;
};

class Ten
  : public RNInterpreter {
public:

  explicit Ten(int)
    : RNInterpreter(1) {}

protected:

  virtual auto one() -> char override { return 'X'; }

  virtual auto four() -> char* override { return "XL"; }

  virtual auto five() -> char override { return 'L'; }

  virtual auto nine() -> char* override { return "XC"; }

  virtual auto multiplier() -> int override { return 10; }

public:

  virtual ~Ten() override = default;
};

class One
  : public RNInterpreter {
public:

  explicit One(int)
    : RNInterpreter(1) {}

protected:

  virtual char one() override { return 'I'; }

  virtual char* four() override { return "IV"; }

  virtual char five() override { return 'V'; }

  virtual char* nine() override { return "IX"; }

  virtual int multiplier() override { return 1; }

public:

  virtual ~One() override = default;
};

RNInterpreter::RNInterpreter() :
    thousands(new Thousand(1)),
    hundreds(new Hundred(1)),
    tens(new Ten(1)),
    ones(new One(1))
{
  // use 1-arg ctor to avoid infinite loop
}

auto RNInterpreter::Interpret(char* input) const -> int
{
  auto total = 0;

  thousands->Interpret(input, total);
  hundreds->Interpret(input, total);
  tens->Interpret(input, total);
  ones->Interpret(input, total);
  return strcmp(input, "") ? 0 : total; // if input was invalid, return 0
}

auto main() -> int
{
  using std::cout;
  using std::cin;
  using std::endl;

  char input[20];
  RNInterpreter interpreter;

  cout << "Enter Roman Numeral: ";

  while (cin >> input) {
    cout << "interpretation is: "
      << interpreter.Interpret(input)
      << "\nEnter Roman Numeral: ";
  }

  getchar();
  return EXIT_SUCCESS;
}
