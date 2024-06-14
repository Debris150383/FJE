#pragma once
#include <StyleRender.hpp>
#include "JsonNode.hpp"


class RectangleStyleRender : public StyleRender {
 public:
  //void render(JsonTree& j) override;
  //void render_object(json::object_t& obj) override;
  //void render_array(json::array_t& arr) override;

  void render_line(std::string key, std::string val, unsigned level ,bool isLast) override;
  void reset() override { lines.clear(); maxLineLength = 0; }
  std::wstring get_rendered_content() override { render_content(); return rendered_content;}
 private:
  void render_content();
  unsigned maxLineLength = 0; 
  std::vector<std::wstring> lines;
};