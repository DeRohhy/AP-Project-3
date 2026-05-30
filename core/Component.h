#pragma once

#include <string>
#include <stack>
#include <vector>

#include "../observer/Observer.h"

enum class ComponentState { PENDING, INSTALLED, FAILED };

class Component
{
public:
    Component(const std::string& _id, const std::string& _title, ComponentState _state = ComponentState::PENDING);

    virtual bool isPackage() const = 0;
    ComponentState getState() const;
    std::string getId() const;
    bool isMockFail() const;
    bool isTopLevel() const;
    int getInstalledParentCount() const;

    virtual void changeState(ComponentState new_state);
    void setMockFail(bool value);
    void setTopLevel(bool value);
    void addObserver(Observer* observer);
    void setInstalledParentCount(int value);
    
    virtual bool install(std::stack<Component*>& installation_order) = 0;
    virtual void uninstall() = 0;
    bool removeSelf();

protected:
    std::string id;
    std::string title;
    bool mock_fail;
    bool top_level; // ~ is_explicityly_installed
    std::vector<Observer*> observers;
    int installed_parent_count;
private:
    ComponentState state;
};