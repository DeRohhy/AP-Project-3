#include "CommandParser.h"

#include <iostream>
#include <string>
#include <sstream>

const std::string PACKAGE = "PACKAGE", MODULE = "MODULE";


CommandParser::CommandParser(const ComponentManager& _manager) :
    component_manager{ _manager } {}


CommandParser::~CommandParser() {};


void CommandParser::run()
{
    std::string line;

    while (getline(std::cin, line) && line != "END")
    {
        std::stringstream ss{ line };

        std::string operation;
        ss >> operation;

        if (operation == "ADD") handleAdd(ss);
        else if (operation == "ATTACH") handleAttach(ss);
        else if (operation == "MOCK_FAIL") handleMockFail(ss);
        else if (operation == "RESOLVE_FAIL") handleResolveFail(ss);
        else if (operation == "INSTALL") handleInstall(ss);
        else if (operation == "UNINSTALL") handleUninstall(ss);
        else invalidCommand();
    }

}

void CommandParser::handleAdd(std::stringstream& ss)
{
    std::string type;
    if (!(ss >> type) || (type != MODULE && type != PACKAGE))
    {
        invalidCommand();
        return;
    }

    std::string id;
    if (!(ss >> id))
    {
        invalidCommand();
        return;
    }

    std::string title;
    getline(ss >> std::ws, title); // using std::ws manipulator to consume leading whitespace before getline reads
    if (title.empty())
    {
        invalidCommand();
        return;
    }

    if ((type == MODULE && !component_manager.addModule(id, title)) ||
        (type == PACKAGE && !component_manager.addPackage(id, title)))
    {
        std::cout << "ERROR: Component with ID " << id << " already exists\n";
    }

}

void CommandParser::handleAttach(std::stringstream& ss)
{
    std::string package_id, child_id;

    if (!(ss >> package_id >> child_id))
    {
        invalidCommand();
        return;
    }

    AttachResult result = component_manager.attachComponent(package_id, child_id);
    switch (result)
    {
    case AttachResult::PACKAGE_NOT_FOUND:
        componentNotFound(package_id);
        break;
    case AttachResult::CHILD_NOT_FOUND:
        componentNotFound(child_id);
        break;
    case AttachResult::NOT_A_PACKAGE:
        std::cout << "Error: Cannot attach to a module\n";
        break;
    case AttachResult::ALREADY_ATTACHED:
        std::cout << "Error: Component " << child_id << " is already attached to " << package_id << '\n';
        break;
    case AttachResult::PACKAGE_ALREADY_INSTALLED:
        std::cout << "Error: Cannot attach to an already installed package\n";
        break;
    case AttachResult::SUCCESS:
        break;
    }
}

void CommandParser::handleMockFail(std::stringstream& ss)
{
    std::string id;
    if (!(ss >> id))
    {
        invalidCommand();
        return;
    }

    switch(component_manager.mockFailComponent(id))
    {
    case MockFailResult::COMPONENT_NOT_FOUND:
        componentNotFound(id);
        break;
    case MockFailResult::ALREADY_MOCK_FAILED:
        std::cout << "ERROR: Component " << id << " is already set to fail\n";
        break;
    case MockFailResult::ALREADY_INSTALLED:
        std::cout << "ERROR: Component " << id << " is already installed\n";
        break;
    case MockFailResult::SUCCESS:
        break;
    }
}

void CommandParser::handleResolveFail(std::stringstream& ss)
{
    std::string id;
    if (!(ss >> id))
    {
        invalidCommand();
        return;
    }

    switch(component_manager.resolveFailComponent(id))
    {
    case ResolveFailResult::COMPONENT_NOT_FOUND:
        componentNotFound(id);
        break;
    case ResolveFailResult::NOT_IN_MOCK_FAIL:
        std::cout << "ERROR: Component " << id << " is not in a mock fail state\n";
        break;
    case ResolveFailResult::SUCCESS:
        break;
    }
}

void CommandParser::handleInstall(std::stringstream& ss) {}

void CommandParser::handleUninstall(std::stringstream& ss) {}


void CommandParser::invalidCommand() const
{
    std::cout << "ERROR: Invalid command\n";
}

void CommandParser::componentNotFound(std::string id) const
{
    std::cout << "Error: Component " << id << " does not exist\n";
}