#include <iostream>
#include <string>
#include "parser.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: emulator <input file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    Parser parser{filename};
    parser.run();

    return 0;
}
