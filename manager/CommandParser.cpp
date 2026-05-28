#include "CommandParser.h"

#include <iostream>
#include <string>
#include <sstream>

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
        else if (operation == "MOCH_FAIL") handleMockFail(ss);
        else if (operation == "RESOLVE_ALL") handleResolveFail(ss);
        else if (operation == "INSTALL") handleInstall(ss);
        else if (operation == "UNINSTALL") handleUninstall(ss);
        else invalidCommand();
    }
}

void CommandParser::handleAdd(std::stringstream& ss) 
{
    std::string type;
    if (!(ss >> type) || (type != "MODULE" && type != "PACKAGE"))
    {
        invalidCommand();
        return;
    }
    std::cout << "ADDING!!\n";
}

void CommandParser::handleAttach(std::stringstream& ss) {}

void CommandParser::handleMockFail(std::stringstream& ss) {}

void CommandParser::handleResolveFail(std::stringstream& ss) {}

void CommandParser::handleInstall(std::stringstream& ss) {}

void CommandParser::handleUninstall(std::stringstream& ss) {}


void CommandParser::invalidCommand() const
{
    std::cout << "ERROR: Invalid command\n";
}