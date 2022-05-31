#pragma once
#include "MyDocument.hpp"
#include "Application.hpp"

/* Customization of framework defined by client */
class MyApplication : public Application {
public:

  MyApplication()
  {
    cout << "MyApplication: ctor" << endl;
  }

  /* Client defines Framework's "hole" */
  virtual auto CreateDocument(char *fn)->Document * override
  {
    cout << "   MyApplication: CreateDocument()" << endl;
    return new MyDocument(fn);
  }

  virtual ~MyApplication() override = default;
};
