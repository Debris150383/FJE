#include <JsonNode.hpp>
#include <JsonVisitor.hpp>
#include <StyleRender.hpp>  // Include the header file for the 'StyleRender' class

static std::string getValueAsString(const json::value_t& type,
                                    const json& value) {
  switch (type) {
    case json::value_t::string:
      return value.get<std::string>();
    case json::value_t::number_integer:
      return std::to_string(value.get<int>());
    case json::value_t::number_unsigned:
      return std::to_string(value.get<unsigned int>());
    case json::value_t::number_float:
      return std::to_string(value.get<float>());
    case json::value_t::boolean:
      return value.get<bool>() ? "true" : "false";
    case json::value_t::null:
      return "";
    default:
      return "";
  }
}

void RenderJsonVisitor::visit(const JsonNode& j) {
  json& data = j.get_json();
  std::string key = "";
  for (auto it = data.begin(); it != data.end(); ++it) {
    key = j.get_arr_key().empty() ? it.key() : j.get_arr_key();
    switch (it.value().type()) {
      case json::value_t::object:
        visitNode(key, j.get_level() + 1,
                  j.is_last() && std::next(it) == data.end());
        visit({it.value(), j.get_level() + 1, std::next(it) == data.end()});
        break;
      case json::value_t::array:
        visit(
            {it.value(), j.get_level(), std::next(it) == data.end(), it.key()});
        break;
      case json::value_t::string:
      case json::value_t::number_integer:
      case json::value_t::number_unsigned:
      case json::value_t::number_float:
      case json::value_t::boolean:
      case json::value_t::null:
        visitLeaf(key, getValueAsString(it.value().type(), it.value()),
                  j.get_level() + 1, std::next(it) == data.end());
        break;
      default:
        break;
    }
  }
}

void RenderJsonVisitor::visitLeaf(std::string key, std::string val,
                                  unsigned level, bool isLast) {
  Icon& icon = Icon::getInstance();
  render.lock()->render_line(icon.leafIcon + key, val, level, isLast);
}

void RenderJsonVisitor::visitNode(std::string key, unsigned level,
                                  bool isLast) {
  Icon& icon = Icon::getInstance();
  render.lock()->render_line(icon.containerIcon + key, "", level, isLast);
}
