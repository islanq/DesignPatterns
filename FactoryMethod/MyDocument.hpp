#pragma once
#include "Document.hpp"
#include <iostream>

/* Concrete derived class defined by client */
class MyDocument : public Document {
public:

  explicit MyDocument(char *fn)
    : Document{fn}
  {}

  virtual auto Open()->void override {
    std::cout << "   MyDocument: Open()" << std::endl;
  }

  virtual auto Close()->void override {
    std::cout << "   MyDocument: Close()" << std::endl;
  }

  virtual ~MyDocument() override = default;
};
