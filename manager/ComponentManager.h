#pragma once

#include <vector>

#include "../core/Component.h"

enum class AttachResult
{
    PACKAGE_NOT_FOUND,
    CHILD_NOT_FOUND,
    NOT_A_PACKAGE,
    ALREADY_ATTACHED,
    PACKAGE_ALREADY_INSTALLED,
    SUCCESS,
};

class ComponentManager
{
public:
    ComponentManager();

    ~ComponentManager();

    Component* getComponent(const std::string& id);

    AttachResult AttachComponent(const std::string& package_id, const std::string& child_id);
private:
    std::vector<Component*> components;
};