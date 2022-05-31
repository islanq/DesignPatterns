#pragma once
#include <ostream>

/* Abstract base class declared by framework */
class Document {
public:

  explicit Document(char *fn) {
    strcpy_s(name, fn);
  }

  virtual auto Open()->void  = 0;
  virtual auto Close()->void = 0;
  auto         GetName()->char * {
    return name;
  }

  virtual ~Document() = default;

private:

  char name[20];
};
