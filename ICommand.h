//
// Created by PC on 15.05.2026.
//
#pragma once
#ifndef PROJEKT_ZOO_ICOMMAND_H
#define PROJEKT_ZOO_ICOMMAND_H


class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};


#endif //PROJEKT_ZOO_ICOMMAND_H