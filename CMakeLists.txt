cmake_minimum_required(VERSION 3.16)
project(VirtualWardrobeQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets QUIET)
if(Qt6_FOUND)
    set(QT_PACKAGE Qt6)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_PACKAGE Qt5)
endif()

add_executable(virtual_wardrobe_qt
    qt/main.cpp
    qt/MainWindow.cpp
    src/ClothingItem.cpp
    src/FileManager.cpp
    src/RecommendationEngine.cpp
    src/UserProfile.cpp
    src/WardrobeManager.cpp
)

target_include_directories(virtual_wardrobe_qt PRIVATE include qt)
target_link_libraries(virtual_wardrobe_qt PRIVATE ${QT_PACKAGE}::Widgets)
