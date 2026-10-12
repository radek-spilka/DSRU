//
// Created by Radek on 21.06.2026.
//

#include "AchievementsCommand.h"
#include "AchievementsState.h"

AchievementsCommand::AchievementsCommand(Game *game) {
    m_game = game;
}

void AchievementsCommand::execute() {
    if (m_game) {
        m_game->changeState(new AchievementsState(m_game));
    }
}
