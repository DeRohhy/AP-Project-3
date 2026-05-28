#include "Package.h"

#include <algorithm>

bool Package::isPackage() const 
{
    return true;
}


bool Package::addDependency(Component* dep)
{
    auto it = std::find(dependencies.begin(), dependencies.end(), dep);

    if (it != dependencies.end()) return false;
    
    dependencies.push_back(dep);
    
    return true;
}