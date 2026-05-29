#pragma once

#include "Component.h"

class Module: public Component
{
public:
    Module(const std::string& _id, const std::string& _title, ComponentState _state = ComponentState::PENDING);

    bool isPackage() const override;
};