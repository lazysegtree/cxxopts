
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

using namespace std;

int main(int argc, char* argv[])
{
     cxxopts::Options cmd_options("font-maker", "Create font PBFs from TTFs or OTFs.");
    cmd_options.add_options()
        ("output", "Output directory (to be created, must not already exist)", cxxopts::value<string>())
        ("fonts", "Input font(s) (as TTF or OTF)", cxxopts::value<vector<string>>())
        ("name", "Override output fontstack name", cxxopts::value<string>())
        ("help", "Print usage")
    ;
    cmd_options.positional_help("<OUTPUT_DIR> <INPUT_FONT> [INPUT_FONT2 ...]");
    cmd_options.parse_positional({"output","fonts"});

    auto result = cmd_options.parse(argc, argv);
    if (result.count("help"))
    {
      cout << cmd_options.help() << endl;
      exit(0);
    }
    if (result.count("output") == 0 || result.count("fonts") == 0) {
        cout << cmd_options.help() << endl;
        exit(1);
    }
    auto output_dir = result["output"].as<string>();
    auto fonts = result["fonts"].as<vector<string>>();
    DEBUG(output_dir);
    DEBUG(fonts.size(), fonts);
}