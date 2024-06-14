#pragma once
#include <memory>
#include <nlohmann/json.hpp>
#include <JsonNode.hpp>
#include <string>
#include <IconStyle.hpp>

//#include "StyleRender.hpp"
//#include <StyleRender.hpp>
class StyleRender;
using json = nlohmann::json;

class JsonVisitor {
 public:
  virtual void visit(const JsonNode& j) = 0;
  // virtual void visitObject(const json::value_t& obj) = 0;
  // virtual void visitArray(const json::value_t& arr) = 0;
  virtual void visitNode(std::string key,  unsigned level, bool isLast) = 0;
  virtual void visitLeaf(std::string key, std::string val, unsigned level, bool isLast) = 0;
  virtual ~JsonVisitor() = default;
};

class RenderJsonVisitor : public JsonVisitor {
 public:
  virtual void visit(const JsonNode& j) override;
  virtual void visitNode(std::string key, unsigned level, bool isLast) override;
  virtual void visitLeaf(std::string key, std::string val, unsigned level, bool isLast) override;
  
  RenderJsonVisitor(std::weak_ptr<StyleRender> render) : render(render) {}
 private:
  std::weak_ptr<StyleRender> render;
};
