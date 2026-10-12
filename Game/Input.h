#pragma once
#include "Action.h"

class Input {
    static Input* m_instance;
    Input();

public:
    static Input* getInstance();
    Action getAction();
};