#include <Node.hpp>

Icon& icon = Icon::getInstance();

string leaf::render() { return icon.leafIcon + key + ": " + value; }

string Container::render() { return icon.containerIcon + key; }

Container::Container(json& j, string key, unsigned level) {
  // root has no key and value, just level = 0
  this->level = level;
  this->key = key;
  //将json库parse的data 变成 level 为 0 的Container children 
  for (auto it = j.begin(); it != j.end(); ++it) {
    if (it->is_object()) {
      children.push_back(std::make_unique<Container>(it.value(), it.key(), level + 1));
    } else if (it->is_array()) {
      for (json::iterator arr_it = it->begin(); arr_it != it->end(); ++arr_it) {
        if (arr_it->is_object()) {
          children.push_back(
              std::make_unique<Container>(*arr_it, it.key(), level + 1));
        } else {
          children.push_back(std::make_unique<leaf>(it.key(), arr_it->dump()));
        }
      }
    } else if (it->is_null()) {
      children.push_back(std::make_unique<leaf>(it.key(), ""));
    } else {
      children.push_back(std::make_unique<leaf>(it.key(), it.value().dump()));
    }
  }
}