#pragma once
#include <nlohmann/json.hpp>
#include <JsonStyle.hpp>
#include <string>
#include "Node.hpp"
#include <memory>

using json = nlohmann::json;

// FJE 程序
class FunnyJsonExplorer {
 public:
  FunnyJsonExplorer(std::unique_ptr<JsonStyleFactory>&& jf) : jf(std::move(jf)) {
  }
  void show(json& j) {
    std::unique_ptr<Container> ct = load(j);
    ct->draw(); 
  }

 private:
  std::unique_ptr<Container> load(json& j);
  std::unique_ptr<JsonStyleFactory> jf;
};