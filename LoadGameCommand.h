//
// Created by PC on 20.06.2026.
//

#ifndef PROJEKT_ZOO_LOADGAMECOMMAND_H
#define PROJEKT_ZOO_LOADGAMECOMMAND_H
#include "Game.h"
#include "ICommand.h"


class LoadGameCommand : public ICommand {
    Game* m_game;
public:
    LoadGameCommand(Game* game);
    void execute() override;
};


#endif //PROJEKT_ZOO_LOADGAMECOMMAND_H