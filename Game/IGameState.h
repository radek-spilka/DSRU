//
// Created by PC on 15.05.2026.
//
#pragma once
#ifndef PROJEKT_ZOO_IGAMESTATE_H
#define PROJEKT_ZOO_IGAMESTATE_H


#include "Action.h"

class Game;
class Renderer;

class IGameState {
public:
    virtual ~IGameState() = default;
    virtual void handleInput(Game* game, Action action) = 0;
    virtual void addToBuffer(Renderer* renderer) = 0;
};


#endif //PROJEKT_ZOO_IGAMESTATE_H