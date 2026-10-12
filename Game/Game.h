//
// Created by PC on 15.05.2026.
//

#ifndef PROJEKT_ZOO_GAME_H
#define PROJEKT_ZOO_GAME_H


#include <chrono>

#include "IGameState.h"
#include "Renderer.h"


class Station;
class Drone;

class Game {
    IGameState* m_currentState;
    Renderer* m_renderer;
    Station* m_station = nullptr;
    Drone* m_drone = nullptr;


    Station* m_savedStation = nullptr;
    Drone* m_savedDrone = nullptr;
    bool m_enemyKilled=false;
    bool m_isRunning;
    std::string m_achievementPopup;
    std::chrono::time_point<std::chrono::steady_clock> m_achievementPopupTime;
    bool m_cheatsUsed = false;
public:
    Game();
    ~Game();

    void changeState(IGameState* newState);
    void triggerAchievementPopup(std::string id);
    void run();
    void exitGame();
    void initNewGame();

    void saveGame();
    void loadGame();
    bool hasSave();

    void markEnemyKilled() { m_enemyKilled = true; }
    bool isEnemyKilled() const { return m_enemyKilled; }
    void markCheatsUsed();

    Station* getStation();
    Drone* getDrone();
};


#endif //PROJEKT_ZOO_GAME_H