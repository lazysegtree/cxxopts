#include <iostream>
#include "debug.h"
#include "../include/cxxopts.hpp"

int
main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
  ("f", "float", cxxopts::value<float>());
  
  auto result = options.parse(argc, argv);
  auto inp = result["f"].as<float>();
  DEBUG(inp);
}