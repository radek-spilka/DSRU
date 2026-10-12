//
// Created by PC on 19.06.2026.
//

#ifndef PROJEKT_ZOO_PROLOGUESTATE_H
#define PROJEKT_ZOO_PROLOGUESTATE_H

#include "IGameState.h"
#include <string>
#include <chrono>

class Game;
class Renderer;

class ProlougeState : public IGameState {
private:
    std::string m_fullText;
    size_t m_displayedLength;
    std::chrono::steady_clock::time_point m_startTime;
    int m_totalDurationMs;

public:
    ProlougeState(Game* game);
    ~ProlougeState() override;

    void handleInput(Game* game, Action action) override;
    void addToBuffer(Renderer* renderer) override;
};

#endif //PROJEKT_ZOO_PROLOGUESTATE_H
