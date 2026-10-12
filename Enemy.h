//
// Created by vojtech on 6/15/26.
//

#ifndef PROJEKT_ZOO_ENEMY_H
#define PROJEKT_ZOO_ENEMY_H

#include "Hazard.h"

class Enemy : public Hazard {

    int m_hackDifficulty;
    int m_energyCost;

public:
    Enemy(int hackDifficulty, int energyCost);

    ~Enemy() override;

    int getHackDifficulty();
    int getEnergyCost();
    HazardType getHazardType() override;
    char getRenderIcon() override;
    Hazard* clone() override;
};


#endif //PROJEKT_ZOO_ENEMY_H
