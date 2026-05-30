#include "SystemLogger.h"

#include <iostream>

void SystemLogger::onNotify(const Component* component, ComponentState old_state, ComponentState new_state)
{
    std::cout << "[OBSERVER] Component " << component->getId() << " changed from " << stateToString(old_state) << " to " << stateToString(new_state) << '\n';
}

std::string SystemLogger::stateToString(ComponentState state) const
{
    switch (state)
    {
    case ComponentState::FAILED:
        return "FAILED";
    case ComponentState::INSTALLED:
        return "INSTALLED";
    case ComponentState::PENDING:
        return "PENDING";
    }
}

