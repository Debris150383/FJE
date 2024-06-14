#pragma once
#include <JsonVisitor.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <JsonNode.hpp>
#include <string>
using json = nlohmann::json;

class StyleRender : public std::enable_shared_from_this<StyleRender> {
 public:
  //virtual void render(JsonTree& j) = 0;
  virtual void render_line(std::string key, std::string val, unsigned level, bool isLast) = 0;
  virtual std::unique_ptr<RenderJsonVisitor> create() {return std::make_unique<RenderJsonVisitor>(shared_from_this());}
  virtual ~StyleRender() = default;
  virtual void reset() { rendered_content.clear(); }
  virtual void append(std::wstring content) { rendered_content += content; }
  virtual std::wstring get_rendered_content() { return rendered_content; }

 protected:
  std::wstring rendered_content; 
};
