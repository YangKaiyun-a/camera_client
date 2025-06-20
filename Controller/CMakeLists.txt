cmake_minimum_required(VERSION 3.14)

project(Controller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Controller_src "./*.cpp" "./*.h")

add_library(Controller STATIC ${Controller_src})

# 添加 Config 的头文件目录，确保能包含 Config 的头文件
target_include_directories(Controller PRIVATE ${CMAKE_SOURCE_DIR}/Config)

target_link_libraries(Controller
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    PRIVATE Qt${QT_VERSION_MAJOR}::Gui
    PRIVATE Qt${QT_VERSION_MAJOR}::Network
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
    PRIVATE Configplugin
)
