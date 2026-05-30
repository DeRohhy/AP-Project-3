#include "Component.h"

#include <string>
#include <iostream>

Component::Component(const std::string& _id, const std::string& _title, ComponentState _state) :
    id{ _id }, title{ _title }, state{ _state }, mock_fail{ false }, top_level{ false }, installed_parent_count{ 0 } {};


void Component::changeState(ComponentState new_state)
{
    if (state == new_state)
        return;
    
    ComponentState old_state = state;
    state = new_state;

    for (Observer* observer: observers)
        observer->onNotify(this, old_state, new_state);
}

ComponentState Component::getState() const
{
    return state;
}

std::string Component::getId() const
{
    return id;
}

bool Component::isMockFail() const
{
    return mock_fail;
}

bool Component::isTopLevel() const
{
    return top_level;
}

int Component::getInstalledParentCount() const
{
    return installed_parent_count;
}


void Component::setMockFail(bool value)
{
    mock_fail = value;
}

void Component::setTopLevel(bool value)
{
    top_level = value;
}


void Component::addObserver(Observer* observer)
{
    observers.push_back(observer);
}

void Component::setInstalledParentCount(int value)
{
    installed_parent_count = value;
}

bool Component::removeSelf()
{
    if (state == ComponentState::PENDING)
        return false;
    
    changeState(ComponentState::PENDING);
    installed_parent_count = 0;
    mock_fail = false;
    top_level = false;

    return true;
}