#pragma once

#include "Component.h"

#include <vector>
#include <string>

class Package: public Component
{
public:
    Package(const std::string& _id, const std::string& _title, ComponentState _state = ComponentState::PENDING);

    bool isPackage() const override;
    
    void changeState(ComponentState new_state) override;
    
    bool hasDependency(std::string id);

    void addDependency(Component* dep);

    bool install(std::stack<Component*>& installation_order) override;
    void uninstall() override;

private:
    std::vector<Component*> dependencies;
};