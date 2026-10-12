#include "SaveGameCommand.h"
#include "MainMenuState.h"
#include "PlayingState.h"

SaveGameCommand::SaveGameCommand(Game* game) : m_game(game) {}

void SaveGameCommand::execute() {
    if (m_game) {
        m_game->saveGame();
        m_game->changeState(new PlayingState(m_game));
    }
}
