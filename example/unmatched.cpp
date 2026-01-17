
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    ("o,option", "Opt", cxxopts::value<std::string>())
    ;
  options.allow_unrecognised_options();  
  auto result = options.parse(argc, argv);
  if(result.count("option")) {
    auto val = result["option"].as<std::string>();
    std::cout << "--option sent as '"<< val << "'\n";
  }
  auto um = result.unmatched();
  for (const std::string &s : um) {
    std::cout << "Unmatched options '" << s << "'\n";
  }
}