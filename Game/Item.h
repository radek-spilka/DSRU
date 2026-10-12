//
// Created by vojtech on 5/11/26.
//

#ifndef PROJEKT_ZOO_ITEM_H
#define PROJEKT_ZOO_ITEM_H

#include "ItemType.h"

#include <string>

class Item {
    ItemType m_itemType;
    char m_renderIcon;

public:
    Item(ItemType itemType, char renderIcon);
    ItemType getItemType();
    std::string getItemTypeName();
    char getRenderIcon();
    Item* clone() const;
};


#endif //PROJEKT_ZOO_ITEM_H
