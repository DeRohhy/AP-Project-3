#include "CommandParser.h"

#include <iostream>

CommandParser::CommandParser(const ComponentManager& _manager) :
    component_manager{ _manager } {}


CommandParser::~CommandParser() {};


void CommandParser::run()
{
    std::cout << "Running Command Parser!\n";
}