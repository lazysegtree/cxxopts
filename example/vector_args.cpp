#include <iostream>
#include "debug.h"
#include "../include/cxxopts.hpp"

int
main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
  ("input", "Input files", cxxopts::value<std::vector<std::string>>());
  
  auto result = options.parse(argc, argv);
  auto inp = result["input"].as<std::vector<std::string>>();
  DEBUG(inp.size(), inp);
}