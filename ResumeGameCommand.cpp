//
// Created by PC on 15.05.2026.
//

#include "ResumeGameCommand.h"
#include "PlayingState.h"

ResumeGameCommand::ResumeGameCommand(Game* game) : m_game(game) {}

void ResumeGameCommand::execute() {
    if (m_game) {
        m_game->changeState(new PlayingState(m_game));
    }
}