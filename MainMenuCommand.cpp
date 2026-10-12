//
// Created by PC on 22.06.2026.
//

#include "MainMenuCommand.h"

#include "MainMenuState.h"

MainMenuCommand::MainMenuCommand(Game *game): m_game(game) {}

void MainMenuCommand::execute() {
    m_game->changeState(new MainMenuState(m_game));
}
