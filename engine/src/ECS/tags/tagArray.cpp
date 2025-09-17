#include <ECS/tags/tagArray.hpp>
#include <cassert>
#include <string>

void TagArray::AddTag(std::string name) {
  assert(nameToTag.find(name) != nameToTag.end() && "Register Tag more than once.");

  nameToTag.insert({name, nextTag}); 
  tagToName.insert({nextTag, name});
  nextTag++;
}


Tag TagArray::GetTag(std::string name) {
  assert(nameToTag.find(name) != nameToTag.end() && "Invalid Tag");
  return nameToTag[name];
}

bool TagArray::ValidTag(std::string name) {
  return (nameToTag.find(name) != nameToTag.end());
}
