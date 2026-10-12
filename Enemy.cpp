//
// Created by vojtech on 6/15/26.
//

#include "Enemy.h"

Enemy::Enemy(int hackDifficulty, int energyCost){
    m_hackDifficulty = hackDifficulty;
    m_energyCost = energyCost;
}

Enemy::~Enemy() {
}

int Enemy::getHackDifficulty() {
    return m_hackDifficulty;
}

int Enemy::getEnergyCost() {
    return m_energyCost;
}

HazardType Enemy::getHazardType() {
    return HazardType::Enemy;
}

char Enemy::getRenderIcon() {
    return 'E';
}

Hazard* Enemy::clone() {
    return new Enemy(m_hackDifficulty, m_energyCost);
}
