#ifndef CLOTHING_ITEM_H
#define CLOTHING_ITEM_H

#include <string>

class ClothingItem {
private:
    int id;
    std::string name;
    std::string type;
    std::string color;
    std::string style;
    std::string occasion;
    std::string pattern;
    std::string lengthTag;

public:
    ClothingItem();
    ClothingItem(int id,
                 const std::string &name,
                 const std::string &type,
                 const std::string &color,
                 const std::string &style,
                 const std::string &occasion,
                 const std::string &pattern,
                 const std::string &lengthTag);

    int getId() const;
    const std::string &getName() const;
    const std::string &getType() const;
    const std::string &getColor() const;
    const std::string &getStyle() const;
    const std::string &getOccasion() const;
    const std::string &getPattern() const;
    const std::string &getLengthTag() const;

    std::string serialize() const;
    static bool deserialize(const std::string &line, ClothingItem &item);
};

#endif
