#pragma once

#include "ComponentManager.h"

class CommandParser
{
public:
    CommandParser(const ComponentManager& _manager);
    
    ~CommandParser();

    void run();
private:
    ComponentManager component_manager;
};