//
// Created by Radek on 21.06.2026.
//

#ifndef PROJEKT_ZOO_ACHIEVEMENTSCOMMAND_H
#define PROJEKT_ZOO_ACHIEVEMENTSCOMMAND_H
#include "ICommand.h"
#include "Game.h"

class AchievementsCommand : public ICommand{
    Game * m_game;

public:
    AchievementsCommand(Game * game);
    void execute() override;
};


#endif //PROJEKT_ZOO_ACHIEVEMENTSCOMMAND_H
