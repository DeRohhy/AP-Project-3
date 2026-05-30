#pragma once

#include <vector>

#include "../core/Component.h"

enum class AttachResult
{
    PACKAGE_NOT_FOUND,
    CHILD_NOT_FOUND,
    NOT_A_PACKAGE,
    ALREADY_ATTACHED,
    PACKAGE_ALREADY_INSTALLED,
    SUCCESS,
};

enum class MockFailResult
{
    COMPONENT_NOT_FOUND,
    ALREADY_MOCK_FAILED,
    ALREADY_INSTALLED,
    SUCCESS,
};

enum class ResolveFailResult
{
    COMPONENT_NOT_FOUND,
    NOT_IN_MOCK_FAIL,
    SUCCESS,
};

enum class InstallResult
{
    COMPONENT_NOT_FOUND,
    ALREADY_INSTALLED,
    FAILED,
    SUCCESS,
};

class ComponentManager
{
public:
    ComponentManager();

    ~ComponentManager();

    Component* getComponent(const std::string& id);

    bool addModule(const std::string id, const std::string title);
    
    bool addPackage(const std::string id, const std::string title);

    AttachResult attachComponent(const std::string& package_id, const std::string& child_id);

    MockFailResult mockFailComponent(const std::string& id);

    ResolveFailResult resolveFailComponent(const std::string& id);

    InstallResult installComponent(const std::string& id);

private:
    std::vector<Component*> components;
};