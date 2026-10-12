//
// Created by vojtech on 5/11/26.
//



#include "Item.h"

#include <iostream>
#include <ostream>

Item::Item(ItemType itemType, char renderIcon) : m_itemType(itemType), m_renderIcon(renderIcon) {
}

ItemType Item::getItemType() {
    return m_itemType;
}

std::string Item::getItemTypeName() {
    switch (m_itemType) {
        case ItemType::DecodingChip: return "Decoding chip";
        case ItemType::Component: return "Component";
        case ItemType::Battery: return "Battery";
    }
}

char Item::getRenderIcon() {
    return m_renderIcon;
}

Item* Item::clone() const {
    return new Item(m_itemType, m_renderIcon);
}


