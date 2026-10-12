//
// Created by Radek on 21.06.2026.
//

#include "Achievements.h"

Achievements::Achievements() {
    m_achievements.push_back(new Achievement{
            "FIRST_FIX",
            "Mechanic in blood",
            "Repair your first malfunction.",
            false,
            {
                "  | ",
                "  | ",
                "  o  "
            }
        });
    m_achievements.push_back(new Achievement{
            "FIRST_BATTERY",
            "My first AAA",
            "Heal yourself using battery.",
            false,
            {
                " |+| ",
                " |/| ",
                " |-| "
            }
        });

    m_achievements.push_back(new Achievement{
        "HACKER",
        "Math finally paid off",
        "Defeat an enemy in the hacking minigame.",
        false,
        {
            " {0} ",
            " 101 ",
            " {1} "
        }
    });

    m_achievements.push_back(new Achievement{
        "FIRST_WIN",
        "Survivor of the finest",
        "Successfully escape the space station.",
        false,
        {
            " /^\\ ",
        "<###>",
       " \\\\/ "
        }
    });

    m_achievements.push_back(new Achievement{
        "RADIATION_DAMAGE",
        "Toxic - Britney Spears",
        "Listen you're not gonna become hulk.",
        false,
        {
            " \\|/ ",
            " -R- ",
            " /|\\ "
        }
    });

    /*
    m_achievements.push_back(new Achievement{
        "ENEMY_DEATH",
        "Death by WHAT?",
        "I mean, basic math right.",
        false,
        {
            " ",
            " 1+1 ",
            " "
        }
    });*/

    m_achievements.push_back(new Achievement{
        "PACIFIST",
        "Pacifist? Really?...",
        "Beat the game without killing a single enemy.",
        false,
        {
            " (@) ",
                        " \\|/ ",
                        "  |  "
        }
    });

    m_achievements.push_back(new Achievement{
        "STUCK",
        "Stuck forever",
        "Well, where to go now?",
        false,
        {
            " ### ",
            " #D# ",
            " ### "
        }
    });
    m_achievements.push_back(new Achievement{
        "HOARDER",
        "Hoarder",
        "I am really full.",
        false,
        {
            " BDC ",
            " CCD ",
            " DBC "
        }
    });
    m_achievements.push_back(new Achievement{
        "NO_CHEATS",
        "The True ending",
        "Get ALL other achievements without using cheats!",
        false,
        {
            " ",
            "  W ",
            " "
        }
    });

}

Achievements * Achievements::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new Achievements();
    }

    return m_instance;
}

Achievements::~Achievements() {
    for (Achievement * achievement: m_achievements) {
        delete achievement;
    }
}

bool Achievements::unlockAchievement(std::string achievementId) {
    if (m_achievements.empty()) return false;

    for (Achievement * achievement: m_achievements) {
        if (achievement->id == achievementId) {
            if (achievement->unlocked) {
                return false;
            }

            achievement->unlocked = true;
            return true;
        }
    }

    return false;
}

void Achievements::unlockAllAchievements() {
    if (m_achievements.empty()) return;

    for (Achievement * achievement: m_achievements) {
        if (achievement->id == "NO_CHEATS") continue; // never unlock via cheat
        achievement->unlocked = true;
    }

    m_cheatsUsed = true;
}

bool Achievements::cheatsUsed() {
    return m_cheatsUsed;
}

std::vector<Achievement *> Achievements::getAchievements() {
    if (m_achievements.empty()) return {};

    return m_achievements;

}

Achievement* Achievements::getAchievementInfo(std::string achievementId) {
    if (m_achievements.empty()) return {};

    for (Achievement * achievement: m_achievements) {
        if (achievement->id == achievementId) {
            return achievement;
        }
    }

    return nullptr;
}


