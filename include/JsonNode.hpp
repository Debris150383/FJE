#pragma once
//#include <JsonVisitor.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
class JsonVisitor;

class JsonNode {
 public:
  void accept(JsonVisitor& visitor);
  JsonNode(json& j, unsigned level = 0, bool isLast = true, std::string arr_key = "") : j(j), level(level),isLast(isLast), arr_key(arr_key) {}
  json& get_json()const { return j; }
  unsigned get_level() const{ return level; }
  bool is_last() const { return isLast; }
  std::string get_arr_key() const { return arr_key; }
  //bool is_leaf() { return isLeaf; }
 private:
  json& j;
  unsigned level;
  bool isLast;
  std::string arr_key;
};
