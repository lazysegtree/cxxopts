// No LLM
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    //("?", "Opt", cxxopts::value<std::string>()->no_implicit_value())
    ("?,help", "Help")
    ("????,help2", "Help")
    ("?help,help3", "Help")
    ("help?,help4", "Help")
    ;
  
  auto result = options.parse(argc, argv);
  DEBUG(result.arguments_string());
}