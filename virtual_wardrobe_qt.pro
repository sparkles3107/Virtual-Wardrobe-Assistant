QT += widgets
CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = app
TARGET = virtual_wardrobe_qt

INCLUDEPATH += include qt

SOURCES += \
    qt/main.cpp \
    qt/MainWindow.cpp \
    src/ClothingItem.cpp \
    src/FileManager.cpp \
    src/RecommendationEngine.cpp \
    src/UserProfile.cpp \
    src/WardrobeManager.cpp

HEADERS += \
    qt/MainWindow.h \
    include/ClothingItem.h \
    include/FileManager.h \
    include/RecommendationEngine.h \
    include/UserProfile.h \
    include/WardrobeManager.h
