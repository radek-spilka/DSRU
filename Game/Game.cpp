//
// Created by PC on 15.05.2026.
//

#include "Game.h"
#include "MainMenuState.h"
#include "Input.h"
#include "Station.h"
#include "Position.h"
#include <windows.h> // Kvuli Sleep()

#include "Colors.h"
#include "Drone.h"
#include "Achievements.h"
#include <chrono>

Game::Game() {
    m_isRunning = true;
    m_renderer = new Renderer();
    m_currentState = new MainMenuState(this);
}

Game::~Game() {
    if (m_currentState) {
        delete m_currentState;
    }
    if (m_renderer) {
        delete m_renderer;
    }
    if (m_station) {
        delete m_station;
    }
    if (m_drone) {
        delete m_drone;
    }
    if (m_savedStation) {
        delete m_savedStation;
    }
    if (m_savedDrone) {
        delete m_savedDrone;
    }
    delete Input::getInstance();
    delete Colors::getInstance();
}

void Game::changeState(IGameState* newState) {
    if (m_currentState) {
        delete m_currentState;
    }
    m_currentState = newState;
}

void Game::exitGame() {
    m_isRunning = false;
}

void Game::initNewGame() {
    if (m_station) {
        delete m_station;
        m_station = nullptr;
    }
    if (m_drone) {
        delete m_drone;
        m_drone = nullptr;
    }

    int mapWidth = 50;
    int mapHeight = 50;
    m_station = new Station(mapWidth, mapHeight);
    m_enemyKilled = false;
    m_drone = new Drone(100, m_station->createNewModule(Position {mapWidth/2, mapHeight/2}, std::nullopt));
}

Station* Game::getStation() {
    return m_station;
}

Drone * Game::getDrone() {
    return m_drone;
}

void Game::triggerAchievementPopup(std::string id) {
    m_achievementPopup = id;
    m_achievementPopupTime = std::chrono::steady_clock::now();
}

void Game::run() {
    while (m_isRunning) {
        m_renderer->clearBuffer();

        if (m_currentState) {
            m_currentState->addToBuffer(m_renderer);
        }

        // --- GLOBAL ACHIEVEMENT POPUP LOGIC ---
        if (!m_achievementPopup.empty()) {
            auto now = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - m_achievementPopupTime).count();

            if (duration < 5) { // Popup svítí 5 vteřin
                std::string displayTitle = "";
                for (Achievement* ach : Achievements::getInstance()->getAchievements()) {
                    if (ach->id == m_achievementPopup) {
                        displayTitle = ach->title;
                        break;
                    }
                }

                std::string displayText = " " + displayTitle + " ";
                int w = static_cast<int>(displayText.length()) + 2;
                int h = 3;

                int consoleW = m_renderer->getConsoleWidth();
                int consoleH = m_renderer->getConsoleHeight();

                // Přičteme kameru, aby se popup správně pozicoval i když se obraz posouvá
                int camX = m_renderer->getCameraX();
                int camY = m_renderer->getCameraY();

                int popupX = camX + (consoleW - w) / 2;
                int startY = camY + consoleH - 4; // Umístění kousek od spodního okraje

                m_renderer->drawFrame(popupX, startY, w, h);
                m_renderer->drawString(popupX + 1, startY + 1, displayText, Colors::getInstance()->DSRD_LOGO);
            } else {
                m_achievementPopup.clear();
            }
        }
        // --------------------------------------

        m_renderer->renderToConsole();

        Action action = Input::getInstance()->getAction();

        if (m_currentState && action != Action::none) {
            m_currentState->handleInput(this, action);
        }

        Sleep(50);
    }
}

void Game::saveGame() {
    if (!m_station || !m_drone) return;

    if (m_savedStation) {
        delete m_savedStation;
        m_savedStation = nullptr;
    }
    if (m_savedDrone) {
        delete m_savedDrone;
        m_savedDrone = nullptr;
    }

    m_savedStation = new Station(*m_station);
    m_savedDrone = new Drone(*m_drone, m_savedStation);
}

void Game::loadGame() {
    if (!m_savedStation || !m_savedDrone) return;

    if (m_station) {
        delete m_station;
        m_station = nullptr;
    }
    if (m_drone) {
        delete m_drone;
        m_drone = nullptr;
    }

    m_station = new Station(*m_savedStation);
    m_drone = new Drone(*m_savedDrone, m_station);
}

bool Game::hasSave() {
    return m_savedStation != nullptr && m_savedDrone != nullptr;
}

void Game::markCheatsUsed() {
    m_cheatsUsed=true;
}
