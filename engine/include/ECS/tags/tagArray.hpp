#pragma once

#include <cstdint>
#include <map>
#include <string>

using Tag = std::uint64_t;  

class TagArray {
  
private:
  std::map<std::string, Tag> nameToTag;
  std::map<Tag, std::string> tagToName;

  Tag nextTag = 0;
  
public:
  void AddTag(std::string name);
  Tag GetTag(std::string name);

  bool ValidTag(std::string name);
};
