//
// Created by PC on 22.06.2026.
//

#ifndef PROJEKT_ZOO_MAINMENUCOMMAND_H
#define PROJEKT_ZOO_MAINMENUCOMMAND_H
#include "Game.h"
#include "ICommand.h"


class MainMenuCommand : public ICommand {
    Game* m_game;
    public:
    MainMenuCommand(Game* game);
    void execute() override;

};


#endif //PROJEKT_ZOO_MAINMENUCOMMAND_H