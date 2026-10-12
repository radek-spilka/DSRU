//
// Created by PC on 19.06.2026.
//

#ifndef PROJEKT_ZOO_GAMEOVERSTATE_H
#define PROJEKT_ZOO_GAMEOVERSTATE_H

#include "IGameState.h"
#include "Menu.h"

class Game;
class Renderer;

class GameOverState : public IGameState {
    Menu* m_menu;

public:
    GameOverState(Game* game);
    ~GameOverState() override;

    void handleInput(Game* game, Action action) override;
    void addToBuffer(Renderer* renderer) override;
};

#endif //PROJEKT_ZOO_GAMEOVERSTATE_H
