//
// Created by vojtech on 6/15/26.
//

#ifndef PROJEKT_ZOO_ITEMFACTORY_H
#define PROJEKT_ZOO_ITEMFACTORY_H

#include "Item.h"


class ItemFactory {
    public:
    ItemFactory();
    Item* generateRandom();
    Item* generateConcrete(ItemType itemType);
};


#endif //PROJEKT_ZOO_ITEMFACTORY_H
