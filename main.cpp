/*
* ========== Naming Convention Guideline ==========
* Classes & Enums & Structs: PascalCase
* Functions: camelCase
* Variables: lower_snake_case
* Constants: UPPER_SNAKE_CASE
* =================================================
*/

#include "CommandParser.h"
#include "ComponentManager.h"

#include "core/Package.h"
#include "core/Module.h"

int main()
{
    ComponentManager manager;
    CommandParser parser{ manager };

    parser.run();


    
    return 0;
}