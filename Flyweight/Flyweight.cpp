#include <iostream>
#include <string.h>
#include <algorithm>
using std::cout;
using std::endl;

class Icon {
public:

  explicit Icon(char *fileName)
  {
    strcpy_s(_name, fileName);

    if (!strcmp(fileName, "go")) {
      _width  = 20;
      _height = 20;
    }

    if (!strcmp(fileName, "stop")) {
      _width  = 40;
      _height = 40;
    }

    if (!strcmp(fileName, "select")) {
      _width  = 60;
      _height = 60;
    }

    if (!strcmp(fileName, "undo")) {
      _width  = 30;
      _height = 30;
    }
  }

  auto GetName() const->const char *     {
    return _name;
  }

  auto Draw(int x, int y) const->void
  {
    cout << "   drawing " << _name << ": upper left (" << x << "," << y <<
      ") - lower right (" << x + _width << "," << y + _height << ")" <<
      endl;
  }

private:

  char _name[20];
  int _width, _height;
};

class FlyweightFactory {
public:

  static auto GetIcon(char *name)->Icon *
  {
    for (auto i = 0; i < _numIcons; i++)
      if (!strcmp(name, _icons[i]->GetName())) return _icons[i];

    _icons[_numIcons] = new Icon(name);
    return _icons[_numIcons++];
  }

  static auto ReportTheIcons()->void
  {
    cout << "Active Flyweights: ";

    for (auto i = 0; i < _numIcons; i++) cout << _icons[i]->GetName() << " ";
    cout << endl;
  }

private:

  enum { MAX_ICONS = 5 };
  static int _numIcons;
  static Icon *_icons[MAX_ICONS];
};

int   FlyweightFactory::_numIcons = 0;
Icon *FlyweightFactory::_icons[];

class DialogBox {
public:

  DialogBox(int x, int y, int incr)
    : _iconsOriginX(x)
    , _iconsOriginY(y)
    , _iconsXIncrement(incr) {}

  virtual auto Draw()->void = 0;
  virtual ~DialogBox()      = default;

protected:

  Icon *_icons[3];
  int _iconsOriginX, _iconsOriginY, _iconsXIncrement;
};

class FileSelection : public DialogBox {
public:

  FileSelection(Icon *first, Icon *second, Icon *third)
    : DialogBox(100, 100, 100)
  {
    _icons[0] = first;
    _icons[1] = second;
    _icons[2] = third;
  }

  virtual auto Draw()->void override
  {
    cout << "drawing FileSelection:" << endl;

    for (auto i = 0; i < 3;
         i++) _icons[i]->Draw(_iconsOriginX + (i * _iconsXIncrement),
                              _iconsOriginY);
  }

  virtual ~FileSelection() override = default;
};

class CommitTransaction : public DialogBox {
public:

  CommitTransaction(Icon *first, Icon *second, Icon *third)
    : DialogBox(150,
                150,
                150)
  {
    _icons[0] = first;
    _icons[1] = second;
    _icons[2] = third;
  }

  virtual auto Draw()->void override
  {
    cout << "drawing CommitTransaction:" << endl;

    for (auto i = 0; i < 3;
         i++) _icons[i]->Draw(_iconsOriginX + (i * _iconsXIncrement),
                              _iconsOriginY);
  }

  virtual ~CommitTransaction() override = default;
};

auto main()->int
{
  DialogBox *dialogs[2];

  dialogs[0] = new FileSelection(
    FlyweightFactory::GetIcon("go"),
    FlyweightFactory::GetIcon("stop"),
    FlyweightFactory::GetIcon("select")
    );

  dialogs[1] = new CommitTransaction(
    FlyweightFactory::GetIcon("select"),
    FlyweightFactory::GetIcon("stop"),
    FlyweightFactory::GetIcon("undo")
    );

  for (auto dialog : dialogs) dialog->Draw();

  FlyweightFactory::ReportTheIcons();

  getchar();
  return EXIT_SUCCESS;
}
