#include "../../include/cxxopts.hpp"
#include <iostream>

int
main(int argc, const char* argv[])
{
  cxxopts::Options options("TestProgram2", "Sample argument parsing with a long description");
  options.custom_help("\nCustom help ..... line 1 with a long long value. 1234567890\nLine2");
  
  options.set_width(5);

  std::cout << options.help() << std::endl;
}