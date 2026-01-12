#include <iostream>
#include "debug.h"
#include "../include/cxxopts.hpp"

int
main(int argc, const char* argv[])
{
  DEBUG(argc);
  for (int i=0; i<argc; i++){
    std::cout << "argv[i] = '" << argv[i] << "'\n";
  }
  std::cout << "Started\n";
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
    //("b,bool", "Bool parameter")
    //("i,integer", "Integer param", cxxopts::value<int>())
    ("a,alpha,beta,gamma,delta", "Integer param with many names", cxxopts::value<int>())
    ("alphac,betac,c,gammac", "Integer param with many names", cxxopts::value<int>())
    ("d,alphad,betad,gammad", "Integer param with many names", cxxopts::value<int>())
    ("alphae,betae,gammae,e", "Integer param with many names", cxxopts::value<int>())
    ("o,one,two,three,four,five", "Second integer param with many names", cxxopts::value<int>())
    ("f,first,second", "Third integer param with many names", cxxopts::value<int>())
    ("s,string", "string parameter", cxxopts::value<std::string>())
    ("vs", "Vector of string", cxxopts::value<std::vector<std::string>>())
    ("v,verbose", "Verbose output",cxxopts::value<bool>()->default_value("false"))
    ("h,help", "Print usage");

  auto grp = options.group_help("");
  for (int i=0; i<grp.options.size(); i++){
    DEBUG(i, grp.options[i].s, grp.options[i].l);
  }
  
  
  auto result = options.parse(argc, argv);

  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  auto res = result["vs"];
  auto val = res.as< std::vector<std::string >>();

  DEBUG(val);

  std::cout << result.arguments_string() << std::endl;
}