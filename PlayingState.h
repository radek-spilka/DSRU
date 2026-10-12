//
// Created by PC on 15.05.2026.
//

#ifndef PROJEKT_ZOO_PLAYINGSTATE_H
#define PROJEKT_ZOO_PLAYINGSTATE_H

#include <string>

#include "Direction.h"
#include "IGameState.h"

#include <chrono>

class Game;
class Renderer;
class Module;
class Drone;

class PlayingState : public IGameState {
private:
    Game* m_game;
    std::string m_interactionMessage;
    bool m_isFacingLockedHatch = false;
    Direction m_lockedHatchDirection;
    std::string m_achievementPopup;
    std::chrono::steady_clock::time_point m_achievementPopupTime;

    void handleMovement(Direction dir);
    void handleInteraction();
    void handleInventoryInput(int pressedSlot);
    void evaluatePostMovement(Module* oldModule, Direction attemptedDir, bool attemptedMove);
    int getChipSlotIndex();

    void updateCamera(Renderer* renderer, Drone* drone, int consoleW, int consoleH);
    void renderModules(Renderer* renderer, int camX, int camY, int consoleW, int consoleH);
    void renderDrone(Renderer* renderer, Drone* drone);
    void renderUI(Renderer* renderer, Drone* drone, int camX, int camY, int consoleW, int consoleH);


public:
    explicit PlayingState(Game* game);
    ~PlayingState() override;

    void handleInput(Game* game, Action action) override;
    void addToBuffer(Renderer* renderer) override;
    void triggerAchievement(std::string id);
};

#endif //PROJEKT_ZOO_PLAYINGSTATE_H