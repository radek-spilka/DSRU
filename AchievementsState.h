//
// Created by Radek on 21.06.2026.
//

#ifndef PROJEKT_ZOO_ACHIEVEMENTSSTATE_H
#define PROJEKT_ZOO_ACHIEVEMENTSSTATE_H
#include "Game.h"


class AchievementsState : public IGameState {
    int m_scrollOffset;
public:
    AchievementsState(Game* game);

    ~AchievementsState() override;

    void handleInput(Game *game, Action action) override;
    void addToBuffer(Renderer *renderer) override;
};


#endif //PROJEKT_ZOO_ACHIEVEMENTSSTATE_H
