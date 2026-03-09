#ifndef WARDROBE_MANAGER_H
#define WARDROBE_MANAGER_H

#include <vector>

#include "ClothingItem.h"

class WardrobeManager {
private:
    std::vector<ClothingItem> items;
    int nextId;

public:
    WardrobeManager();
    explicit WardrobeManager(const std::vector<ClothingItem> &loadedItems);

    void addItem(const std::string &name,
                 const std::string &type,
                 const std::string &color,
                 const std::string &style,
                 const std::string &occasion,
                 const std::string &pattern,
                 const std::string &lengthTag);

    bool removeItem(int id);
    const std::vector<ClothingItem> &getItems() const;
    std::vector<ClothingItem> getItemsByType(const std::string &type) const;
};

#endif
