#include "../include/cxxopts.hpp"
#include <iostream>

int
main(int argc, const char* argv[])
{
  std::cout << "Started\n";
  cxxopts::Options options("TestProgram2", "Sample argument parsing");
  options.add_options("grp1")
    ("b,bool", "Bool parameter")
    ("i,integer", "Integer param", cxxopts::value<int>())
    ("s,string", "string parameter", cxxopts::value<std::string>())
    ("v,verbose", "Verbose output",cxxopts::value<bool>()->default_value("false"))
    ("h,help", "Print usage");
  
  // Doubt - how was grp1 even allowed here?
  options.add_options("grp2")
    ("x,xvec", "Vector Parameter", cxxopts::value<std::vector<std::string>>() )
    ("y,yvec", "Vector Parameter 2", cxxopts::value<std::vector<std::string>>() );

  
  
  
  auto result = options.parse(argc, argv);
  std::vector<std::string> vs = {"grp1", "grp2"};
  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  std::cout << result.arguments_string() << std::endl;
}