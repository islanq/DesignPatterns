#include <iostream>
using std::cout;
using std::endl;

class FileSelectionDialog;

class Widget {
public:

  Widget(FileSelectionDialog *mediator, char *name)
  {
    _mediator = mediator;
    strcpy_s(_name, name);
  }

  virtual auto Changed()->void;
  virtual auto UpdateWidget()->void = 0;
  virtual auto QueryWidget()->void  = 0;
  virtual ~Widget()                 = default;

protected:

  char _name[20];

private:

  FileSelectionDialog *_mediator;
};

class List
  : public Widget {
public:

  List(FileSelectionDialog *dir, char *name)
    : Widget(dir, name)
  {}

  virtual auto QueryWidget()->void override {
    cout << "   " << _name << " list queried" << endl;
  }

  virtual auto UpdateWidget()->void override {
    cout << "   " << _name << " list updated" << endl;
  }
};

class Edit
  : public Widget {
public:

  Edit(FileSelectionDialog *dir, char *name)
    : Widget(dir, name)
  {}

  virtual auto QueryWidget()->void override {
    cout << "   " << _name << " edit queried" << endl;
  }

  virtual auto UpdateWidget()->void override {
    cout << "   " << _name << " edit updated" << endl;
  }
};

class FileSelectionDialog {
public:

  enum Widgets
  {
    FilterEdit,
    DirList,
    FileList,
    SelectionEdit
  };
  FileSelectionDialog()
  {
    _components[FilterEdit]    = new Edit(this, "filter");
    _components[DirList]       = new List(this, "dir");
    _components[FileList]      = new List(this, "file");
    _components[SelectionEdit] = new Edit(this, "selection");
  }

  virtual ~FileSelectionDialog();
  auto handleEvent(int which)->void {
    _components[which]->Changed();
  }

  virtual auto widgetChanged(Widget *theChangedWidget)->void
  {
    if (theChangedWidget == _components[FilterEdit]) {
      _components[FilterEdit]->QueryWidget();
      _components[DirList]->UpdateWidget();
      _components[FileList]->UpdateWidget();
      _components[SelectionEdit]->UpdateWidget();
    } else if (theChangedWidget == _components[DirList]) {
      _components[DirList]->QueryWidget();
      _components[FileList]->UpdateWidget();
      _components[FilterEdit]->UpdateWidget();
      _components[SelectionEdit]->UpdateWidget();
    } else if (theChangedWidget == _components[FileList]) {
      _components[FileList]->QueryWidget();
      _components[SelectionEdit]->UpdateWidget();
    } else if (theChangedWidget == _components[SelectionEdit]) {
      _components[SelectionEdit]->QueryWidget();
      cout << "   file opened" << endl;
    }
  }

private:

  Widget *_components[4];
};

FileSelectionDialog::~FileSelectionDialog()
{
  for (auto i = 0; i < 4; i++) delete _components[i];
}

auto Widget::Changed()->void {
  _mediator->widgetChanged(this);
}

auto main()->int
{
  FileSelectionDialog FileDialog;
  int i;

  cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
  std::cin >> i;

  while (i) {
    FileDialog.handleEvent(i - 1);
    cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
    std::cin >> i;
  }

  return EXIT_SUCCESS;
}
