#ifndef PROJEKT_ZOO_VICTORYSTATE_H
#define PROJEKT_ZOO_VICTORYSTATE_H

#include "IGameState.h"
#include "Menu.h"

class Game;
class Renderer;

class VictoryState : public IGameState {
private:
    Menu* m_menu;

public:
    VictoryState(Game* game);
    ~VictoryState() override;

    void handleInput(Game* game, Action action) override;
    void addToBuffer(Renderer* renderer) override;
};

#endif //PROJEKT_ZOO_VICTORYSTATE_H