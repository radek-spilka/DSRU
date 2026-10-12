//
// Created by Radek on 21.06.2026.
//

#ifndef PROJEKT_ZOO_ACHIVEMENTS_H
#define PROJEKT_ZOO_ACHIVEMENTS_H

#include <vector>
#include "Achievement.h"

class Achievements {
    static Achievements * m_instance;
    std::vector<Achievement*> m_achievements;
    bool m_cheatsUsed = false;
    Achievements();
public:
    static Achievements * getInstance();
    ~Achievements();
    bool unlockAchievement(std::string achievementId);
    void unlockAllAchievements();
    bool cheatsUsed();

    std::vector<Achievement *> getAchievements();
    Achievement* getAchievementInfo(std::string achievementId);
};


#endif //PROJEKT_ZOO_ACHIVEMENTS_H
