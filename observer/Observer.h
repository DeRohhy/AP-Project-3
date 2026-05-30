#pragma once

#include <vector>

class Component;
enum class ComponentState;

class Observer
{
public:
    virtual ~Observer() {}
    virtual void onNotify(const Component* component, ComponentState old_state, ComponentState new_state) = 0;
};
