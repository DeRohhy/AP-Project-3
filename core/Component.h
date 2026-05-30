#pragma once

#include <string>
#include <stack>

enum class ComponentState { PENDING, INSTALLED, FAILED };

class Component
{
public:
    Component(const std::string& _id, const std::string& _title, ComponentState _state = ComponentState::PENDING);

    virtual bool isPackage() const = 0;

    void changeState(ComponentState new_state);

    ComponentState getState() const;

    std::string getId() const;

    bool isMockFail() const;

    void setMockFail(bool value);

    void setTopLevel(bool value);

    virtual bool install(std::stack<Component*>& installation_order) = 0;
protected:
    std::string id;
    std::string title;
    bool mock_fail;
    bool top_level;
private:
    ComponentState state;
};