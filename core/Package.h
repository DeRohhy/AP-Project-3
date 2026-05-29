#pragma once

#include "Component.h"

#include <vector>
#include <string>

class Package: public Component
{
public:
    bool hasDependency(std::string id);

    void addDependency(Component* dep);

    bool isPackage() const override;
private:
    std::vector<Component*> dependencies;
};