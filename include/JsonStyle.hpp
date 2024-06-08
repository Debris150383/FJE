#pragma once
#include <IconStyle.hpp>
#include <Node.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class RectangleJson : public Container {
 public:
  void draw();
  RectangleJson(json& j) : Container(j) {}

 private:
  void drawHelper(std::unique_ptr<Node>& node, int level, bool isFirstRoot,
                  bool isLastRoot, int maxLength);
  int calculateMaxLength(std::unique_ptr<Node>& node, int level);
  void printLine(string content, int level, bool isFirstLine, bool isLastLine,
                 int maxLength);
};

class TreeJson : public Container {
 public:
  void draw();
  TreeJson(json& j) : Container(j) {}

 private:
  void drawHelper(std::unique_ptr<Node>& node, string indent, bool isLast);
};

class JsonStyleFactory {
 public:
  virtual std::unique_ptr<Container> create(json& j) = 0;
  virtual ~JsonStyleFactory() = default;
};

class RectangleJsonStyleFactory : public JsonStyleFactory {
 public:
  std::unique_ptr<Container> create(json& j) override {
    return std::make_unique<RectangleJson>(j);
  }
};

class TreeJsonStyleFactory : public JsonStyleFactory {
 public:
  std::unique_ptr<Container> create(json& j) override {
    return std::make_unique<TreeJson>(j);
  }
};

class JsonFactory {
 public:
  using FactoryCreator = std::function<std::unique_ptr<JsonStyleFactory>()>;

  static void registerFactory(const std::string& style,
                              FactoryCreator creator) {
    getRegistry()[style] = std::move(creator);
  }

  static std::unique_ptr<JsonStyleFactory> getFactory(
      const std::string& style) {
    auto& registry = getRegistry();
    auto it = registry.find(style);
    if (it != registry.end()) {
      return it->second();
    } else {
      return nullptr;
    }
  }

 private:
  static std::unordered_map<std::string, FactoryCreator>& getRegistry() {
    static std::unordered_map<std::string, FactoryCreator> registry;
    return registry;
  }
};
