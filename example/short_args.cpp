// No LLM
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    ("o,option", "Opt", cxxopts::value<std::string>()->implicit_value("implicit"))
    ;
  
  //const char* argvb[] = {"./a.out", "-o=hi"};
  
  auto res = options.parse(argc, argv)["option"].as<std::string>();
  std::cout << "option is '" << res << "'\n";
}