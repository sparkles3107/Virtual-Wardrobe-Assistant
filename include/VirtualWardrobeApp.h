#ifndef VIRTUAL_WARDROBE_APP_H
#define VIRTUAL_WARDROBE_APP_H

#include "FileManager.h"
#include "RecommendationEngine.h"
#include "UserProfile.h"
#include "WardrobeManager.h"

class VirtualWardrobeApp {
private:
    FileManager fileManager;
    WardrobeManager wardrobeManager;
    RecommendationEngine recommendationEngine;
    UserProfile userProfile;

    static int readInt(const std::string &prompt);
    static std::string readLine(const std::string &prompt);
    static void printItemRow(const ClothingItem &item);

    void upsertUserProfile();
    void addClothingItem();
    void removeClothingItem();
    void listClothingItems() const;
    void suggestOutfit() const;

public:
    VirtualWardrobeApp(const std::string &wardrobeFile, const std::string &profileFile);
    void run();
};

#endif
