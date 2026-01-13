#include <iostream>
#include "debug.h"

#define CXXOPTS_VECTOR_DELIMITER ';'

#include "../include/cxxopts.hpp"

int main(int argc, const char* argv[])
{
  DEBUG(argc);
  for (int i=0; i<argc; i++){
    DEBUG(i, argv[i]);
  }
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    ("vs", "Vector of string", cxxopts::value<std::vector<std::string>>())
    ;

  auto result = options.parse(argc, argv);
  auto res = result["vs"];
  auto val = res.as< std::vector<std::string >>();

  DEBUG(val.size(), val);

  //std::cout << result.arguments_string() << std::endl;
}