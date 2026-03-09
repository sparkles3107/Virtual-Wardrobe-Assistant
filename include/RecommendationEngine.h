#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include <string>
#include <vector>

#include "ClothingItem.h"
#include "UserProfile.h"

struct OutfitRecommendation {
    bool found;
    int score;
    ClothingItem top;
    ClothingItem bottom;
    std::string reason;
};

class RecommendationEngine {
private:
    static std::string toLower(std::string text);
    static bool isOccasionMatch(const ClothingItem &item, const std::string &occasion);
    static bool isStyleMatch(const ClothingItem &item, const std::string &style);
    static int skinToneScore(const ClothingItem &item, const UserProfile &profile);
    static int heightScore(const ClothingItem &item, const UserProfile &profile);
    static int ageStyleScore(const ClothingItem &item, const UserProfile &profile);

public:
    OutfitRecommendation recommend(const UserProfile &profile,
                                   const std::vector<ClothingItem> &items,
                                   const std::string &occasion,
                                   const std::string &requestedStyle) const;
};

#endif
