#include "../../include/cxxopts.hpp"
#include <iostream>

int
main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram2", "Sample argument parsing with a long description");
  options.custom_help("\nCustom help ..... line 1 with a long long value. 1234567890\nLine2");
  options.add_options("grp1")
    ("i,integer", "Integer param with a long long description", cxxopts::value<int>())
    ("very-long-integer-option-that-will-cause-issues", "Integer param with a long long description", cxxopts::value<int>())
    ("h,help", "Print usage. This will help your soul to understand the magics of this program");
  
  options.set_width(5);

  auto result = options.parse(argc, argv);
  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  std::cout << result.arguments_string() << std::endl;
}