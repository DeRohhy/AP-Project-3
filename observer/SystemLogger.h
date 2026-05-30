#pragma once

#include <string>

#include "../core/Component.h"
#include "Observer.h"

class SystemLogger : public Observer
{
public:
    void onNotify(const Component* component, ComponentState old_state, ComponentState new_state) override;
private:
    std::string stateToString(ComponentState state) const;
};