#include "../include/cxxopts.hpp"
#include <iostream>

int
main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram2", "Sample argument parsing");
  options.custom_help("\nCustom help .....\nLine2");
  options.add_options("grp1")
    ("i,integer", "Integer param", cxxopts::value<int>())
    ("h,help", "Print usage");
  auto result = options.parse(argc, argv);
  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  std::cout << result.arguments_string() << std::endl;
}