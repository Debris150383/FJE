#include <TreeJsonStyle.hpp>

void TreeJson::draw() {
  for (size_t i = 0; i < children.size(); i++) {
    drawHelper(children[i], "", i == children.size() - 1);
  }
}

void TreeJson::drawHelper(std::unique_ptr<Node>& node,string indent, bool isLast) {
  if (node == nullptr) {
    return;
  }

  // Print the current node
  std::cout << indent;
  if (isLast) {
    std::cout << "└─ ";
    indent += "   ";  // for next level, this is the end of the branch
  } else {
    std::cout << "├─ ";
    indent += "│  ";  // for next level, the branch continues
  }
  std::cout << node->render() << "\n";

  // If the node is a Container, print its children
  Container* container = dynamic_cast<Container*>(node.get());
  if (container != nullptr) {
    for (size_t i = 0; i < container->children.size(); i++) {
      drawHelper(container->children[i], indent,
                 i == container->children.size() - 1);
    }
  }
}


struct TreeJsonStyleFactoryRegistrar {
    TreeJsonStyleFactoryRegistrar() {
        JsonFactory::registerFactory("tree", [] {
            return std::make_unique<TreeJsonStyleFactory>();
        });
    }
} treeJsonStyleFactoryRegistrar; // 全局变量，构造函数在程序启动时运行