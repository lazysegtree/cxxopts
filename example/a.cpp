#include <iostream>

#include "../include/cxxopts.hpp"

int
main(int argc, const char* argv[])
{
  std::cout << "Started\n";
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    ("b,bool", "Bool parameter")
    ("i,integer", "Integer param", cxxopts::value<int>())
    ("s,string", "string parameter", cxxopts::value<std::string>())
    ("v,verbose", "Verbose output",cxxopts::value<bool>()->default_value("false"))
    ("h,help", "Print usage");
  
  
  auto result = options.parse(argc, argv);

  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  std::cout << result.arguments_string() << std::endl;
}