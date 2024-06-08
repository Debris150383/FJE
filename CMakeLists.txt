file(GLOB_RECURSE SOURCES "src/*.cpp")

add_subdirectory(external/json)
add_subdirectory(external/argparse)


add_executable(FJE ${SOURCES} )
target_link_libraries(FJE nlohmann_json::nlohmann_json argparse)

set_target_properties(FJE PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

target_include_directories(FJE PRIVATE include)