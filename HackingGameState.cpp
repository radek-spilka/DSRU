#include "HackingGameState.h"
#include "PlayingState.h"
#include <random>
#include <string>
#include <chrono>

#include "Achievements.h"
#include "Colors.h"
#include "Game.h"
#include "Renderer.h"
#include "Station.h"

HackingGameState::HackingGameState(Game* game, Drone* drone, Enemy* enemy)
    : m_game(game), m_drone(drone), m_enemy(enemy), m_message(">> HACKING MINIGAME <<") {

    m_timeLimitMs = 10000 - (m_enemy->getHackDifficulty() * 500);
    if (m_timeLimitMs < 3000) m_timeLimitMs = 3000;

    m_hasStarted = false;
    generatePuzzle();
}

void HackingGameState::update() {
    if (m_isVictory || !m_hasStarted) return;

    auto now = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();

    if (elapsed > m_timeLimitMs) {
        m_drone->drainEnergy(m_enemy->getEnergyCost());
        m_message = "TIMEOUT! Energy drained!";
        m_hasStarted = false;
        generatePuzzle();
    }
}

void HackingGameState::generatePuzzle() {
    m_valA = rand() % 20 + 1;
    m_valB = rand() % 20 + 1;
    m_expectedResult = m_valA + m_valB;

    m_correctSlot = rand() % 3;

    for (int i = 0; i < 3; ++i) {
        if (i == m_correctSlot) {
            m_options[i] = m_expectedResult;
        } else {
            int wrongVal;
            do {
                wrongVal = m_expectedResult + (rand() % 10 - 5);
            } while (wrongVal == m_expectedResult || wrongVal < 0);
            m_options[i] = wrongVal;
        }
    }
    m_startTime = std::chrono::steady_clock::now();
}

void HackingGameState::handleInput(Game* game, Action action) {
    if (m_isVictory) {
        m_game->changeState(new PlayingState(m_game));
        return;
    }

    if (action == Action::pause) {
        m_game->changeState(new PlayingState(m_game));
        return;
    }

    if (m_hasStarted) {
        auto now = std::chrono::steady_clock::now();
        int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();
        if (elapsed > m_timeLimitMs) {
            m_drone->drainEnergy(m_enemy->getEnergyCost());
            m_message = "TIMEOUT! Energy drained!";
            m_hasStarted = false;
            generatePuzzle();
            return;
        }
    }

    if (!m_hasStarted) {
        if (action == Action::interact) {
            m_hasStarted = true;
            m_startTime = std::chrono::steady_clock::now();
            m_message = "DECRYPTING...";
        }
        return;
    }

    int chosenSlot = -1;
    if (action == Action::num1) chosenSlot = 0;
    else if (action == Action::num2) chosenSlot = 1;
    else if (action == Action::num3) chosenSlot = 2;
    else return;

    if (chosenSlot == m_correctSlot) {
        m_isVictory = true;
        m_message = "SUCCESS! FIREWALL BYPASSED.";
        if (Achievements::getInstance()->unlockAchievement("HACKER")) {
            m_game->triggerAchievementPopup("HACKER");
        }
        m_game->markEnemyKilled();
        m_drone->getOccupiedModule()->removeHazard();
        m_drone->setInventoryItem(m_game->getStation()->getItemFactory()->generateConcrete(ItemType::Component));


    } else {
        m_drone->drainEnergy(m_enemy->getEnergyCost());
        m_message = "WRONG! Energy drained. Try again!";
        m_hasStarted = false;
        generatePuzzle();
    }
}

void HackingGameState::resolveFight(bool won) {
    if (won) {
        m_drone->getOccupiedModule()->removeHazard();
        m_drone->setInventoryItem(m_game->getStation()->getItemFactory()->generateConcrete(ItemType::Component));
        m_game->changeState(new PlayingState(m_game));
    }
}

void HackingGameState::addToBuffer(Renderer* renderer) {
    if (m_hasStarted && !m_isVictory) {
        auto now = std::chrono::steady_clock::now();
        int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();
        if (elapsed > m_timeLimitMs) {
            m_drone->drainEnergy(m_enemy->getEnergyCost());
            m_message = "TIMEOUT! Energy drained!";
            m_hasStarted = false;
            generatePuzzle();
        }
    }

    int w = renderer->getConsoleWidth();
    int h = renderer->getConsoleHeight();

    renderer->setCamera(0, 0);

    renderer->drawFrame(0, 0, w, h);

    std::string title = "";
    renderer->drawString((w - title.length()) / 2, 3, title, "\x1b[37m");

    if (!m_message.empty()) {
        renderer->drawString((w - m_message.length()) / 2, 5, m_message, Colors::getInstance()->NORMAL_TEXT);
    }

    if (m_isVictory) {
        std::string vicText1 = "ACCESS GRANTED";
        std::string vicText2 = "+ 1 Component";
        std::string promptText = "[ANY KEY] TO CONTINUE";

        renderer->drawString((w - vicText1.length()) / 2, h / 2 - 1, vicText1, Colors::getInstance()->VICTORY1_TEXT);
        renderer->drawString((w - vicText2.length()) / 2, h / 2 + 1, vicText2, "\x1b[37m");
        renderer->drawString((w - promptText.length()) / 2, h - 3, promptText, "\x1b[37m");
    }
    else {
        int energy = m_drone->getEnergy();
        if (energy > 100) energy = 100;

        int bars = energy / 5;
        if(bars > 20) bars = 20;
        if(bars < 0) bars = 0;

        std::string energyBar = "ENERGY: [";
        for(int i = 0; i < 20; ++i) {
            if(i < bars) energyBar += "#";
            else energyBar += "-";
        }
        energyBar += "] " + std::to_string(energy) + " / 100";

        renderer->drawString((w - energyBar.length()) / 2, 7, energyBar, Colors::getInstance()->ENERGY_COLOR);

        int remainingMs = m_timeLimitMs;

        if (m_hasStarted) {
            auto now = std::chrono::steady_clock::now();
            int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();
            remainingMs -= elapsed;
        }

        if (remainingMs < 0) remainingMs = 0;

        int remainingS = remainingMs / 1000;
        int remainingDec = (remainingMs % 1000) / 100;

        std::string timeStr = "TIME: 00:";
        if (remainingS < 10) timeStr += "0";
        timeStr += std::to_string(remainingS) + "." + std::to_string(remainingDec);

        renderer->drawString((w - timeStr.length()) / 2, h - 4, timeStr, Colors::getInstance()->TIME_TEXT);

        if (m_hasStarted) {
            std::string eq = std::to_string(m_valA) + " + " + std::to_string(m_valB) + " = ?";
            renderer->drawString((w - eq.length()) / 2, h / 2 - 2, eq, Colors::getInstance()->NORMAL_TEXT);

            std::string opt1 = "[1] " + std::to_string(m_options[0]);
            std::string opt2 = "[2] " + std::to_string(m_options[1]);
            std::string opt3 = "[3] " + std::to_string(m_options[2]);

            int spacing = 8;
            int totalOptLength = opt1.length() + opt2.length() + opt3.length();
            int startX = (w - (totalOptLength + spacing * 2)) / 2;

            renderer->drawString(startX, h / 2 + 2, opt1, Colors::getInstance()->OPTIONS_TEXT);
            renderer->drawString(startX + opt1.length() + spacing, h / 2 + 2, opt2, "\x1b[37m");
            renderer->drawString(startX + opt1.length() + spacing + opt2.length() + spacing, h / 2 + 2, opt3, "\x1b[37m");
        } else {
            std::string hiddenEq = "*** ENCRYPTED ***";
            renderer->drawString((w - hiddenEq.length()) / 2, h / 2 - 2, hiddenEq, "\x1b[37m");

            // Změněno podle toho, že v handleInput reaguješ na Action::interact
            std::string startInfo = "[INTERACT] TO START";
            renderer->drawString((w - startInfo.length()) / 2, h / 2 + 2, startInfo, "\x1b[37m");
        }
    }
}