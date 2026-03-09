#include "VirtualWardrobeApp.h"

#include <iomanip>
#include <iostream>
#include <limits>

VirtualWardrobeApp::VirtualWardrobeApp(const std::string &wardrobeFile, const std::string &profileFile)
    : fileManager(wardrobeFile, profileFile),
      wardrobeManager(fileManager.loadWardrobe()),
      userProfile() {
    fileManager.loadUserProfile(userProfile);
}

int VirtualWardrobeApp::readInt(const std::string &prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a number.\n";
    }
}

std::string VirtualWardrobeApp::readLine(const std::string &prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void VirtualWardrobeApp::printItemRow(const ClothingItem &item) {
    std::cout << std::left << std::setw(5) << item.getId() << std::setw(18) << item.getName() << std::setw(10)
              << item.getType() << std::setw(12) << item.getColor() << std::setw(14) << item.getStyle()
              << std::setw(12) << item.getOccasion() << std::setw(10) << item.getPattern() << item.getLengthTag()
              << "\n";
}

void VirtualWardrobeApp::upsertUserProfile() {
    int age = readInt("Age: ");
    std::string skinTone = readLine("Skin tone (warm/cool/neutral): ");
    std::string height = readLine("Height category (short/average/tall): ");
    std::string style = readLine("Preferred style (casual/formal/trendy/classic/smart-casual): ");

    userProfile.setAge(age);
    userProfile.setSkinTone(skinTone);
    userProfile.setHeightCategory(height);
    userProfile.setPreferredStyle(style);

    if (fileManager.saveUserProfile(userProfile)) {
        std::cout << "Profile saved.\n";
    } else {
        std::cout << "Failed to save profile.\n";
    }
}

void VirtualWardrobeApp::addClothingItem() {
    std::string name = readLine("Name: ");
    std::string type = readLine("Type (top/bottom/outerwear/footwear): ");
    std::string color = readLine("Color: ");
    std::string style = readLine("Style (formal/casual/trendy/classic/smart-casual): ");
    std::string occasion = readLine("Occasion (party/casual/office/all): ");
    std::string pattern = readLine("Pattern (solid/vertical/horizontal/printed): ");
    std::string lengthTag = readLine("Length tag (short/regular/long/ankle): ");

    wardrobeManager.addItem(name, type, color, style, occasion, pattern, lengthTag);

    if (fileManager.saveWardrobe(wardrobeManager.getItems())) {
        std::cout << "Item added and saved.\n";
    } else {
        std::cout << "Item added, but save failed.\n";
    }
}

void VirtualWardrobeApp::removeClothingItem() {
    int id = readInt("Enter item ID to remove: ");

    if (!wardrobeManager.removeItem(id)) {
        std::cout << "Item not found.\n";
        return;
    }

    if (fileManager.saveWardrobe(wardrobeManager.getItems())) {
        std::cout << "Item removed and saved.\n";
    } else {
        std::cout << "Item removed, but save failed.\n";
    }
}

void VirtualWardrobeApp::listClothingItems() const {
    const auto &items = wardrobeManager.getItems();
    if (items.empty()) {
        std::cout << "No items in wardrobe yet.\n";
        return;
    }

    std::cout << "\n------------------------ Wardrobe ------------------------\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(18) << "Name" << std::setw(10) << "Type"
              << std::setw(12) << "Color" << std::setw(14) << "Style" << std::setw(12) << "Occasion"
              << std::setw(10) << "Pattern" << "Length\n";
    std::cout << "----------------------------------------------------------\n";

    for (const auto &item : items) {
        printItemRow(item);
    }
}

void VirtualWardrobeApp::suggestOutfit() const {
    std::string occasion = readLine("Occasion for outfit (party/casual/office, blank for any): ");
    std::string style = readLine("Preferred style (blank uses profile style): ");

    OutfitRecommendation rec = recommendationEngine.recommend(userProfile, wardrobeManager.getItems(), occasion, style);

    if (!rec.found) {
        std::cout << rec.reason << "\n";
        return;
    }

    std::cout << "\nBest Outfit Recommendation\n";
    std::cout << "Top    : " << rec.top.getName() << " (" << rec.top.getColor() << ", " << rec.top.getStyle() << ")\n";
    std::cout << "Bottom : " << rec.bottom.getName() << " (" << rec.bottom.getColor() << ", " << rec.bottom.getStyle() << ")\n";
    std::cout << "Score  : " << rec.score << "\n";
    std::cout << "Reason : " << rec.reason << "\n";
}

void VirtualWardrobeApp::run() {
    while (true) {
        std::cout << "\n===== Virtual Wardrobe Assistant =====\n";
        std::cout << "1. Create/Update User Profile\n";
        std::cout << "2. Add Clothing Item\n";
        std::cout << "3. Remove Clothing Item\n";
        std::cout << "4. View Wardrobe\n";
        std::cout << "5. Recommend Outfit\n";
        std::cout << "6. Exit\n";

        int choice = readInt("Choose an option: ");

        if (choice == 1) {
            upsertUserProfile();
        } else if (choice == 2) {
            addClothingItem();
        } else if (choice == 3) {
            removeClothingItem();
        } else if (choice == 4) {
            listClothingItems();
        } else if (choice == 5) {
            suggestOutfit();
        } else if (choice == 6) {
            std::cout << "Exiting application.\n";
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}
