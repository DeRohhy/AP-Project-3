#include "Package.h"

#include <algorithm>

Package::Package(const std::string& _id, const std::string& _title, ComponentState _state)
    : Component(_id, _title, _state) {}

bool Package::hasDependency(std::string id)
{
    for (auto* dep: dependencies)
        if (dep->getId() == id)
            return true;

    return false;
    // return std::find(dependencies.begin(), dependencies.end(), dep) != dependencies.end();
}

void Package::addDependency(Component* dep)
{
    // auto it = std::find(dependencies.begin(), dependencies.end(), dep);

    // if (it != dependencies.end()) return false;
    
    dependencies.push_back(dep);
    
    // return true;
}

bool Package::isPackage() const 
{
    return true;
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
    return true;
}
