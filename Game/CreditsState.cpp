//
// Created by Radek on 19.06.2026.
//

#include "CreditsState.h"

#include "Game.h"
#include "Renderer.h"
#include "MainMenuState.h"
#include "Colors.h"


CreditsState::CreditsState(Game* game)
    : m_displayedLength(0), m_totalDurationMs(12000) {

    m_fullText = "[SYSTEM LOG: CREDITS...]\n"
                 "\n"
                 "@Radek Spilka                    \n"
                 "@Martin Gabriel                    \n"
                 "@Vojtech Zouhar                    \n"
                 "@Patrik Stefka                    \n"
                 "\n"
                 "Thank you for playing :)\n\n"
                 "...END OF TRANSMISSION.";

    m_startTime = std::chrono::steady_clock::now();
}

CreditsState::~CreditsState() = default;

void CreditsState::handleInput(Game* game, Action action) {
    if (action != Action::none) {
        game->changeState(new MainMenuState(game));
    }
}

void CreditsState::addToBuffer(Renderer* renderer) {
    if (!renderer) return;

    int consoleW = renderer->getConsoleWidth();
    int consoleH = renderer->getConsoleHeight();

    renderer->setCamera(0, 0);

    auto now = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();

    if (elapsed >= m_totalDurationMs) {
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
            if (lineCount == 0) {
                textColor = Colors::getInstance()->CREDITS_HEADER_TEXT;
            } else if (lineCount >= 2 && lineCount <= 5) {
                textColor = Colors::getInstance()->CREDITS_NAMES_TEXT;
            } else {
                textColor = Colors::getInstance()->NORMAL_TEXT;
            }

            renderer->drawString(currentX, currentY, std::string(1, ch), textColor);
            currentX++;
        }

        if (currentY >= consoleH - 2) {
            break;
        }
    }

    if (elapsed < m_totalDurationMs) {
        std::string skipText = "[SPACE to skip]";
        int skipX = (consoleW - static_cast<int>(skipText.length())) / 2;
        renderer->drawString(skipX, consoleH - 2, skipText, Colors::getInstance()->NORMAL_TEXT);
    } else {
        std::string doneText = "[Press any key to continue]";
        int doneX = (consoleW - static_cast<int>(doneText.length())) / 2;
        renderer->drawString(doneX, consoleH - 2, doneText, Colors::getInstance()->NORMAL_TEXT);
    }
}
