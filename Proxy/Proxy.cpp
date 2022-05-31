#include <string>
#include <iostream>
#include <tuple>
#include <xhash>
#include <filesystem>

using std::string;
using std::cout;
using std::endl;

class Subject {
public:

  virtual auto Execute()->void = 0;
  virtual ~Subject()           = default;
};

class RealSubject
  : public Subject {
  string str;

public:

  explicit RealSubject(string s)
    : str{s} {}

  virtual auto Execute()->void override {
    cout << str << '\n';
  }

  virtual ~RealSubject() override = default;
};

class ProxySubject
  : public Subject {
  string first, second, third;
  RealSubject *ptr;

public:

  friend auto hash_value(const ProxySubject& obj)->size_t
  {
    size_t seed = 0x1CBFDB40;

    seed ^= (seed << 6) + (seed >> 2) + 0x253F0DA2 + hash_value(obj.first);
    seed ^= (seed << 6) + (seed >> 2) + 0x7C30B468 + size_t(obj.ptr);
    return seed;
  }

  explicit ProxySubject(string s)
  {
    auto num = s.find_first_of(' ');

    first = s.substr(0, num);
    s     = s.substr(num + 1);

    num    = s.find_first_of(' ');
    second = s.substr(0, num);
    s      = s.substr(num + 1);

    num   = s.find_first_of(' ');
    third = s.substr(0, num);
    s     = s.substr(num + 1);

    ptr = new RealSubject(s);
  }

  auto operator->() const->RealSubject *
  {
    cout << first << ' ' << second << ' ';
    return ptr;
  }

  virtual auto Execute()->void override
  {
    cout << first << ' ' << third << ' ';
    ptr->Execute();
  }

  ~ProxySubject() {
    delete ptr;
  }
};

auto main()->int
{
  ProxySubject proxy_subject(
    "the quick brown fox \
     jumped over the dog"
    );

  proxy_subject->Execute();
  proxy_subject.Execute();

  getchar();
  return EXIT_SUCCESS;
}
