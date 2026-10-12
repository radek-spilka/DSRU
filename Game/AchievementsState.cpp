#include "AchievementsState.h"
#include "MainMenuState.h"
#include "Game.h"
#include "Renderer.h"
#include "Colors.h"
#include "Achievements.h"

AchievementsState::AchievementsState(Game* game) : m_scrollOffset(0) {}

AchievementsState::~AchievementsState() = default;

void AchievementsState::handleInput(Game* game, Action action) {
    if (action == Action::pause || action == Action::interact) {
        game->changeState(new MainMenuState(game));
        return;
    }

    auto list = Achievements::getInstance()->getAchievements();
    int totalItems = static_cast<int>(list.size());
    int visibleItems = 3;

    if (action == Action::moveDown) {
        if (m_scrollOffset < totalItems - visibleItems) {
            m_scrollOffset++;
        }
    } else if (action == Action::moveUp) {
        if (m_scrollOffset > 0) {
            m_scrollOffset--;
        }
    } else if (action == Action::cheat) {
        Achievements::getInstance()->unlockAllAchievements();
    }
}

void AchievementsState::addToBuffer(Renderer* renderer) {
    if (!renderer) return;

    bool allOtherUnlocked = true;
    for (Achievement * achievement : Achievements::getInstance()->getAchievements()) {
        if ( ! achievement->unlocked and achievement->id != "NO_CHEATS") {
            allOtherUnlocked = false;
        }
    }
    if (allOtherUnlocked && !Achievements::getInstance()->cheatsUsed()) {
        for (Achievement * achievement : Achievements::getInstance()->getAchievements()) {
            if (achievement->id == "NO_CHEATS") {
                achievement->unlocked = true;
            }
        }
    }

    renderer->setCamera(0, 0);

    int consoleW = renderer->getConsoleWidth();
    int consoleH = renderer->getConsoleHeight();

    std::string title = "=== ACHIEVEMENTS ===";
    int titleX = (consoleW - static_cast<int>(title.length())) / 2;
    std::string titleColor;

    auto list = Achievements::getInstance()->getAchievements();
    int totalItems = static_cast<int>(list.size());

    int unlockedCount = 0;
    for (Achievement* ach : list) {
        if (ach->unlocked) {
            unlockedCount++;
        }
    }

    std::string progressText = "Unlocked: " + std::to_string(unlockedCount) + " / " + std::to_string(totalItems) + " ";
    std::string progressColor;

    if (unlockedCount == totalItems && totalItems > 0) {
        progressColor = Colors::getInstance()->ACHIEVEMENTS_UNLOCKED;
        titleColor = Colors::getInstance()->NORMAL_TEXT;
    } else {
        progressColor = Colors::getInstance()->INNER_WALL_COLOR;
        titleColor = Colors::getInstance()->DARK_NORMAL_TEXT;
    }

    int progressX = (consoleW - static_cast<int>(progressText.length())) / 2;
    renderer->drawString(progressX, 3, progressText, progressColor);
    renderer->drawString(titleX, 2, title, titleColor);

    renderer->drawFrame(4, 4, consoleW - 8, consoleH - 8);

    int visibleItems = 3;
    int startY = 6;
    int currentY = startY;
    int drawnCount = 0;

    for (int i = m_scrollOffset; i < totalItems && drawnCount < visibleItems; ++i) {
        Achievement* ach = list[i];

        if (currentY + ach->icon.size() > consoleH - 5) break;

        std::string iconColor = ach->unlocked ? Colors::getInstance()->ACHIEVEMENTS_UNLOCKED : Colors::getInstance()->ACHIEVEMENTS_LOCKED;
        std::string titleColor = ach->unlocked ? Colors::getInstance()->ACHIEVEMENTS_ICON : Colors::getInstance()->ACHIEVEMENTS_LOCKED;
        std::string descColor = ach->unlocked ? Colors::getInstance()->NORMAL_TEXT : Colors::getInstance()->ACHIEVEMENTS_LOCKED;

        int iconX = 16;

        for (size_t r = 0; r < ach->icon.size(); ++r) {
            std::string lineToDraw = ach->unlocked ? ach->icon[r] : " ??? ";
            renderer->drawString(iconX, currentY + r, lineToDraw, iconColor);
        }

        int textX = iconX + 8;

        renderer->drawString(textX, currentY, ach->title, titleColor);

        std::string desc = ach->unlocked ? ach->description : "???";
        renderer->drawString(textX, currentY + 1, desc, descColor);

        currentY += ach->icon.size() + 3;
        drawnCount++;
    }

    std::string navText = "[UP/DOWN] Scroll   [SPACE] Back";
    int navX = (consoleW - static_cast<int>(navText.length())) / 2;
    renderer->drawString(navX, consoleH - 2, navText, Colors::getInstance()->NORMAL_TEXT);
}
