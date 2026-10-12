//
// Created by vojtech on 6/15/26.
//

#ifndef PROJEKT_ZOO_MALFUNCTION_H
#define PROJEKT_ZOO_MALFUNCTION_H

#include "Hazard.h"


class Malfunction : public Hazard {

public:
    Malfunction();
    ~Malfunction() override;

    HazardType getHazardType() override;
    char getRenderIcon() override;
    Hazard* clone() override;
};


#endif //PROJEKT_ZOO_MALFUNCTION_H
