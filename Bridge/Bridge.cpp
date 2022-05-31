#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string.h>
#include <ostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::setw;
using std::setfill;
using std::for_each;
using std::begin;
using std::end;

class TimeImp {
public:

  TimeImp(int hr, int min)
    : hr_{hr},
    min_{min}
  {}

  virtual auto Tell()->void {
    cout << "time is " << setw(2) << setfill(' ') << hr_ << min_ << endl;
  }

  virtual ~TimeImp() = default;

protected:

  int hr_, min_;
};

class CivilianTimeImp
  : public TimeImp {
public:

  CivilianTimeImp(int hr, int min, int pm)
    : TimeImp(hr, min)
  {
    strcpy(whichM_, pm
           ? " PM"
           : " AM");
  }

  auto Tell()->void override {
    cout << "time is " << hr_ << ":" << min_ << whichM_ << endl;
  }

protected:

  char whichM_[4];
};

class ZuluTimeImp
  : public TimeImp {
public:

  ZuluTimeImp(int hr, int min, int zone)
    : TimeImp(hr, min)
  {
    if (zone == 5) strcpy(zone_, " Eastern Standard Time");
    else if (zone == 6) strcpy(zone_, " Central Standard Time");
  }

  auto Tell()->void override {
    cout << "time is " << setw(2) << setfill(' ') << hr_ << min_ << zone_ << endl;
  }

  virtual ~ZuluTimeImp() override = default;

protected:

  char zone_[30];
};

class Time {
public:

  virtual ~Time() = default;
  Time() : imp_{nullptr} {}

  Time(int hr, int min) {
    imp_ = new TimeImp(hr, min);
  }

  virtual auto Tell()->void {
    imp_->Tell();
  }

protected:

  TimeImp *imp_;
};

class CivilianTime
  : public Time {
public:

  CivilianTime(int hr, int min, int pm) {
    imp_ = new CivilianTimeImp(hr, min, pm);
  }

  virtual ~CivilianTime() override = default;
};

class ZuluTime
  : public Time {
public:

  ZuluTime(int hr, int min, int zone) {
    imp_ = new ZuluTimeImp(hr, min, zone);
  }

  virtual ~ZuluTime() override = default;
};


auto main()->int
{
  Time *times[3];

  times[0] = new Time(14, 30);
  times[1] = new CivilianTime(2, 30, 1);
  times[2] = new ZuluTime(14, 30, 6);

  for_each(
    begin(times), end(times),
    [](auto p)
  {
    p->Tell();
  });


  cout << endl << endl;

  for (auto time : times) {
    time->Tell();
  }

  getchar();
  return EXIT_SUCCESS;
}
