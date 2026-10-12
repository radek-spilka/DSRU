//
// Created by vojtech on 6/15/26.
//

#ifndef PROJEKT_ZOO_HAZARDFACTORY_H
#define PROJEKT_ZOO_HAZARDFACTORY_H


#include "Hazard.h"

class HazardFactory {
    int m_requiredMalfunctions;
    int m_alreadyGeneratedMalfunctions;
public:
    HazardFactory();
    Hazard* generate();
    int getRequiredMalfunctions();
    void repairedMalfunctions();
    int getAlreadyGeneratedMalfunctions();
    void setRequiredMalfunctions(int val);
    void setAlreadyGeneratedMalfunctions(int val);
};

#endif