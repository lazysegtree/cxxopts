
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int argc, const char* argv[])
{
  for(int i=0; i<argc; i++){
    DEBUG(i, argv[i]);
  }
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    ("vo", "Vector", cxxopts::value<std::vector<std::string>>())
    ("o,option", "Opt", cxxopts::value<std::vector<std::string>>())
    ("o2,option2", "Opt2", cxxopts::value<std::vector<std::string>>())
    ("h,help", "Print usage")
    ;
  options.parse_positional({"o"});
  options.parse_positional({"o", "o2"});
  auto result = options.parse(argc, argv);

  if(result.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  }
  if(result.count("option")) {
    auto val = result["option"].as<std::vector<std::string>>();
    DEBUG(val.size(), val);
  }
  if(result.count("vo")) {
    auto val = result["vo"].as<std::vector<std::string>>();
    DEBUG(val.size(), val);
  }

  std::cout << result.arguments_string() << std::endl;
}