//
// Created by vojtech on 6/15/26.
//

#include "Malfunction.h"

#include <iostream>
#include <ostream>

Malfunction::Malfunction() {
}

Malfunction::~Malfunction() {
}

HazardType Malfunction::getHazardType() {
    return HazardType::Malfunction;
}

char Malfunction::getRenderIcon() {
    return '!';
}

Hazard* Malfunction::clone() {
    return new Malfunction();
}
