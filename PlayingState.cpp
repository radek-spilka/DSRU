//
// Created by PC on 15.05.2026.
//

#include "PlayingState.h"

#include <map>
#include <string>
#include <vector>

#include "Action.h"
#include "Colors.h"
#include "Direction.h"
#include "Drone.h"
#include "Enemy.h"
#include "MainMenuState.h"
#include "Game.h"
#include "GameOverState.h"
#include "HackingGameState.h"
#include "Hatch.h"
#include "Renderer.h"
#include "Station.h"
#include "Module.h"
#include "Position.h"
#include "Radiation.h"
#include "VictoryState.h"
#include "Achievements.h"

namespace {
    // Render konstanty
    constexpr int MOD_W = 7;
    constexpr int MOD_H = 7;
    constexpr int SPACING_X = MOD_W - 1;
    constexpr int SPACING_Y = MOD_H - 1;
    constexpr int START_X = 6;
    constexpr int START_Y = 4;
}

PlayingState::PlayingState(Game* game) : m_game(game){}

PlayingState::~PlayingState() = default;

void PlayingState::handleInput(Game* game, Action action) {
    Module* oldModule = game->getDrone()->getOccupiedModule();
    bool attemptedMove = false;
    Direction attemptedDir;


    switch (action) {
        case Action::pause:
            game->changeState(new MainMenuState(game));
            return;
        case Action::moveUp:
            attemptedDir = Direction::North;
            handleMovement(attemptedDir);
            attemptedMove = true;
            break;
        case Action::moveDown:
            attemptedDir = Direction::South;
            handleMovement(attemptedDir);
            attemptedMove = true;
            break;
        case Action::moveRight:
            attemptedDir = Direction::East;
            handleMovement(attemptedDir);
            attemptedMove = true;
            break;
        case Action::moveLeft:
            attemptedDir = Direction::West;
            handleMovement(attemptedDir);
            attemptedMove = true;
            break;
        case Action::interact:
            handleInteraction();
            break;
        case Action::num1:
            handleInventoryInput(1);
            break;
        case Action::num2:
            handleInventoryInput(2);
            break;
        case Action::num3:
            handleInventoryInput(3);
            break;
        case Action::cheat:
            if (m_game and m_game->getStation() and m_game->getStation()->getFinalModule()!=nullptr) {
                m_game->getStation()->unlockFinalModule();
                m_interactionMessage = "CHEAT: All malfunctions repaired!";
                m_game->markCheatsUsed();
            }
            break;
        default:
            break;
    }

    evaluatePostMovement(oldModule, attemptedDir, attemptedMove);
}

void PlayingState::handleMovement(Direction dir) {
    m_interactionMessage.clear();
    m_isFacingLockedHatch = false;
    m_game->getStation()->tryToMoveDrone(m_game->getDrone(), dir);
}

void PlayingState::handleInteraction() {
    Module* currentModule = m_game->getDrone()->getOccupiedModule();
    if (m_game->getDrone()->getOccupiedModule()->getIsFinal()) {
        triggerAchievement("FIRST_WIN");
        if (!m_game->isEnemyKilled()) {
            triggerAchievement("PACIFIST");
        }
        m_game->changeState(new VictoryState(m_game));
        return;
    }
    if (currentModule->getHazard() != nullptr) {
        switch (currentModule->getHazard()->getHazardType()) {
            case HazardType::Enemy:
                m_interactionMessage = "Enemy, fight or die!";
                m_game->changeState(new HackingGameState(m_game, m_game->getDrone(), static_cast<Enemy *>(currentModule->getHazard())));
                break;
            case HazardType::Malfunction:
                m_interactionMessage = "Malfunction, needs to be repaired by Component.";
                break;
            case HazardType::Radiation:
                m_interactionMessage = "...RaDiatiOn...";
                break;
        }
    }
    else if (currentModule->getItem() != nullptr) {
        Item* item = currentModule->getItem();
        m_game->getDrone()->setInventoryItem(item);
        currentModule->removeItem();
        m_interactionMessage = "Got item! (" + item->getItemTypeName() +")";

        if (m_game->getDrone()->getInventoryItems().size() >= 10) {
            triggerAchievement("HOARDER");
        }
    }
    else {
        m_interactionMessage = "Nothing to interact with!";
    }
}

void PlayingState::handleInventoryInput(int pressedSlot) {
    std::map<ItemType, int> tempCounts;
    for (Item* item : m_game->getDrone()->getInventoryItems()) {
        if (item) tempCounts[item->getItemType()]++;
    }

    int currentSlot = 1;
    bool actionTaken = false;
    Module* currentModule = m_game->getDrone()->getOccupiedModule();

    for (const auto& pair : tempCounts) {
        if (currentSlot == pressedSlot) {
            ItemType selectedItem = pair.first;

            if (selectedItem == ItemType::DecodingChip) {
                if (m_isFacingLockedHatch) {
                    Position targetPos = currentModule->getPosition().getNewPosition(m_lockedHatchDirection);
                    Module* targetModule = m_game->getStation()->getModuleAt(targetPos);

                    if (targetModule != nullptr && targetModule->getIsFinal()) {
                        m_interactionMessage = "First, Repair MALFUNCTIONS!";
                        actionTaken = true;
                    }
                    else if (m_game->getDrone()->consumeItem(ItemType::DecodingChip)) {
                        m_game->getStation()->unlockHatchInDirection(currentModule, m_lockedHatchDirection);
                        m_interactionMessage = "Hatch unlocked!";
                        m_isFacingLockedHatch = false;
                        actionTaken = true;
                    }

                } else {
                    m_interactionMessage = "No locked hatch here.";
                    actionTaken = true;
                }
            }
            else if (selectedItem == ItemType::Component) {
                Hazard* hazard = currentModule->getHazard();
                if (hazard != nullptr && hazard->getHazardType() == HazardType::Malfunction) {
                    if (m_game->getDrone()->consumeItem(ItemType::Component)) {
                        currentModule->removeHazard();
                        m_interactionMessage = "Malfunction repaired!";
                        actionTaken = true;
                        m_game->getStation()->getHazardFactory()->repairedMalfunctions();
                        triggerAchievement("FIRST_FIX");
                        if (m_game->getStation()->getHazardFactory()->getRequiredMalfunctions() <= 0) {
                            m_interactionMessage = "All malfunctions successfully repaired!";
                            m_game->getStation()->unlockFinalModule();
                        }
                    }
                } else {
                    m_interactionMessage = "No malfunction to repair here.";
                    actionTaken = true;
                }
            }
            else if (selectedItem == ItemType::Battery) {
                int lastEnergy = m_game->getDrone()->getEnergy();
                if (m_game->getDrone()->consumeItem(ItemType::Battery)) {
                    int healAmount = rand() % (15 - 5 + 1) + 5;
                    m_game->getDrone()->addEnergy(healAmount);
                    triggerAchievement("FIRST_BATTERY");

                    if (lastEnergy == m_game->getDrone()->getEnergy()) {
                        m_interactionMessage = "Baterry consumed, health is already max!";
                    }
                    else m_interactionMessage = "Battery consumed! Energy +" + std::to_string(healAmount);
                    actionTaken = true;
                }
            }
            break;
        }
        currentSlot++;
    }

    if (!actionTaken && m_isFacingLockedHatch) {
        m_interactionMessage = "Wrong item!";
    }
}

int PlayingState::getChipSlotIndex() {
    std::map<ItemType, int> tempCounts;
    for (Item* item : m_game->getDrone()->getInventoryItems()) {
        if (item) tempCounts[item->getItemType()]++;
    }

    int currentSlot = 1;
    for (const auto& pair : tempCounts) {
        if (pair.first == ItemType::DecodingChip) {
            return currentSlot;
        }
        currentSlot++;
    }
    return -1;
}

void PlayingState::evaluatePostMovement(Module* oldModule, Direction attemptedDir, bool attemptedMove) {
    if (!attemptedMove) return;

    Module* newModule = m_game->getDrone()->getOccupiedModule();

    if (oldModule == newModule) {
        Hatch* hatch = oldModule->getHatchInDirection(attemptedDir);
        bool isLockedHatch = (hatch != nullptr && hatch->isLocked());

        Hazard* currentHazard = oldModule->getHazard();
        bool inRadiation = (currentHazard != nullptr && currentHazard->getRenderIcon() == 'R');

        int damage = 0;
        if (inRadiation) {
            damage = static_cast<Radiation*>(currentHazard)->getDamagePerSecond();
        }

        // míšo pokud tohle čteš, řekni proste phil nebo č jako čít (čteš)

        if (isLockedHatch) {
            m_isFacingLockedHatch = true;
            m_lockedHatchDirection = attemptedDir;

            int chipSlot = getChipSlotIndex();
            std::string radMsg = inRadiation ? " Energy dropping!" : "";

            if (m_game->getStation()->getModuleAt(oldModule->getPosition().getNewPosition(attemptedDir)) != nullptr and m_game->getStation()->getModuleAt(oldModule->getPosition().getNewPosition(attemptedDir))->getIsFinal()) {
                m_interactionMessage = "Hatch blocked? Hmmm.." + radMsg;
            }
            else if (chipSlot != -1) {
                m_interactionMessage = "Hatch locked! To unlock press [" + std::to_string(chipSlot) + "]" + radMsg;
            } else {
                m_interactionMessage = "Hatch locked! You need a Decoding chip." + radMsg;

                // Optimalizovana kontrola STUCK
                bool anyDoorOpen = false;
                auto mapGrid = m_game->getStation()->getMapGrid();

                for (size_t x = 0; x < mapGrid.size(); ++x) {
                    for (size_t y = 0; y < mapGrid[x].size(); ++y) {
                        Module* module = mapGrid[x][y];
                        if (!module) continue;

                        for (Hatch* checkHatch : module->getHatches()) {
                            if (checkHatch != nullptr && !checkHatch->isLocked()) {
                                anyDoorOpen = true;
                                break;
                            }
                        }
                        if (anyDoorOpen) break;
                    }
                    if (anyDoorOpen) break;
                }

                if (!anyDoorOpen) {
                    triggerAchievement("STUCK");
                }
            }

            if (inRadiation) {
                m_game->getDrone()->drainEnergy(damage);
            }

        } else {
            if (inRadiation) {
                m_game->getDrone()->drainEnergy(damage);
                m_interactionMessage = "Wall bump! Energy -" + std::to_string(damage);
            } else {
                m_interactionMessage = "Bumped into a wall!";
            }
        }
    }
    else {
        Hazard* newHazard = newModule->getHazard();
        if (newHazard != nullptr){
            if (newHazard->getRenderIcon() == 'R') {
                int damage = static_cast<int>(static_cast<Radiation*>(newHazard)->getDamagePerSecond());
                m_game->getDrone()->drainEnergy(damage);
                m_interactionMessage = "Radiation area! Energy dropping! -" + std::to_string(damage);
                triggerAchievement("RADIATION_DAMAGE");
            }
        }
        if (m_game->getDrone()->getOccupiedModule()->getIsFinal()) {
            m_interactionMessage = "Final module reached! [Space] to leave Space!";
        }
    }
}

void PlayingState::addToBuffer(Renderer* renderer) {
    if (!renderer || !m_game) return;

    Drone* drone = m_game->getDrone();
    int consoleW = renderer->getConsoleWidth();
    int consoleH = renderer->getConsoleHeight();

    if (drone->getEnergy() <= 0) {
        m_game->changeState(new GameOverState(m_game));
        return;
    }

    updateCamera(renderer, drone, consoleW, consoleH);

    int camX = renderer->getCameraX();
    int camY = renderer->getCameraY();

    renderModules(renderer, camX, camY, consoleW, consoleH);
    renderDrone(renderer, drone);
    renderUI(renderer, drone, camX, camY, consoleW, consoleH);
}

void PlayingState::triggerAchievement(std::string id) {
    if (Achievements::getInstance()->unlockAchievement(id)) {
        m_game->triggerAchievementPopup(id);
    }
}

void PlayingState::updateCamera(Renderer* renderer, Drone* drone, int consoleW, int consoleH) {
    if (!drone || !drone->getOccupiedModule()) return;

    int camX = renderer->getCameraX();
    int camY = renderer->getCameraY();
    Position dronePos = drone->getOccupiedModule()->getPosition();

    int droneWorldX = START_X + static_cast<int>(dronePos.x) * SPACING_X + (MOD_W / 2);
    int droneWorldY = START_Y + static_cast<int>(dronePos.y) * SPACING_Y + (MOD_H / 2);

    if (camX == 0 && camY == 0) {
        camX = droneWorldX - consoleW / 2;
        camY = droneWorldY - consoleH / 2;
    } else {
        int droneScreenX = droneWorldX - camX;
        int droneScreenY = droneWorldY - camY;

        int marginX = 26;
        int marginY = 12;

        if (droneScreenX < marginX) {
            camX -= (marginX - droneScreenX);
        } else if (droneScreenX > consoleW - marginX) {
            camX += (droneScreenX - (consoleW - marginX));
        }

        if (droneScreenY < marginY) {
            camY -= (marginY - droneScreenY);
        } else if (droneScreenY > consoleH - marginY) {
            camY += (droneScreenY - (consoleH - marginY));
        }
    }

    renderer->setCamera(camX, camY);
}

void PlayingState::renderModules(Renderer* renderer, int camX, int camY, int consoleW, int consoleH) {
    auto mapGrid = m_game->getStation()->getMapGrid();

    int viewMinX = camX - MOD_W;
    int viewMaxX = camX + consoleW + MOD_W;
    int viewMinY = camY - MOD_H;
    int viewMaxY = camY + consoleH + MOD_H;

    for (size_t x = 0; x < mapGrid.size(); ++x) {
        for (size_t y = 0; y < mapGrid[x].size(); ++y) {
            Module* module = mapGrid[x][y];
            if (!module) continue;

            int worldX = START_X + static_cast<int>(x) * SPACING_X;
            int worldY = START_Y + static_cast<int>(y) * SPACING_Y;

            if (worldX < viewMinX || worldX > viewMaxX || worldY < viewMinY || worldY > viewMaxY) {
                continue;
            }

            renderer->drawFrame(worldX, worldY, MOD_W, MOD_H);

            bool hasNorthHatch = false, hasSouthHatch = false, hasWestHatch = false, hasEastHatch = false;
            std::vector<Hatch*> hatches = module->getHatches();

            for (Hatch* hatch : hatches) {
                if (!hatch) continue;
                Direction dir = hatch->getDirection();
                if (dir == Direction::North) hasNorthHatch = true;
                else if (dir == Direction::South) hasSouthHatch = true;
                else if (dir == Direction::West) hasWestHatch = true;
                else if (dir == Direction::East) hasEastHatch = true;
            }

            if (!hasNorthHatch) renderer->drawString(worldX, worldY, std::string(MOD_W, '#'), Colors::getInstance()->OUTER_WALL_COLOR);
            if (!hasSouthHatch) renderer->drawString(worldX, worldY + MOD_H - 1, std::string(MOD_W, '#'), Colors::getInstance()->OUTER_WALL_COLOR);
            if (!hasWestHatch) {
                for (int i = 0; i < MOD_H; ++i) renderer->drawString(worldX, worldY + i, "#", Colors::getInstance()->OUTER_WALL_COLOR);
            }
            if (!hasEastHatch) {
                for (int i = 0; i < MOD_H; ++i) renderer->drawString(worldX + MOD_W - 1, worldY + i, "#", Colors::getInstance()->OUTER_WALL_COLOR);
            }


            if (module->getIsFinal()) {
                if (m_game->getStation()->getHazardFactory()->getRequiredMalfunctions() <= 0) {
                    renderer->drawString(worldX + 3, worldY + 2, "F",Colors::getInstance()->FINAL_COLOR);
                    renderer->drawString(worldX + 2, worldY + 3, "F", Colors::getInstance()->FINAL_COLOR);
                    renderer->drawString(worldX + 4, worldY + 3, "F", Colors::getInstance()->FINAL_COLOR);
                } else {
                    renderer->drawString(worldX + 3, worldY + 2, "?",Colors::getInstance()->FINAL_COLOR);
                    renderer->drawString(worldX + 2, worldY + 3, "?", Colors::getInstance()->FINAL_COLOR);
                    renderer->drawString(worldX + 4, worldY + 3, "?", Colors::getInstance()->FINAL_COLOR);
                }
            }

            char icon = module->getRenderIcon();

            if (icon == 'R') {
                for (int ry = 1; ry < MOD_H - 1; ++ry) {
                    for (int rx = 1; rx < MOD_W - 1; ++rx) {
                        if ((rx + ry) % 2 == 0) {
                            renderer->drawString(worldX + rx, worldY + ry, "~", Colors::getInstance()->RADIATION_COLOR);
                        }
                    }
                }

                renderer->drawString(worldX + (MOD_W / 2), worldY + (MOD_H / 2), "R", Colors::getInstance()->RADIATION_ICON_COLOR);

            } else {
                int cornerIndex = (x * 3 + y) % 4;
                int iconX = worldX;
                int iconY = worldY;

                switch (cornerIndex) {
                    case 0: iconX += 1; iconY += 1; break;
                    case 1: iconX += MOD_W - 2; iconY += 1; break;
                    case 2: iconX += MOD_W - 2; iconY += MOD_H - 2; break;
                    case 3: iconX += 1; iconY += MOD_H - 2; break;
                }

                if (icon == '!' or icon == 'E') {
                    renderer->drawString(iconX, iconY, std::string(1, icon), Colors::getInstance()->HAZARD_ICON_COLOR);
                } else {
                    renderer->drawString(iconX, iconY, std::string(1, icon), Colors::getInstance()->ICON_COLOR);
                }

            }

            for (Hatch* hatch : hatches) {
                if (!hatch) continue;
                Direction dir = hatch->getDirection();
                Position modulePos = module->getPosition();
                Position neighborPos = modulePos.getNewPosition(dir);

                bool neighborExists = false;

                bool leadsToFinal = module->getIsFinal();

                if (neighborPos.x >= 0 && neighborPos.x < static_cast<int>(mapGrid.size()) &&
                    neighborPos.y >= 0 && !mapGrid.empty() &&
                    neighborPos.y < static_cast<int>(mapGrid[0].size())) {

                    Module* neighborMod = mapGrid[neighborPos.x][neighborPos.y];

                    if (neighborMod != nullptr) {
                        neighborExists = true;

                        if (neighborMod->getIsFinal()) {
                            leadsToFinal = true;
                        }
                    }
                    }

                char hatchChar;
                if (leadsToFinal && hatch->isLocked()) {
                    hatchChar = '?';
                } else {
                    hatchChar = hatch->isLocked() ? 'L' : (neighborExists ? ' ' : 'H');
                }
                if (hatchChar == 'H') {
                    if (dir == Direction::North) renderer->drawString(worldX + (MOD_W / 2), worldY, std::string(1, hatchChar), Colors::getInstance()->HATCH_COLOR);
                    else if (dir == Direction::South) renderer->drawString(worldX + (MOD_W / 2), worldY + MOD_H - 1, std::string(1, hatchChar), Colors::getInstance()->HATCH_COLOR);
                    else if (dir == Direction::East) renderer->drawString(worldX + MOD_W - 1, worldY + (MOD_H / 2), std::string(1, hatchChar), Colors::getInstance()->HATCH_COLOR);
                    else if (dir == Direction::West) renderer->drawString(worldX, worldY + (MOD_H / 2), std::string(1, hatchChar), Colors::getInstance()->HATCH_COLOR);
                } else {
                    if (dir == Direction::North) renderer->drawString(worldX + (MOD_W / 2), worldY, std::string(1, hatchChar), Colors::getInstance()->LOCKED_HATCH_COLOR);
                    else if (dir == Direction::South) renderer->drawString(worldX + (MOD_W / 2), worldY + MOD_H - 1, std::string(1, hatchChar), Colors::getInstance()->LOCKED_HATCH_COLOR);
                    else if (dir == Direction::East) renderer->drawString(worldX + MOD_W - 1, worldY + (MOD_H / 2), std::string(1, hatchChar), Colors::getInstance()->LOCKED_HATCH_COLOR);
                    else if (dir == Direction::West) renderer->drawString(worldX, worldY + (MOD_H / 2), std::string(1, hatchChar), Colors::getInstance()->LOCKED_HATCH_COLOR);
                }


            }
        }
    }
}

void PlayingState::renderDrone(Renderer* renderer, Drone* drone) {
    if (!drone || !drone->getOccupiedModule()) return;

    Position dronePos = drone->getOccupiedModule()->getPosition();
    int droneWorldX = START_X + static_cast<int>(dronePos.x) * SPACING_X + (MOD_W / 2);
    int droneWorldY = START_Y + static_cast<int>(dronePos.y) * SPACING_Y + (MOD_H / 2);

    renderer->drawString(droneWorldX, droneWorldY, "D", Colors::getInstance()->DRONE_COLOR);
}

void PlayingState::renderUI(Renderer* renderer, Drone* drone, int camX, int camY, int consoleW, int consoleH) {
    std::string emptyLine(consoleW, ' ');
    for (int i = 0; i < 3; ++i) renderer->drawString(camX, camY + i, emptyLine, "\x1b[37m");
    for (int i = consoleH - 2; i < consoleH; ++i) renderer->drawString(camX, camY + i, emptyLine, "\x1b[37m");

    for (int i = 0; i < consoleH; ++i) {
        renderer->drawString(camX, camY + i, "     ", "\x1b[37m");
        renderer->drawString(camX + consoleW - 5, camY + i, "     ", "\x1b[37m");
    }

    renderer->drawFrame(camX + 5, camY + 3, consoleW - 10, consoleH - 5);

    if (m_game && m_game->getStation()) {
        int numMalfunctions = m_game->getStation()->getHazardFactory()->getRequiredMalfunctions();

        if (numMalfunctions <= 0) {
            renderer->drawString(camX + 6, camY + 2, "Find exit!", Colors::getInstance()->NORMAL_TEXT);
        } else {
            std::string baseText = "Malfunctions: ";
            std::string exclamationMarks = std::string(numMalfunctions, '!');

            renderer->drawString(camX + 6, camY + 2, baseText, Colors::getInstance()->NORMAL_TEXT);

            int nextX = camX + 6 + baseText.length();

            renderer->drawString(nextX, camY + 2, exclamationMarks, Colors::getInstance()->MALFUNCTION_TEXT_COLOR);
        }
    }

    std::string invText = "INVENTORY: ";
    if (drone) {
        std::vector<Item*> items = drone->getInventoryItems();
        if (items.empty()) {
            invText += "[ Empty ]";
        } else {
            std::map<ItemType, int> itemCounts;
            for (Item* item : items) {
                if (item) itemCounts[item->getItemType()]++;
            }

            invText += "";
            bool first = true;
            int slotIndex = 1;

            for (const auto& pair : itemCounts) {
                if (!first) invText += " | ";

                std::string itemName;
                switch (pair.first) {
                    case ItemType::Battery:      itemName = "Battery"; break;
                    case ItemType::Component:    itemName = "Component"; break;
                    case ItemType::DecodingChip: itemName = "Decoding chip"; break;
                    default:                     itemName = "Unknown"; break;
                }

                invText += "[" + std::to_string(slotIndex) + "] " + itemName + ": " + std::to_string(pair.second);
                slotIndex++;
                first = false;
            }
            invText += "";
        }
        int energy = drone->getEnergy();
        int bars = energy / 5;
        if (bars > 20) bars = 20;
        if (bars < 0) bars = 0;

        std::string prefixText = "ENERGY: ";
        std::string barText = "[";
        for (int i = 0; i < 20; ++i) {
            if (i < bars) barText += "#";
            else barText += "-";
        }
        barText += "]";
        std::string suffixText = " " + std::to_string(energy);

        int totalLength = prefixText.length() + barText.length() + suffixText.length();
        int startX = camX + consoleW - totalLength - 6;

        renderer->drawString(startX, camY + 2, prefixText, Colors::getInstance()->NORMAL_TEXT);

        int barX = startX + prefixText.length();
        renderer->drawString(barX, camY + 2, barText, Colors::getInstance()->ENERGY_COLOR);

        int suffixX = barX + barText.length();
        renderer->drawString(suffixX, camY + 2, suffixText, Colors::getInstance()->NORMAL_TEXT);
    }

    int invX = camX + (consoleW - static_cast<int>(invText.length())) / 2;
    renderer->drawString(invX, camY + consoleH - 1, invText, Colors::getInstance()->INVENTORY_COLOR);

    if (!m_interactionMessage.empty()) {
        int msgX = camX + (consoleW - static_cast<int>(m_interactionMessage.length())) / 2;
        renderer->drawString(msgX, camY + 1, m_interactionMessage, Colors::getInstance()->INTERACTION_MESSAGE_COLOR);
    }
}
