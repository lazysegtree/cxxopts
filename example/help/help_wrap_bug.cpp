#include "../../include/cxxopts.hpp"
#include <iostream>

int
main(int argc, const char* argv[])
{

  cxxopts::Options options("MyProgram", "One line description of MyProgram");
  options.add_options()
    ("d,debug2", "01234567890123456789") // a bool parameter
    ("h,help", "Print usage");

  options.set_width(21);

  auto result = options.parse(argc, argv);
  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  std::cout << result.arguments_string() << std::endl;
}