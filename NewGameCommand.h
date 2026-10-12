//
// Created by PC on 15.05.2026.
//

#ifndef PROJEKT_ZOO_NEWGAMECOMMAND_H
#define PROJEKT_ZOO_NEWGAMECOMMAND_H


#include "ICommand.h"
#include "Game.h"

class NewGameCommand : public ICommand {
private:
    Game* m_game;
public:
    NewGameCommand(Game* game);
    void execute() override;
};

#endif //PROJEKT_ZOO_NEWGAMECOMMAND_H