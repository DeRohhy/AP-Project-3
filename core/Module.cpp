#include "Module.h"

Module::Module(const std::string& _id, const std::string& _title, ComponentState _state)
    : Component(_id, _title, _state) {}


bool Module::isPackage() const
{
    return false;
}

bool Module::install(std::stack<Component*>& installation_order)
{
    if (mock_fail)
    {
        changeState(ComponentState::FAILED);
        return false;
    }

    if (getState() != ComponentState::INSTALLED)
    {
        changeState(ComponentState::INSTALLED);
        
        installation_order.push(this);
    }

    return true;
}


void Module::uninstall()
{
    changeState(ComponentState::PENDING);
}
