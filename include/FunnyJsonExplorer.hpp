#pragma once
#include <JsonStyle.hpp>
#include <memory>
#include <nlohmann/json.hpp>

#include "Node.hpp"

using json = nlohmann::json;

// FJE 程序
class FunnyJsonExplorer {
 public:
  FunnyJsonExplorer(std::unique_ptr<JsonStyleFactory>&& jf)
      : jf(std::move(jf)) {}
  void show(json& j) {
    std::unique_ptr<Container> ct = load(j);
    ct->draw();
  }

 private:
  std::unique_ptr<Container> load(json& j) { return jf->create(j); }
  std::unique_ptr<JsonStyleFactory> jf;
};