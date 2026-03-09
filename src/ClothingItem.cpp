#include "ClothingItem.h"

#include <sstream>
#include <vector>

ClothingItem::ClothingItem() : id(0) {}

ClothingItem::ClothingItem(int id,
                           const std::string &name,
                           const std::string &type,
                           const std::string &color,
                           const std::string &style,
                           const std::string &occasion,
                           const std::string &pattern,
                           const std::string &lengthTag)
    : id(id),
      name(name),
      type(type),
      color(color),
      style(style),
      occasion(occasion),
      pattern(pattern),
      lengthTag(lengthTag) {}

int ClothingItem::getId() const { return id; }
const std::string &ClothingItem::getName() const { return name; }
const std::string &ClothingItem::getType() const { return type; }
const std::string &ClothingItem::getColor() const { return color; }
const std::string &ClothingItem::getStyle() const { return style; }
const std::string &ClothingItem::getOccasion() const { return occasion; }
const std::string &ClothingItem::getPattern() const { return pattern; }
const std::string &ClothingItem::getLengthTag() const { return lengthTag; }

std::string ClothingItem::serialize() const {
    std::ostringstream out;
    out << id << "|" << name << "|" << type << "|" << color << "|" << style << "|" << occasion << "|"
        << pattern << "|" << lengthTag;
    return out.str();
}

bool ClothingItem::deserialize(const std::string &line, ClothingItem &item) {
    std::vector<std::string> parts;
    std::string token;
    std::stringstream ss(line);

    while (std::getline(ss, token, '|')) {
        parts.push_back(token);
    }

    if (parts.size() != 8) {
        return false;
    }

    try {
        item = ClothingItem(std::stoi(parts[0]), parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);
        return true;
    } catch (...) {
        return false;
    }
}
