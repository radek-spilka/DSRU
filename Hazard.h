//
// Created by vojtech on 5/11/26.
//

#ifndef PROJEKT_ZOO_HAZARD_H
#define PROJEKT_ZOO_HAZARD_H

#include "HazardType.h"

class Hazard {

public:
    Hazard() = default;
    virtual ~Hazard() = default;
    virtual HazardType getHazardType() = 0;
    virtual char getRenderIcon() = 0;
    virtual Hazard* clone() = 0;
};


#endif //PROJEKT_ZOO_HAZARD_H
