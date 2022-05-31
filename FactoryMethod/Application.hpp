#pragma once
#include <ostream>
#include <iostream>

using std::cout;
using std::endl;

/* Framework declaration */
class Application {
public:

  Application()
    : _index(0)
  {
    cout << "Application: ctor" << endl;
  }

  /* The client will call this "entry point" of the framework */
  auto NewDocument(char *name)->void
  {
    cout << "Application: NewDocument()" << endl;

    /* Framework calls the "hole" reserved for client customization */
    _docs[_index] = CreateDocument(name);
    _docs[_index++]->Open();
  }

  static auto  OpenDocument()->void {}

  auto         ReportDocs()->void;

  /* Framework declares a "hole" for the client to customize */
  virtual auto CreateDocument(char *)->Document * = 0;
  virtual ~Application()                          = default;

private:

  int _index;

  /* Framework uses Document's base class */
  Document *_docs[10];
};

inline auto Application::ReportDocs()->void
{
  cout << "Application: ReportDocs()" << endl;

  for (auto i = 0; i < _index; i++) {
    cout << "   " << _docs[i]->GetName() << endl;
  }
}
