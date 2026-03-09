#include "MainWindow.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow() : fileManager("wardrobe_data.txt", "user_profile.txt"), wardrobeManager(), userProfile() {
    buildUi();
    loadData();
}

QString MainWindow::fromStd(const std::string &text) { return QString::fromStdString(text); }
std::string MainWindow::toStd(const QString &text) { return text.trimmed().toStdString(); }

void MainWindow::buildUi() {
    setWindowTitle("Virtual Wardrobe Assistant (Qt)");
    resize(980, 700);

    QWidget *central = new QWidget(this);
    QVBoxLayout *rootLayout = new QVBoxLayout(central);

    QTabWidget *tabs = new QTabWidget(central);

    QWidget *profileTab = new QWidget(tabs);
    QFormLayout *profileForm = new QFormLayout(profileTab);
    ageSpin = new QSpinBox(profileTab);
    ageSpin->setRange(5, 100);
    skinToneBox = new QComboBox(profileTab);
    skinToneBox->addItems({"warm", "cool", "neutral"});
    heightBox = new QComboBox(profileTab);
    heightBox->addItems({"short", "average", "tall"});
    profileStyleBox = new QComboBox(profileTab);
    profileStyleBox->addItems({"casual", "formal", "trendy", "classic", "smart-casual"});

    QPushButton *saveProfileBtn = new QPushButton("Save Profile", profileTab);
    profileForm->addRow("Age", ageSpin);
    profileForm->addRow("Skin Tone", skinToneBox);
    profileForm->addRow("Height Category", heightBox);
    profileForm->addRow("Preferred Style", profileStyleBox);
    profileForm->addRow(saveProfileBtn);

    connect(saveProfileBtn, &QPushButton::clicked, this, [this]() { saveProfile(); });

    QWidget *wardrobeTab = new QWidget(tabs);
    QVBoxLayout *wardrobeLayout = new QVBoxLayout(wardrobeTab);

    QGroupBox *addBox = new QGroupBox("Add Clothing Item", wardrobeTab);
    QFormLayout *addForm = new QFormLayout(addBox);
    nameEdit = new QLineEdit(addBox);
    typeBox = new QComboBox(addBox);
    typeBox->addItems({"top", "bottom", "outerwear", "footwear"});
    colorEdit = new QLineEdit(addBox);
    itemStyleBox = new QComboBox(addBox);
    itemStyleBox->addItems({"casual", "formal", "trendy", "classic", "smart-casual", "all"});
    occasionBox = new QComboBox(addBox);
    occasionBox->addItems({"casual", "office", "party", "all"});
    patternBox = new QComboBox(addBox);
    patternBox->addItems({"solid", "vertical", "horizontal", "printed"});
    lengthBox = new QComboBox(addBox);
    lengthBox->addItems({"short", "regular", "long", "ankle"});

    QPushButton *addBtn = new QPushButton("Add Item", addBox);
    addForm->addRow("Name", nameEdit);
    addForm->addRow("Type", typeBox);
    addForm->addRow("Color", colorEdit);
    addForm->addRow("Style", itemStyleBox);
    addForm->addRow("Occasion", occasionBox);
    addForm->addRow("Pattern", patternBox);
    addForm->addRow("Length", lengthBox);
    addForm->addRow(addBtn);
    connect(addBtn, &QPushButton::clicked, this, [this]() { addItem(); });

    table = new QTableWidget(wardrobeTab);
    table->setColumnCount(8);
    table->setHorizontalHeaderLabels({"ID", "Name", "Type", "Color", "Style", "Occasion", "Pattern", "Length"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHBoxLayout *removeLayout = new QHBoxLayout();
    removeIdSpin = new QSpinBox(wardrobeTab);
    removeIdSpin->setRange(1, 999999);
    QPushButton *removeBtn = new QPushButton("Remove by ID", wardrobeTab);
    removeLayout->addWidget(removeIdSpin);
    removeLayout->addWidget(removeBtn);
    removeLayout->addStretch();
    connect(removeBtn, &QPushButton::clicked, this, [this]() { removeItem(); });

    wardrobeLayout->addWidget(addBox);
    wardrobeLayout->addWidget(table);
    wardrobeLayout->addLayout(removeLayout);

    QWidget *recTab = new QWidget(tabs);
    QVBoxLayout *recLayout = new QVBoxLayout(recTab);
    QFormLayout *recForm = new QFormLayout();
    recommendOccasionBox = new QComboBox(recTab);
    recommendOccasionBox->addItems({"", "casual", "office", "party"});
    recommendStyleBox = new QComboBox(recTab);
    recommendStyleBox->addItems({"", "casual", "formal", "trendy", "classic", "smart-casual"});
    recForm->addRow("Occasion (blank = any)", recommendOccasionBox);
    recForm->addRow("Style (blank = profile)", recommendStyleBox);

    QPushButton *recBtn = new QPushButton("Recommend Outfit", recTab);
    resultLabel = new QLabel("No recommendation yet.", recTab);
    resultLabel->setWordWrap(true);

    connect(recBtn, &QPushButton::clicked, this, [this]() { recommendOutfit(); });

    recLayout->addLayout(recForm);
    recLayout->addWidget(recBtn);
    recLayout->addWidget(resultLabel);
    recLayout->addStretch();

    tabs->addTab(profileTab, "User Profile");
    tabs->addTab(wardrobeTab, "Wardrobe");
    tabs->addTab(recTab, "Recommendations");

    rootLayout->addWidget(tabs);
    setCentralWidget(central);
}

void MainWindow::loadData() {
    UserProfile loadedProfile;
    if (fileManager.loadUserProfile(loadedProfile)) {
        userProfile = loadedProfile;
    }

    wardrobeManager = WardrobeManager(fileManager.loadWardrobe());

    ageSpin->setValue(userProfile.getAge() > 0 ? userProfile.getAge() : 20);
    skinToneBox->setCurrentText(fromStd(userProfile.getSkinTone()));
    heightBox->setCurrentText(fromStd(userProfile.getHeightCategory()));
    profileStyleBox->setCurrentText(fromStd(userProfile.getPreferredStyle()));

    refreshWardrobeTable();
}

void MainWindow::refreshWardrobeTable() {
    const auto &items = wardrobeManager.getItems();
    table->setRowCount(static_cast<int>(items.size()));

    for (int row = 0; row < static_cast<int>(items.size()); ++row) {
        const ClothingItem &item = items[static_cast<std::size_t>(row)];
        table->setItem(row, 0, new QTableWidgetItem(QString::number(item.getId())));
        table->setItem(row, 1, new QTableWidgetItem(fromStd(item.getName())));
        table->setItem(row, 2, new QTableWidgetItem(fromStd(item.getType())));
        table->setItem(row, 3, new QTableWidgetItem(fromStd(item.getColor())));
        table->setItem(row, 4, new QTableWidgetItem(fromStd(item.getStyle())));
        table->setItem(row, 5, new QTableWidgetItem(fromStd(item.getOccasion())));
        table->setItem(row, 6, new QTableWidgetItem(fromStd(item.getPattern())));
        table->setItem(row, 7, new QTableWidgetItem(fromStd(item.getLengthTag())));
    }
}

void MainWindow::saveProfile() {
    userProfile.setAge(ageSpin->value());
    userProfile.setSkinTone(toStd(skinToneBox->currentText()));
    userProfile.setHeightCategory(toStd(heightBox->currentText()));
    userProfile.setPreferredStyle(toStd(profileStyleBox->currentText()));

    if (fileManager.saveUserProfile(userProfile)) {
        QMessageBox::information(this, "Saved", "User profile saved successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Could not save user profile.");
    }
}

void MainWindow::addItem() {
    if (nameEdit->text().trimmed().isEmpty() || colorEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Missing Data", "Name and color are required.");
        return;
    }

    wardrobeManager.addItem(toStd(nameEdit->text()),
                            toStd(typeBox->currentText()),
                            toStd(colorEdit->text()),
                            toStd(itemStyleBox->currentText()),
                            toStd(occasionBox->currentText()),
                            toStd(patternBox->currentText()),
                            toStd(lengthBox->currentText()));

    if (!fileManager.saveWardrobe(wardrobeManager.getItems())) {
        QMessageBox::warning(this, "Error", "Item added but could not save data to file.");
    }

    nameEdit->clear();
    colorEdit->clear();
    refreshWardrobeTable();
}

void MainWindow::removeItem() {
    const int id = removeIdSpin->value();
    if (!wardrobeManager.removeItem(id)) {
        QMessageBox::information(this, "Not Found", "No item found with that ID.");
        return;
    }

    if (!fileManager.saveWardrobe(wardrobeManager.getItems())) {
        QMessageBox::warning(this, "Error", "Item removed but could not save file.");
    }

    refreshWardrobeTable();
}

void MainWindow::recommendOutfit() {
    OutfitRecommendation rec = recommendationEngine.recommend(userProfile,
                                                              wardrobeManager.getItems(),
                                                              toStd(recommendOccasionBox->currentText()),
                                                              toStd(recommendStyleBox->currentText()));

    if (!rec.found) {
        resultLabel->setText(fromStd(rec.reason));
        return;
    }

    const QString text = QString("Top: %1 (%2, %3)\nBottom: %4 (%5, %6)\nScore: %7\nWhy: %8")
                             .arg(fromStd(rec.top.getName()))
                             .arg(fromStd(rec.top.getColor()))
                             .arg(fromStd(rec.top.getStyle()))
                             .arg(fromStd(rec.bottom.getName()))
                             .arg(fromStd(rec.bottom.getColor()))
                             .arg(fromStd(rec.bottom.getStyle()))
                             .arg(rec.score)
                             .arg(fromStd(rec.reason));

    resultLabel->setText(text);
}
