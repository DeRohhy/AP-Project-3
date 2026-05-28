#include "Component.h"

#include <string>


Component::Component(const std::string& _id, const std::string& _title, ComponentState _state) :
    id{ _id }, title{ _title }, state{ _state } {};


void Component::changeState(ComponentState new_state)
{
    state = new_state;
    
    // Todo:
    // Use observer pattern and notify to print the state change in console
}
