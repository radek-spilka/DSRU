//
// Created by PC on 15.05.2026.
//

#ifndef PROJEKT_ZOO_MAINMENUSTATE_H
#define PROJEKT_ZOO_MAINMENUSTATE_H
#include "IGameState.h"
#include "Menu.h"

class Game;
class Renderer;

class MainMenuState : public IGameState {
private:
    Menu* m_menu;

public:
    MainMenuState(Game* game);
    ~MainMenuState() override;

    void handleInput(Game* game, Action action) override;
    void addToBuffer(Renderer* renderer) override;
};


#endif //PROJEKT_ZOO_MAINMENUSTATE_H