#pragma once

#include <cstddef>
#include <map>
#include <vector>

struct System {
  virtual ~System() = default;    
  virtual void Do() = 0;
};

using SystemId = size_t;

class SystemManager {
  
private:
  
public:
  
};
