#pragma once

#include "Component.h"

#include <vector>

class Package: public Component
{
public:
    bool addDependency(Component* dependency);

    bool isPackage() const override;
private:
    std::vector<Component*> dependencies;
};