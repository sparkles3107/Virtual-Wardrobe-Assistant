#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <string>

class UserProfile {
private:
    int age;
    std::string skinTone;
    std::string heightCategory;
    std::string preferredStyle;

public:
    UserProfile();
    UserProfile(int age,
                const std::string &skinTone,
                const std::string &heightCategory,
                const std::string &preferredStyle);

    int getAge() const;
    const std::string &getSkinTone() const;
    const std::string &getHeightCategory() const;
    const std::string &getPreferredStyle() const;

    void setAge(int value);
    void setSkinTone(const std::string &value);
    void setHeightCategory(const std::string &value);
    void setPreferredStyle(const std::string &value);

    std::string serialize() const;
    static bool deserialize(const std::string &line, UserProfile &profile);
};

#endif
