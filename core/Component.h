#pragma once

#include <string>

enum class ComponentState { PENDING, INSTALLED, FAILED };

class Component
{
public:
    Component(const std::string& _id, const std::string& _title, ComponentState _state = ComponentState::PENDING);

    virtual bool isPackage() const = 0;

    void changeState(ComponentState new_state);

    std::string getId() const;
protected:
    ComponentState state;
    std::string id;
    std::string title;
};