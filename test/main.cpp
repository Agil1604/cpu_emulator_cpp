#include <iostream>
#include <stdlib.h>
#include <vector>

#include "parser.h"
#include "stack.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: emulator <input file>" << std::endl;
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];

    Parser parser{filename};
    std::vector<Command> commands = parser.parse_command_sequence();

    for (const auto &cmd : commands)
    {
        cmd.execute();
    }
    return 0;
}
