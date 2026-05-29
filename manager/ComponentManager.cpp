#include "ComponentManager.h"
#include "../core/Package.h"

ComponentManager::ComponentManager() = default;

ComponentManager::~ComponentManager() 
{
    // Todo: remove all components
}

Component* ComponentManager::getComponent(const std::string& id)
{
    for (Component* ptr: components)
        if (ptr->getId() == id)
            return ptr;

    return nullptr;
}


AttachResult ComponentManager::AttachComponent(const std::string& package_id, const std::string& child_id)
{
    Component* parent_component = getComponent(package_id);
    Component* child_component = getComponent(child_id);

    /*
        We have to validate these 2 component ids in this order:
        1) check if package_id exists
        2) check if child_id exists
        3) check if the package_id coresponding component is of type package
        4) check if child_id has already been attached to package_id
        5) check if package_id is already installed
    */

    if (parent_component == nullptr)
        return AttachResult::PACKAGE_NOT_FOUND;
    
    if (child_component == nullptr)
        return AttachResult::CHILD_NOT_FOUND;

    Package* package = dynamic_cast<Package*>(parent_component);
    
    if (package == nullptr)
        return AttachResult::NOT_A_PACKAGE;

    if (package->hasDependency(child_id))
        return AttachResult::ALREADY_ATTACHED;

    if (package->getState() == ComponentState::INSTALLED)
        return AttachResult::PACKAGE_ALREADY_INSTALLED;

    package->addDependency(child_component);

    return AttachResult::SUCCESS;
}
