#include "UserProfile.h"

#include <sstream>
#include <vector>

UserProfile::UserProfile() : age(0), skinTone("neutral"), heightCategory("average"), preferredStyle("casual") {}

UserProfile::UserProfile(int age,
                         const std::string &skinTone,
                         const std::string &heightCategory,
                         const std::string &preferredStyle)
    : age(age), skinTone(skinTone), heightCategory(heightCategory), preferredStyle(preferredStyle) {}

int UserProfile::getAge() const { return age; }
const std::string &UserProfile::getSkinTone() const { return skinTone; }
const std::string &UserProfile::getHeightCategory() const { return heightCategory; }
const std::string &UserProfile::getPreferredStyle() const { return preferredStyle; }

void UserProfile::setAge(int value) { age = value; }
void UserProfile::setSkinTone(const std::string &value) { skinTone = value; }
void UserProfile::setHeightCategory(const std::string &value) { heightCategory = value; }
void UserProfile::setPreferredStyle(const std::string &value) { preferredStyle = value; }

std::string UserProfile::serialize() const {
    std::ostringstream out;
    out << age << "|" << skinTone << "|" << heightCategory << "|" << preferredStyle;
    return out.str();
}

bool UserProfile::deserialize(const std::string &line, UserProfile &profile) {
    std::vector<std::string> parts;
    std::string token;
    std::stringstream ss(line);

    while (std::getline(ss, token, '|')) {
        parts.push_back(token);
    }

    if (parts.size() != 4) {
        return false;
    }

    try {
        profile = UserProfile(std::stoi(parts[0]), parts[1], parts[2], parts[3]);
        return true;
    } catch (...) {
        return false;
    }
}
