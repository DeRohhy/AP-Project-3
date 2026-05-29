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
        else if (operation == "RESOLVE_ALL") handleResolveFail(ss);
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
        std::cout << "Error: Component " << package_id << " does not exist\n";
        break;
    case AttachResult::CHILD_NOT_FOUND:
        std::cout << "Error: Component " << child_id << " does not exist\n";
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

void CommandParser::handleMockFail(std::stringstream& ss) {}

void CommandParser::handleResolveFail(std::stringstream& ss) {}

void CommandParser::handleInstall(std::stringstream& ss) {}

void CommandParser::handleUninstall(std::stringstream& ss) {}


void CommandParser::invalidCommand() const
{
    std::cout << "ERROR: Invalid command\n";
}