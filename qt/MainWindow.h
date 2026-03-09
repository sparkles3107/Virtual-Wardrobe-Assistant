#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QSpinBox>
#include <QTableWidget>

#include "FileManager.h"
#include "RecommendationEngine.h"
#include "UserProfile.h"
#include "WardrobeManager.h"

class MainWindow : public QMainWindow {
public:
    MainWindow();

private:
    FileManager fileManager;
    WardrobeManager wardrobeManager;
    RecommendationEngine recommendationEngine;
    UserProfile userProfile;

    QSpinBox *ageSpin;
    QComboBox *skinToneBox;
    QComboBox *heightBox;
    QComboBox *profileStyleBox;

    QLineEdit *nameEdit;
    QComboBox *typeBox;
    QLineEdit *colorEdit;
    QComboBox *itemStyleBox;
    QComboBox *occasionBox;
    QComboBox *patternBox;
    QComboBox *lengthBox;
    QSpinBox *removeIdSpin;
    QTableWidget *table;

    QComboBox *recommendOccasionBox;
    QComboBox *recommendStyleBox;
    QLabel *resultLabel;

    void buildUi();
    void loadData();
    void refreshWardrobeTable();
    void saveProfile();
    void addItem();
    void removeItem();
    void recommendOutfit();

    static QString fromStd(const std::string &text);
    static std::string toStd(const QString &text);
};

#endif
