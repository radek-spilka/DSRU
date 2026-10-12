#include "MainMenuState.h"

#include "AchievementsCommand.h"
#include "AchievementsState.h"
#include "CreditsCommand.h"
#include "NewGameCommand.h"
#include "ResumeGameCommand.h"
#include "ExitGameCommand.h"
#include "Renderer.h"
#include "Game.h"

#include "Colors.h"
#include "Drone.h"
#include "LoadGameCommand.h"
#include "SaveGameCommand.h"

MainMenuState::MainMenuState(Game* game) {
    std::vector<MenuItem> options;

    if (game->getStation() != nullptr and !game->getDrone()->getOccupiedModule()->getIsFinal()) {
        options.push_back({"Resume game", new ResumeGameCommand(game)});
        options.push_back({"Save game", new SaveGameCommand(game)});
        if (game->hasSave()) {
            options.push_back({"Load game", new LoadGameCommand(game)});
        }
        options.push_back({"New game", new NewGameCommand(game)});
        options.push_back({"EXIT", new ExitGameCommand(game)});
    } else {
        options.push_back({"New game", new NewGameCommand(game)});
        options.push_back({"EXIT", new ExitGameCommand(game)});
        if (game->hasSave()) {
            options.push_back({"Load game", new LoadGameCommand(game)});
        }
    }

    options.push_back({"Achievements", new AchievementsCommand(game)});
    options.push_back({"Credits", new CreditsCommand(game)});

    m_menu = new Menu(options);
}

MainMenuState::~MainMenuState() {
    if (m_menu) {
        for (auto& item : m_menu->getOptions()) {
            delete item.m_command;
        }
        delete m_menu;
    }
}

void MainMenuState::handleInput(Game* game, Action action) {
    if (action == Action::moveUp) {
        m_menu->moveUp();
    } else if (action == Action::moveDown) {
        m_menu->moveDown();
    } else if (action == Action::interact) {
        m_menu->selectOption();
    }
}

void MainMenuState::addToBuffer(Renderer* renderer) {
    if (!renderer || !m_menu) return;

    // Uložit aktuální kameru hry
    int oldCamX = renderer->getCameraX();
    int oldCamY = renderer->getCameraY();

    renderer->setCamera(0, 0);

    int consoleW = renderer->getConsoleWidth();
    int consoleH = renderer->getConsoleHeight();

    std::vector<std::string> logo = {
        " _____   _____ _____  _    _ ",
        "|  __ \\ / ____|  __ \\| |  | |",
        "| |  | | (___ | |__) | |  | |",
        "| |  | |\\___ \\|  _  /| |  | |",
        "| |__| |____) | | \\ \\| |__| |",
        "|_____/\\_____/|_|  \\_\\\\____/ ",
        "                             ",
        "  Deep Space Repair Unit     "
    };

    auto& options = m_menu->getOptions();
    int selected = m_menu->getSelectedIndex();

    int logoHeight = logo.size();
    int optionsHeight = options.size() * 2 + 1;
    int totalHeight = logoHeight + 2 + optionsHeight;

    int currentY = (consoleH - totalHeight) / 2;
    if (currentY < 1) currentY = 1;

    for (const auto& line : logo) {
        int x = (consoleW - line.length()) / 2;
        renderer->drawString(x, currentY++, line, Colors::getInstance()->DSRD_LOGO);
    }

    currentY += 2;

    int frameW = 40;
    int frameX = (consoleW - frameW) / 2;
    renderer->drawFrame(frameX, currentY - 1, frameW, optionsHeight);

    for (size_t i = 0; i < options.size(); i++) {
        std::string text;
        if (static_cast<int>(i) == selected) {
            text = "  > [ " + options[i].m_label + " ] <  ";
        } else {
            text = "      " + options[i].m_label + "      ";
        }

        int textX = (consoleW - text.length()) / 2;
        if (text.find('<') != std::string::npos) {
            renderer->drawString(textX, currentY, text, Colors::getInstance()->MAIN_MENU_SELECTED_TEXT);
        } else {
            renderer->drawString(textX, currentY, text, Colors::getInstance()->MAIN_MENU_TEXT);
        }

        currentY += 2;
    }
    renderer->setCamera(oldCamX, oldCamY);
}