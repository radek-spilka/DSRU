//
// Created by PC on 15.05.2026.
//

#ifndef PROJEKT_ZOO_RESUMEGAMECOMMAND_H
#define PROJEKT_ZOO_RESUMEGAMECOMMAND_H


#include "ICommand.h"
#include "Game.h"

class ResumeGameCommand : public ICommand {
private:
    Game* m_game;
public:
    ResumeGameCommand(Game* game);
    void execute() override;
};


#endif //PROJEKT_ZOO_RESUMEGAMECOMMAND_H