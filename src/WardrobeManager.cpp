#include "WardrobeManager.h"

namespace {
std::string toLower(std::string value) {
    for (char &c : value) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return value;
}
}

WardrobeManager::WardrobeManager() : nextId(1) {}

WardrobeManager::WardrobeManager(const std::vector<ClothingItem> &loadedItems) : items(loadedItems), nextId(1) {
    for (const auto &item : items) {
        if (item.getId() >= nextId) {
            nextId = item.getId() + 1;
        }
    }
}

void WardrobeManager::addItem(const std::string &name,
                              const std::string &type,
                              const std::string &color,
                              const std::string &style,
                              const std::string &occasion,
                              const std::string &pattern,
                              const std::string &lengthTag) {
    items.emplace_back(nextId++, name, type, color, style, occasion, pattern, lengthTag);
}

bool WardrobeManager::removeItem(int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getId() == id) {
            items.erase(it);
            return true;
        }
    }
    return false;
}

const std::vector<ClothingItem> &WardrobeManager::getItems() const { return items; }

std::vector<ClothingItem> WardrobeManager::getItemsByType(const std::string &type) const {
    const std::string loweredType = toLower(type);
    std::vector<ClothingItem> result;

    for (const auto &item : items) {
        if (toLower(item.getType()) == loweredType) {
            result.push_back(item);
        }
    }

    return result;
}
