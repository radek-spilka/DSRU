//
// Created by Radek on 19.06.2026.
//

#include "CreditsCommand.h"
#include "Game.h"
#include "CreditsState.h"

CreditsCommand::CreditsCommand(Game *game) {
    m_game = game;
}

void CreditsCommand::execute() {
    if (m_game) {
        m_game->changeState(new CreditsState(m_game));
    }
}
