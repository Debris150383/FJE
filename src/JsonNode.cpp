#include <JsonNode.hpp>
#include <JsonVisitor.hpp>

void JsonNode::accept(JsonVisitor& visitor) {
    //std::cout << "begin parse json" << std::endl;
    visitor.visit(*this);
}