#include <iostream>
#include "../../include/cxxopts.hpp"

int main(int argc, char * argv[]) {

    cxxopts::Options parser = cxxopts::Options("Reproducible Bug");
    parser.add_options()
    ("h,help", "show this help message and exit")
    ("my-option", "description with long wooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooord", cxxopts::value<int>())
    ("my-option-2", "many small width words to test if the the wrapping is smart or its dumb. If it turns out to be smart, then its good but also bad. Alas! so much complexity on this stupid useless parser.", cxxopts::value<int>());

    parser.set_width(40);

    auto args = parser.parse(argc, argv);
    if (args.count("help"))
    {
        std::cout << parser.help() << std::endl;
        exit(0);
    }

    return 0;
}