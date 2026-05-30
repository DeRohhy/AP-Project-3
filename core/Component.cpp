#include "Component.h"

#include <string>
#include <iostream>

Component::Component(const std::string& _id, const std::string& _title, ComponentState _state) :
    id{ _id }, title{ _title }, state{ _state }, mock_fail{ false }, top_level{ false } {};


void Component::changeState(ComponentState new_state)
{
    ComponentState old_state = state;
    state = new_state;


    // remember to remove iostream at the top
    std::cout << "[!] " << id << ' ' << int(old_state) << " -> " << int(new_state) << '\n';
    
    // Todo:
    // Use observer pattern and notify to print the state change in console
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

void Component::setMockFail(bool value)
{
    mock_fail = value;
}

void Component::setTopLevel(bool value)
{
    top_level = value;
}
