#pragma once

#include "Component.h"

class Module: public Component
{
public:
    bool isPackage() const override;
};