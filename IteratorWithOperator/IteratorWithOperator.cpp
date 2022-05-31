#include <iostream>

class Stack {
  int items[10], sp;

public:

  friend class StackIter;
  Stack() : sp{-1}
  {}

  auto Push(int in)->void {
    items[++sp] = in;
  }

  auto Pop()->int  {
    return items[sp--];
  }

  auto IsEmpty() const->bool {
    return sp == -1;
  }
};

class StackIter {
  const Stack& stk;
  int index;

public:

  explicit StackIter(const Stack& s)
    : stk{s}
    , index{0}
  {}

  auto operator++()->void {
    index++;
  }

  auto operator()() const->bool {
    return index != stk.sp + 1;
  }

  auto operator*() const->int  {
    return stk.items[index];
  }
};

bool operator==(const Stack& l, const Stack& r)
{
  StackIter itl(l), itr(r);

  for (; itl(); ++itl, ++itr)
    if (*itl != *itr) break;
  return !itl() && !itr();
}

auto main()->int
{
  using std::cout;
  using std::endl;

  Stack s1;

  for (auto i = 1; i < 5; i++) {
    s1.Push(i);
  }
  auto s2(s1), s3(s1), s4(s1), s5(s1);
  s3.Pop();
  s5.Pop();
  s4.Push(2);
  s5.Push(9);
  cout << "1 == 2 is " << (s1 == s2) << '\n'
       << "1 == 3 is " << (s1 == s3) << '\n'
       << "1 == 4 is " << (s1 == s4) << '\n'
       << "1 == 5 is " << (s1 == s5) << endl;


  getchar();
  return EXIT_SUCCESS;
}
