// No LLM
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    ("o,?,option", "Opt", cxxopts::value<std::string>()->no_implicit_value())
    ;
  
  //const char* argvb[] = {"./a.out", "-o=hi"};
  //options.allow_unrecognised_options();
  auto result = options.parse(argc, argv);
  auto res = result["option"].as<std::string>();
  std::cout << "option is '" << res << "'\n";
  DEBUG(result.arguments_string());
}