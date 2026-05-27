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


void CommandParser::invalidCommand() const
{
    std::cout << "ERROR: Invalid command\n";
}