#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>

#include "ClothingItem.h"
#include "UserProfile.h"

class FileManager {
private:
    std::string wardrobeFile;
    std::string profileFile;

public:
    FileManager(const std::string &wardrobeFile, const std::string &profileFile);

    std::vector<ClothingItem> loadWardrobe() const;
    bool saveWardrobe(const std::vector<ClothingItem> &items) const;

    bool loadUserProfile(UserProfile &profile) const;
    bool saveUserProfile(const UserProfile &profile) const;
};

#endif                                                                 
