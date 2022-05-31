#pragma once
#include <ostream>

/* Abstract base class declared by framework */
class Document {
public:

  explicit Document(char *fn) {
    strcpy_s(name, fn);
  }

  virtual void Open()  = 0;
  virtual void Close() = 0;
  char* GetName() {
    return name;
  }

  virtual ~Document() = default;

private:

  char name[20];
};
