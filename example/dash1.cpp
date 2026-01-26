#include <iostream>
#include "debug.h"
#include "../include/cxxopts.hpp"


void another_cli_parse(int argc, const char* argv[]) {
  std::cout << "In another_cli_parse()\n"; 
  DEBUG(argc);
  for (int i=0; i<argc; i++){
    std::cout << "argv[i] = '" << argv[i] << "'\n";
  }
}

int
main(int argc, const char* argv[])
{
  DEBUG(argc);
  for (int i=0; i<argc; i++){
    std::cout << "argv[i] = '" << argv[i] << "'\n";
  }
  cxxopts::Options options("TestProgram", "Sample argument parsing");
  options.add_options()
  ("input", "Input files", cxxopts::value<std::vector<std::string>>());

  options.allow_unrecognised_options();
  
  auto result = options.parse(argc, argv);
  auto inp = result["input"].as<std::vector<std::string>>();

  DEBUG(inp.size(), inp);
  auto res = result.unmatched();
  DEBUG(res);

  if (res.size() > 0) {
    std::cout << "Got '" << res.size() << "' extra arguments\n";
    another_cli_parse(res.size()+1, &argv[argc - res.size()-1] );
  } 

  std::cout << "argv afterwards\n" ;

  DEBUG(argc);
  for (int i=0; i<argc; i++){
    std::cout << "argv[i] = '" << argv[i] << "'\n";
  }

}