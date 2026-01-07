#include <iostream>

#include "../include/cxxopts.hpp"

int
main(int argc, const char* argv[])
{
  std::cout << "Started\n";
    cxxopts::Options options("MyProgram", "One line description of MyProgram");
    options.add_options()
  ("d,debug2", "01234567890123456789") // a bool parameter
  ("i,integer", "Int param", cxxopts::value<int>())
  ("f,file", "File name", cxxopts::value<std::string>())
  ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
  ("h,help", "Print usage");

  options.set_width(40);
  auto result = options.parse(argc, argv);
  if (1||result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  std::cout << result.arguments_string() << std::endl;
}

/*

The function to format description is buggy

https://github.com/jarro2783/cxxopts/blob/c01a048d888608f546144a7b4187029ec05a6f17/include/cxxopts.hpp#L2176-L2301


There are many things wrong here, like doing `desc += " "; ` for some wired reason, and many fragile stuff during iterations. 

the function lack unit tests

*/