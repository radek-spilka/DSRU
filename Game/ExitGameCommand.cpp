//
// Created by PC on 15.05.2026.
//

#include "ExitGameCommand.h"

ExitGameCommand::ExitGameCommand(Game* game) : m_game(game) {}

void ExitGameCommand::execute() {
    if (m_game) {
        m_game->exitGame();
    }
}