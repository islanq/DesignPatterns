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

  auto CreateIterator() const->StackIter *; // 2. Add a createIterator() member
};

class StackIter {
  // 1. Design an "iterator" class
  const Stack *stk;
  int index;

public:

  explicit StackIter(const Stack *s)
    : stk{s}
    , index{0}
  {}

  auto First()->void {
    index = 0;
  }

  auto Next()->void {
    index++;
  }

  auto IsDone() const->bool {
    return index == stk->sp + 1;
  }

  auto CurrentItem() const->int  {
    return stk->items[index];
  }
};

auto Stack::CreateIterator() const->StackIter * {
  return new StackIter(this);
}

auto operator==(const Stack& l, const Stack& r)->bool
{
  // 3. Clients ask the container object to create an iterator object
  auto itl = l.CreateIterator();
  auto itr = r.CreateIterator();

  // 4. Clients use the first(), isDone(), next(), and currentItem() protocol
  for (itl->First(), itr->First(); !itl->IsDone(); itl->Next(), itr->Next())
    if (itl->CurrentItem() != itr->CurrentItem()) break;

  auto ans = itl->IsDone() && itr->IsDone();
  delete itl;
  delete itr;
  return ans;
}

auto main()->int
{
  using std::cout;
  using std::endl;

  Stack s1;

  for (auto i = 1; i < 5; i++) s1.Push(i); auto s2(s1), s3(s1), s4(s1), s5(s1);
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
