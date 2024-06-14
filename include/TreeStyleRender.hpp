#pragma once
#include <StyleRender.hpp>

class TreeStyleRender : public StyleRender {
 public:
  //void render(JsonTree& j) override;
  //void render_object(json::object_t& obj) override;
  //void render_array(json::array_t& arr) override;
  void render_line(std::string key, std::string val, unsigned level, bool isLast) override;
  std::wstring indent;
};