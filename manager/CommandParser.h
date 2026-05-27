#pragma once

#include "ComponentManager.h"

#include <sstream>

class CommandParser
{
public:
    CommandParser(const ComponentManager& _manager);
    
    ~CommandParser();

    void run();

    void invalidCommand() const;

    void handleAdd(std::stringstream& ss);
private:
    ComponentManager component_manager;
};