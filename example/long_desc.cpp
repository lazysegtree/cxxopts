#include <iostream>
#include "../include/cxxopts.hpp"

int main(int argc, char * argv[]) {

    cxxopts::Options parser = cxxopts::Options("Reproducible Bug");
    parser.add_options()
    ("h,help", "show this help message and exit")
    ("my-option", "description with long wooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooord", cxxopts::value<int>());

    auto args = parser.parse(argc, argv);
    if (args.count("help"))
    {
        std::cout << parser.help() << std::endl;
        exit(0);
    }

    return 0;
}