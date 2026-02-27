
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    ("o,option", "Opt", cxxopts::value<std::string>())
    ("x,xoption", "xOpt", cxxopts::value<std::string>())
    ("h,help", "Print usage")
    ;
  
  options.parse_positional({"option"});
  options.parse_positional({"xoption"});
  
  options.allow_unrecognised_options();
  auto result = options.parse(argc, argv);
  
  if(result.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  }
  std::cout << result.arguments_string() << std::endl;
  auto um = result.unmatched();
  for(int i=0; i<um.size(); ++i){
    std::cout << um[i] << std::endl;
  }
}