//
// Created by PC on 15.05.2026.
//

#ifndef PROJEKT_ZOO_HACKINGGAMESTATE_H
#define PROJEKT_ZOO_HACKINGGAMESTATE_H


#include "IGameState.h"
#include "Drone.h"
#include "Enemy.h"
#include "Action.h"
#include "Item.h"


#include <string>
#include <chrono>

class HackingGameState : public IGameState {
public:
    HackingGameState(Game* game, Drone* drone, Enemy* enemy);
    virtual ~HackingGameState() = default;

    void handleInput(Game* game, Action action) override;
    void addToBuffer(Renderer* renderer) override;

    void update();

private:
    void generatePuzzle();
    void resolveFight(bool won);

    Game* m_game;
    Drone* m_drone;
    Enemy* m_enemy;

    int m_valA;
    int m_valB;
    int m_expectedResult;
    int m_options[3];
    int m_correctSlot;
    bool m_isVictory = false;
    bool m_hasStarted = false;

    std::string m_message;
    std::chrono::steady_clock::time_point m_startTime;
    int m_timeLimitMs;
};


#endif //PROJEKT_ZOO_HACKINGGAMESTATE_H