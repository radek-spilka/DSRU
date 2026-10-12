#include "VictoryState.h"

#include "Colors.h"
#include "CreditsCommand.h"
#include "Game.h"
#include "Renderer.h"
#include "NewGameCommand.h"
#include "ExitGameCommand.h"
#include "MainMenuCommand.h"
#include "MainMenuState.h"

VictoryState::VictoryState(Game* game) {
    std::vector<MenuItem> options;
    options.push_back({"New game", new NewGameCommand(game)});
    options.push_back({"Main menu", new MainMenuCommand (game)});
    options.push_back({"Exit game", new ExitGameCommand(game)});
    m_menu = new Menu(options);
}

VictoryState::~VictoryState() {
    if (m_menu) {
        for (auto& item : m_menu->getOptions()) {
            delete item.m_command;
        }
        delete m_menu;
    }
}

void VictoryState::handleInput(Game* game, Action action) {
    if (action == Action::moveUp) {
        m_menu->moveUp();
    } else if (action == Action::moveDown) {
        m_menu->moveDown();
    } else if (action == Action::interact) {
        m_menu->selectOption();
    }
}

void VictoryState::addToBuffer(Renderer* renderer) {
    if (!renderer || !m_menu) return;

    int oldCamX = renderer->getCameraX();
    int oldCamY = renderer->getCameraY();
    renderer->setCamera(0, 0);

    int consoleW = renderer->getConsoleWidth();
    int consoleH = renderer->getConsoleHeight();

    std::string title = "YOU WIN!";
    std::string subtitle = "All malfunctions repaired and the final module reached.";

    int titleX = (consoleW - static_cast<int>(title.length())) / 2;
    int subtitleX = (consoleW - static_cast<int>(subtitle.length())) / 2;

    renderer->drawString(titleX, consoleH / 2 - 4, title, Colors::getInstance()->VICTORY_TEXT);
    renderer->drawString(subtitleX, consoleH / 2 - 2, subtitle, Colors::getInstance()->NORMAL_TEXT);

    std::vector<MenuItem>& options = m_menu->getOptions();
    int selected = m_menu->getSelectedIndex();

    int currentY = consoleH / 2 + 1;
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
