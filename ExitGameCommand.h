//
// Created by PC on 15.05.2026.
//

#ifndef PROJEKT_ZOO_EXITGAMECOMMAND_H
#define PROJEKT_ZOO_EXITGAMECOMMAND_H

#include "ICommand.h"
#include "Game.h"

class ExitGameCommand : public ICommand {
    Game* m_game;
public:
    ExitGameCommand(Game* game);
    void execute() override;
};

#endif //PROJEKT_ZOO_EXITGAMECOMMAND_H