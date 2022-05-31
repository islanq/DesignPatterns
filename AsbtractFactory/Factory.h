#pragma once

class Factory {
public:

  virtual auto CreateCurvedInstance()->Shape *   = 0;
  virtual auto CreateStraightInstance()->Shape * = 0;
  virtual ~Factory()                             = default;
};
