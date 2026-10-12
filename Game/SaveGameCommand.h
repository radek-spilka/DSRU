#ifndef PROJEKT_ZOO_SAVEGAMECOMMAND_H
#define PROJEKT_ZOO_SAVEGAMECOMMAND_H

#include "ICommand.h"
#include "Game.h"

class SaveGameCommand : public ICommand {
private:
    Game* m_game;
public:
    SaveGameCommand(Game* game);
    void execute() override;
};

#endif //PROJEKT_ZOO_SAVEGAMECOMMAND_H
