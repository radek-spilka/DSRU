//
// Created by vojtech on 6/15/26.
//

#include "ItemFactory.h"

#include <cstdlib>

ItemFactory::ItemFactory() {

}

Item * ItemFactory::generateConcrete(ItemType itemType) {
    switch (itemType) {
        case ItemType::Battery:
            return new Item(ItemType::Battery, 'B');
        case ItemType::Component:
            return new Item(ItemType::Component, 'C');
        case ItemType::DecodingChip:
            return new Item(ItemType::DecodingChip, 'D');
    }
}

Item * ItemFactory::generateRandom() {
    int randomness = rand() % 100;

    if (randomness < 1) {
        return generateConcrete(ItemType::Component);
    }

    if (randomness < 45) {
        return generateConcrete(ItemType::DecodingChip);
    }

    else {
        return generateConcrete(ItemType::Battery);
    }
}
