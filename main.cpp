#include <argparse/argparse.hpp>
#include <cassert>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>

#include "FunnyJsonExplorer.hpp"
#include "IconStyle.hpp"
#include "JsonStyle.hpp"
#include "Node.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
  // icon 配置文件 请使用绝对路径
  std::string icon_file_path = "./icon_config.json";
  // argparse 设置 
  argparse::ArgumentParser program("FJE");
  program.add_argument("-f").help("json file to be parsed");

  // two styles  rectangle and tree
  program.add_argument("-s", "--style")
      .help("Choose an icon style: rectangle or tree")
      .default_value(std::string("tree"))
      .action([](const std::string& value) {
        if (value != "rectangle" && value != "tree") {
          throw std::runtime_error("Invalid style: " + value);
        }
        return value;
      });

  // n icons 根据 配置文件显示
  json icon_config = json::parse(
      std::ifstream(icon_file_path));
  std::vector<std::string> iconNames;
  for (auto it = icon_config.begin(); it != icon_config.end(); ++it) {
    iconNames.push_back(it.key());
  }

  std::string iconHelpInfo = "Choose an icon from the following";
  for (auto& icon : iconNames) {
    iconHelpInfo += " " + icon;
  }
  program.add_argument("-i", "--icon")
      .help(iconHelpInfo)
      .default_value(std::string("star"))
      .action([&iconNames](const std::string& value) {
        if (std::find(iconNames.begin(), iconNames.end(), value) ==
            iconNames.end()) {
          throw std::runtime_error("Invalid icon: " + value);
        }
        return value;
      });

  // TODO:输出到文件, 可选, 暂时未实现
  program.add_argument("-o", "--output")
      .help("Output to a file")
      .default_value(std::string(""));

  program.usage();

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cout << err.what() << std::endl;
    std::cout << program;
    return 1;
  }

  // 解析参数
  std::string json_file_path = program.get<std::string>("-f");
  std::string style = program.get<std::string>("-s");
  std::string iconStyle = program.get<std::string>("-i");
  std::string output = program.get<std::string>("-o");

  std::ifstream json_file(json_file_path);
  if (!json_file.is_open()) {
    std::cout << "File not found: " << json_file_path << std::endl;
    return 1;
  }
  // 解析json文件
  json data = json::parse(json_file);
  // 根据style选择工厂
  std::unique_ptr<JsonStyleFactory> factory = JsonFactory::getFactory(style);
  // 根据配置文件的icon 设置全局唯一的icon实例
  for (auto it = icon_config.begin(); it != icon_config.end(); ++it) {
    if (it.key() == iconStyle) {
      Icon& icon = Icon::getInstance();
      icon.leafIcon = it.value()["leaf"];
      icon.containerIcon = it.value()["container"];
      icon.name = iconStyle;
    }
  }

  // 创建FJE并显示相应风格json
  FunnyJsonExplorer fje(std::move(factory));
  fje.show(data);
}