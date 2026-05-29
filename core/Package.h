#pragma once

#include "Component.h"

#include <vector>
#include <string>

class Package: public Component
{
public:
    Package(const std::string& _id, const std::string& _title, ComponentState _state = ComponentState::PENDING);

    bool hasDependency(std::string id);

    void addDependency(Component* dep);

    bool isPackage() const override;
private:
    std::vector<Component*> dependencies;
};