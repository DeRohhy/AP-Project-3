#include "Package.h"

#include <algorithm>

#include <iostream>

Package::Package(const std::string& _id, const std::string& _title, ComponentState _state)
    : Component(_id, _title, _state) {}

bool Package::hasDependency(std::string id)
{
    for (auto* dep: dependencies)
        if (dep->getId() == id)
            return true;

    return false;
}

void Package::addDependency(Component* dep)
{
    dependencies.push_back(dep);
}

bool Package::isPackage() const 
{
    return true;
}

void Package::changeState(ComponentState new_state)
{
    if (getState() == new_state)
        return;
    
    ComponentState old_state = getState();
    Component::changeState(new_state);

    if (new_state == ComponentState::INSTALLED)
    {        
        // increment all dep installed_parent_count by 1
        for (Component* dep: dependencies)
            dep->setInstalledParentCount(dep->getInstalledParentCount() + 1);
    }
    else if (old_state == ComponentState::INSTALLED)
    {
        // decrement all dep installed_parent_count by 1
        for (Component* dep: dependencies)
            dep->setInstalledParentCount(dep->getInstalledParentCount() - 1);
    }
}


bool Package::install(std::stack<Component*>& installation_order) 
{
    if (mock_fail)
    {
        changeState(ComponentState::FAILED);
        return false;
    }

    if (getState() == ComponentState::INSTALLED)
        return true;

    for (Component* dep: dependencies)
    {
        if (!dep->install(installation_order))
        {
            changeState(ComponentState::FAILED);
            return false;
        }
    }

    changeState(ComponentState::INSTALLED);
    installation_order.push(this);

    return true;
}

void Package::uninstall()
{
    if (getState() != ComponentState::INSTALLED)
        return;
    
    changeState(ComponentState::PENDING);
    
    // uninstall dependency component in reverse adding order
    if (!dependencies.empty())
    {
        for (auto it = dependencies.rbegin(); it != dependencies.rend(); ++it)
        {
            Component* dep = *it;

            if (dep->getInstalledParentCount() == 0 && !dep->isTopLevel())
                dep->uninstall();
        }
    }

}
