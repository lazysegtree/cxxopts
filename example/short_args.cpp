// No LLM
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int , const char* [])
{
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    ("h,help", "Helps", cxxopts::value<std::vector<std::string>>()->implicit_value(""))
    ;

  int argc = 3;
  const char* argv[] = {"./a.out", "-h", "1,2"};
  auto result = options.parse(argc, argv);
  auto res = result["help"];
  auto val = res.as< std::vector<std::string >>();

  DEBUG(val.size(), val);

  //std::cout << result.arguments_string() << std::endl;
}