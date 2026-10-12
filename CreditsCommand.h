//
// Created by Radek on 19.06.2026.
//

#ifndef PROJEKT_ZOO_CREDITSCOMMAND_H
#define PROJEKT_ZOO_CREDITSCOMMAND_H
#include "Game.h"
#include "ICommand.h"


class CreditsCommand : public ICommand{
    Game * m_game;
public:
    CreditsCommand(Game * game);
    void execute() override;

};


#endif //PROJEKT_ZOO_CREDITSCOMMAND_H
