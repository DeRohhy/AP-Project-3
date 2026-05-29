#include "Module.h"

Module::Module(const std::string& _id, const std::string& _title, ComponentState _state)
    : Component(_id, _title, _state) {}


bool Module::isPackage() const
{
    return false;
}