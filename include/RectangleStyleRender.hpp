#pragma once
#include <StyleRender.hpp>
#include "JsonNode.hpp"


class RectangleStyleRender : public StyleRender {
 public:

  void render_line(std::string key, std::string val, unsigned level ,bool isLast) override;
  void reset() override { lines.clear(); maxLineLength = 0; }
  std::wstring get_rendered_content() override { render_content(); return rendered_content;}
 private:
  void render_content();
  unsigned maxLineLength = 0; 
  std::vector<std::wstring> lines;
};