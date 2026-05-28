#pragma once

#include "Component.h"

#include <vector>

class Package: public Component
{
public:
    bool addDependency(Component* dependency);
private:
    std::vector<Component*> dependencies;
};