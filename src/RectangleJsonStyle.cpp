#include <RectangleJsonStyle.hpp>


void RectangleJson::draw() {
  int maxLength = 0;
  for (auto&& child : children) {
    maxLength = std::max(maxLength, calculateMaxLength(child, 1));
  }

  for (size_t i = 0; i < children.size(); i++) {
    drawHelper(children[i], 1, i == 0, i == children.size() - 1, maxLength);
  }
}

void RectangleJson::drawHelper(std::unique_ptr<Node>& node, int level, bool isFirstRoot,
                               bool isLastRoot, int maxLength) {
  if (node == nullptr) {
    return;
  }
  std::string content = node->render();
  Container* container = dynamic_cast<Container*>(node.get());
  bool isLastLine =
      isLastRoot && (container == nullptr || container->children.empty());
  bool isFirstLine = isFirstRoot;

  printLine(content, level, isFirstLine, isLastLine, maxLength);

  if (container != nullptr) {
    for (size_t i = 0; i < container->children.size(); i++) {
      drawHelper(container->children[i], level + 1, false,
                 isLastRoot && i == container->children.size() - 1, maxLength);
    }
  }
}

int RectangleJson::calculateMaxLength(std::unique_ptr<Node>& node, int level) {
  if (node == nullptr) {
    return 0;
  }

  int maxLength = node->render().length() + level * 8;
  Container* container = dynamic_cast<Container*>(node.get());
  if (container != nullptr) {
    for (auto&& child : container->children) {
      maxLength = std::max(maxLength, calculateMaxLength(child, level + 1));
    }
  }
  return maxLength;
}

void RectangleJson::printLine(std::string content, int level, bool isFirst,
                              bool isLast, int maxLength) {
  std::string indent = "";
  for (int i = 0; i < level - 1; i++) {
    if (isLast)
      indent += "└─ ";
    else
      indent += "│  ";
  }
  std::string prefix = isFirst ? "┌─ " : (isLast ? "└─ " : "├─ ");
  std::string line = indent + prefix + content;
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  std::wstring wide_line = converter.from_bytes(line);

  int padding = maxLength - wide_line.length();
  assert(padding > 0 && "padding must be positive");
  line += std::string(padding, '-');

  if (isFirst) {
    std::cout << line << "┐\n";
  } else if (isLast) {
    std::cout << line << "┘\n";
  } else {
    std::cout << line << "┤\n";
  }
}

struct RectangleJsonStyleFactoryRegistrar {
    RectangleJsonStyleFactoryRegistrar() {
        JsonFactory::registerFactory("rectangle", [] {
            return std::make_unique<RectangleJsonStyleFactory>();
        });
    }
} rectangleJsonStyleFactoryRegistrar; // 全局变量，构造函数在程序启动时运行