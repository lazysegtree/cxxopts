
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    ("vo", "Vector", cxxopts::value<std::vector<std::string>>())
    ("o,option", "Opt", cxxopts::value<std::vector<std::string>>())
    ;
  options.parse_positional({"o"});
  auto result = options.parse(argc, argv);

  if(result.count("option")) {
    auto val = result["option"].as<std::vector<std::string>>();
    DEBUG(val.size(), val);
  }
  if(result.count("vo")) {
    auto val = result["vo"].as<std::vector<std::string>>();
    DEBUG(val.size(), val);
  }
}