#include "ComponentManager.h"
#include "../core/Package.h"
#include "../core/Module.h"

#include <iostream>
#include <stack>

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

bool ComponentManager::addModule(const std::string id, const std::string title)
{
    if (getComponent(id) != nullptr)
        return false;

    Module* new_module = new Module{ id, title };

    new_module->addObserver(&logger);

    components.push_back(new_module);
    
    return true;
}

bool ComponentManager::addPackage(const std::string id, const std::string title)
{
    if (getComponent(id) != nullptr)
        return false;

    
    Package* new_package = new Package{ id, title };

    new_package->addObserver(&logger);

    components.push_back(new_package);
    
    return true;
}

AttachResult ComponentManager::attachComponent(const std::string& package_id, const std::string& child_id)
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

MockFailResult ComponentManager::mockFailComponent(const std::string& id)
{
    Component* component = getComponent(id);

    if (component == nullptr)
        return MockFailResult::COMPONENT_NOT_FOUND;

    if (component->isMockFail())
        return MockFailResult::ALREADY_MOCK_FAILED;
    
    if (component->getState() == ComponentState::INSTALLED)
        return MockFailResult::ALREADY_INSTALLED;
    
    component->setMockFail(true);
    
    return MockFailResult::SUCCESS;
}

ResolveFailResult ComponentManager::resolveFailComponent(const std::string& id)
{
    Component* component = getComponent(id);

    if (component == nullptr)
        return ResolveFailResult::COMPONENT_NOT_FOUND;

    if (!component->isMockFail())
        return ResolveFailResult::NOT_IN_MOCK_FAIL;
    
    component->setMockFail(false);

    return ResolveFailResult::SUCCESS;
}

InstallResult ComponentManager::installComponent(const std::string& id)
{
    Component* component = getComponent(id);

    if (component == nullptr)
        return InstallResult::COMPONENT_NOT_FOUND;

    if (component->getState() == ComponentState::INSTALLED)
        return InstallResult::ALREADY_INSTALLED;

    std::vector<Component*> installation_order;
    bool result = component->install(installation_order);

    if (result)
    {
        component->setTopLevel(true);

        return InstallResult::SUCCESS;
    }
    
    return InstallResult::FAILED;
}

UninstallResult ComponentManager::uninstallComponent(const std::string& id)
{
    Component* component = getComponent(id);

    if (component == nullptr)
        return UninstallResult::COMPONENT_NOT_FOUND;

    if (component->getState() != ComponentState::INSTALLED)
        return UninstallResult::COMPONENT_NOT_INSTALLED;

    if (component->getInstalledParentCount() > 0)
        return UninstallResult::COMPONENT_IS_REQUIRED;
    
    component->uninstall();
    component->setTopLevel(false);

    return UninstallResult::SUCCESS;
}

bool ComponentManager::uninstallAll()
{
    int uninstalled_count = 0;
    // uninstall all components in reverse adding order
    for (auto it = components.rbegin(); it != components.rend(); ++it)
    {
        Component* component = *it;

        uninstalled_count += component->removeSelf();
    }

    return uninstalled_count > 0;
}