//
// Created by PC on 19.06.2026.
//

#include "ProlougeState.h"

#include "Colors.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayingState.h"

ProlougeState::ProlougeState(Game* game)
    : m_displayedLength(0), m_totalDurationMs(10000) {

    m_fullText = "INITIATING BOOT...\n"
             "UNIT: DSRU-73\n"
             "SCHEMATICS: CORRUPTED\n"
             "DIRECTIVE: OVERRIDE MAIN CONTROL\n"
             "                                                  "
             "\nYou awaken in a flickering Airlock, a fragile maintenance\n"
             "drone (D) trapped aboard a colossal, deteriorating space\n"
             "station. With all internal schematics corrupted, the modular\n"
             "sectors ahead form a blind, shifting labyrinth of sealed\n"
             "hatches (H), lethal radiation leaks, and rogue security bots\n"
             "programmed to dismantle trespassers.\n"
             "\n"
             "The emergency lighting flickers. Something moves in the\n"
             "darkness beyond the airlock seal.\n"
             "\n"
             "AWAITING YOUR COMMAND...";


    m_startTime = std::chrono::steady_clock::now();
}

ProlougeState::~ProlougeState() = default;

void ProlougeState::handleInput(Game* game, Action action) {
    if (action != Action::none) {
        game->changeState(new PlayingState(game));
    }
}

void ProlougeState::addToBuffer(Renderer* renderer) {
    if (!renderer) return;

    int consoleW = renderer->getConsoleWidth();
    int consoleH = renderer->getConsoleHeight();

    renderer->setCamera(0, 0);

    auto now = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();

    if (elapsed >= m_totalDurationMs) {
        Game* gamePtr = nullptr;
        m_displayedLength = m_fullText.length();
    } else {
        float progress = static_cast<float>(elapsed) / m_totalDurationMs;
        m_displayedLength = static_cast<size_t>(progress * m_fullText.length());
        if (m_displayedLength > m_fullText.length()) {
            m_displayedLength = m_fullText.length();
        }
    }

    std::string displayedText = m_fullText.substr(0, m_displayedLength);

    int currentY = 2;
    int currentX = 2;
    int maxX = consoleW - 4;

    int lineCount = 0;

    for (char ch : displayedText) {
        if (ch == '\n') {
            currentY++;
            currentX = 2;
            lineCount++;
        } else {
            if (currentX >= maxX) {
                currentY++;
                currentX = 2;
            }

            std::string textColor;
            if (lineCount < 5) {
                textColor = Colors::getInstance()->PROLOGUE_COLOR; // Systémový text bude červeně (použij název ze svého Singletonu)
            } else {
                textColor = Colors::getInstance()->NORMAL_TEXT; // Příběh bude normální barvou
            }

            renderer->drawString(currentX, currentY, std::string(1, ch), textColor);
            currentX++;
        }

        if (currentY >= consoleH - 2) {
            break;
        }

        std::string skipText = "[Space] to skip";
        int skipX = (consoleW - static_cast<int>(skipText.length())) / 2;
        renderer->drawString(skipX, consoleH - 2, skipText, Colors::getInstance()->NORMAL_TEXT);
    }
}