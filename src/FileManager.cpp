#include "FileManager.h"

#include <fstream>

FileManager::FileManager(const std::string &wardrobeFile, const std::string &profileFile)
    : wardrobeFile(wardrobeFile), profileFile(profileFile) {}

std::vector<ClothingItem> FileManager::loadWardrobe() const {
    std::vector<ClothingItem> items;
    std::ifstream file(wardrobeFile);
    if (!file.is_open()) {
        return items;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        ClothingItem item;
        if (ClothingItem::deserialize(line, item)) {
            items.push_back(item);
        }
    }

    return items;
}

bool FileManager::saveWardrobe(const std::vector<ClothingItem> &items) const {
    std::ofstream file(wardrobeFile, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }

    for (const auto &item : items) {
        file << item.serialize() << "\n";
    }

    return true;
}

bool FileManager::loadUserProfile(UserProfile &profile) const {
    std::ifstream file(profileFile);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    if (!std::getline(file, line)) {
        return false;
    }

    return UserProfile::deserialize(line, profile);
}

bool FileManager::saveUserProfile(const UserProfile &profile) const {
    std::ofstream file(profileFile, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }

    file << profile.serialize() << "\n";
    return true;
}
