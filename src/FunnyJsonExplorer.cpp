#include "FunnyJsonExplorer.hpp"
#include <iostream>
#include <memory>
#include "Node.hpp"


std::unique_ptr<Container> FunnyJsonExplorer::load(json& j) {
    return jf->create(j);
}
