#include "LoadGameCommand.h"
#include "PlayingState.h"

LoadGameCommand::LoadGameCommand(Game* game) : m_game(game) {}

void LoadGameCommand::execute() {
    if (m_game && m_game->hasSave()) {
        m_game->loadGame();
        m_game->changeState(new PlayingState(m_game));
    }
}