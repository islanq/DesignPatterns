#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class AlarmListener {
public:

  virtual ~AlarmListener()   = default;
  virtual auto Alarm()->void = 0;
};

class SensorSystem {
  vector<AlarmListener *>listeners;

public:

  auto Attach(AlarmListener *al)->void {
    listeners.push_back(al);
  }

  auto SoundTheAlarm()->void
  {
    for (auto i = 0; i < listeners.size(); i++) listeners[i]->Alarm();
  }
};

class Lighting
  : public AlarmListener {
public:

  virtual auto Alarm()->void override {
    cout << "lights up" << '\n';
  }

  virtual ~Lighting() override = default;
};

class Gates
  : public AlarmListener {
public:

  virtual auto Alarm()->void override {
    cout << "gates close" << '\n';
  }

  virtual ~Gates() override = default;
};

class CheckList {
  virtual auto Localize()->void {
    cout << "   establish a perimeter" << '\n';
  }

  virtual auto Isolate()->void {
    cout << "   isolate the grid"          << '\n';
  }

  virtual auto Identify()->void {
    cout << "   identify the source"   << '\n';
  }

public:

  auto ByTheNumbers()->void
  {
    // Template Method design pattern
    Localize();
    Isolate();
    Identify();
  }

  virtual ~CheckList() = default;
};

// class inheri.  // type inheritance
class Surveillance
  : public CheckList,
    public AlarmListener {
  virtual auto Isolate()->void override {
    cout << "   train the cameras" << '\n';
  }

public:

  virtual auto Alarm()->void  override
  {
    cout << "Surveillance - by the numbers:" << '\n';
    ByTheNumbers();
  }

  virtual ~Surveillance() override = default;
};

auto main()->int
{
  SensorSystem ss;

  auto gates        = make_unique<Gates>();
  auto lighting     = make_unique<Lighting>();
  auto surveillance = make_unique<Surveillance>();

  ss.Attach(gates.get());
  ss.Attach(lighting.get());
  ss.Attach(surveillance.get());
  ss.SoundTheAlarm();

  getchar();
  return EXIT_SUCCESS;
}
