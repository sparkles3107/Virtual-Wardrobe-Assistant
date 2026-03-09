#include "RecommendationEngine.h"

#include <algorithm>
#include <climits>
#include <sstream>
#include <unordered_set>

std::string RecommendationEngine::toLower(std::string text) {
    for (char &c : text) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return text;
}

bool RecommendationEngine::isOccasionMatch(const ClothingItem &item, const std::string &occasion) {
    const std::string itemOccasion = toLower(item.getOccasion());
    const std::string expected = toLower(occasion);

    return expected.empty() || itemOccasion == expected || itemOccasion == "all";
}

bool RecommendationEngine::isStyleMatch(const ClothingItem &item, const std::string &style) {
    const std::string itemStyle = toLower(item.getStyle());
    const std::string expected = toLower(style);

    return expected.empty() || itemStyle == expected || itemStyle == "all";
}

int RecommendationEngine::skinToneScore(const ClothingItem &item, const UserProfile &profile) {
    const std::string tone = toLower(profile.getSkinTone());
    const std::string color = toLower(item.getColor());

    static const std::unordered_set<std::string> warmColors = {
        "beige", "brown", "mustard", "olive", "coral", "orange", "maroon", "cream"};
    static const std::unordered_set<std::string> coolColors = {
        "blue", "navy", "emerald", "gray", "black", "white", "pink", "purple"};

    if (tone == "warm") {
        return warmColors.count(color) ? 3 : 0;
    }
    if (tone == "cool") {
        return coolColors.count(color) ? 3 : 0;
    }
    return (warmColors.count(color) || coolColors.count(color)) ? 2 : 1;
}

int RecommendationEngine::heightScore(const ClothingItem &item, const UserProfile &profile) {
    const std::string height = toLower(profile.getHeightCategory());
    const std::string pattern = toLower(item.getPattern());
    const std::string length = toLower(item.getLengthTag());
    const std::string type = toLower(item.getType());

    int score = 0;
    if (height == "short") {
        if (pattern == "vertical") {
            score += 3;
        }
        if (type == "outerwear" && length == "long") {
            score -= 1;
        }
    } else if (height == "tall") {
        if (type == "outerwear" && length == "long") {
            score += 2;
        }
        if (length == "ankle" || length == "long") {
            score += 1;
        }
    } else {
        if (length == "regular") {
            score += 1;
        }
    }

    return score;
}

int RecommendationEngine::ageStyleScore(const ClothingItem &item, const UserProfile &profile) {
    const int age = profile.getAge();
    const std::string style = toLower(item.getStyle());

    if (age <= 22 && (style == "trendy" || style == "casual")) {
        return 2;
    }
    if (age >= 23 && age <= 35 && (style == "smart-casual" || style == "formal" || style == "casual")) {
        return 2;
    }
    if (age > 35 && (style == "formal" || style == "classic" || style == "smart-casual")) {
        return 2;
    }
    return 0;
}

OutfitRecommendation RecommendationEngine::recommend(const UserProfile &profile,
                                                     const std::vector<ClothingItem> &items,
                                                     const std::string &occasion,
                                                     const std::string &requestedStyle) const {
    OutfitRecommendation best{};
    best.found = false;
    best.score = INT_MIN;

    std::vector<ClothingItem> tops;
    std::vector<ClothingItem> bottoms;

    for (const auto &item : items) {
        const std::string type = toLower(item.getType());
        if (type == "top") {
            tops.push_back(item);
        } else if (type == "bottom") {
            bottoms.push_back(item);
        }
    }

    const std::string effectiveStyle = requestedStyle.empty() ? profile.getPreferredStyle() : requestedStyle;

    for (const auto &top : tops) {
        for (const auto &bottom : bottoms) {
            int score = 0;
            std::ostringstream reason;

            if (isOccasionMatch(top, occasion) && isOccasionMatch(bottom, occasion)) {
                score += 6;
                reason << "occasion matched; ";
            }

            if (isStyleMatch(top, effectiveStyle) && isStyleMatch(bottom, effectiveStyle)) {
                score += 6;
                reason << "style matched; ";
            }

            score += skinToneScore(top, profile) + skinToneScore(bottom, profile);
            score += heightScore(top, profile) + heightScore(bottom, profile);
            score += ageStyleScore(top, profile) + ageStyleScore(bottom, profile);

            if (top.getColor() != bottom.getColor()) {
                score += 1;
            }

            if (score > best.score) {
                best.found = true;
                best.score = score;
                best.top = top;
                best.bottom = bottom;
                best.reason = reason.str();
            }
        }
    }

    if (!best.found) {
        best.score = 0;
        best.reason = "Not enough wardrobe items. Add at least one top and one bottom.";
    }

    return best;
}
