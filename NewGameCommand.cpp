#include "NewGameCommand.h"
#include "Game.h"
#include "PlayingState.h"
#include "ProlougeState.h"

NewGameCommand::NewGameCommand(Game* game) : m_game(game) {}

void NewGameCommand::execute() {
    if (m_game) {
        m_game->initNewGame();
        m_game->changeState(new ProlougeState(m_game));
    }
}