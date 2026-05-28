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

    void handleAttach(std::stringstream& ss);

    void handleMockFail(std::stringstream& ss);

    void handleResolveFail(std::stringstream& ss);

    void handleInstall(std::stringstream& ss);

    void handleUninstall(std::stringstream& ss);

private:
    ComponentManager component_manager;
};