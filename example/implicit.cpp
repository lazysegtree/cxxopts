// No LLM
#include <iostream>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int , const char* [])
{
  cxxopts::Options options1("TestProgram", "Sample argument parsing");
  options1.add_options()
    ("option", "Opt", cxxopts::value<std::string>()->implicit_value("implicit"))
    ;
  cxxopts::Options options2("TestProgram", "Sample argument parsing");
  options2.add_options()
    ("option", "Opt", cxxopts::value<std::string>())
    ;

  const char* argva[] = {"./a.out", "--option", "another"};
  const char* argvb[] = {"./a.out", "--option=another"};


  auto res1a = options1.parse(3, argva)["option"].as<std::string>();
  auto res2a = options2.parse(3, argva)["option"].as<std::string>();
  auto res1b = options1.parse(2, argvb)["option"].as<std::string>();
  auto res2b = options2.parse(2, argvb)["option"].as<std::string>();

  std::cout << "(without  implicit_value, with --option another ) option is '" << res2a << "'\n";
  std::cout << "(without  implicit_value, with --option=another ) option is '" << res2b << "'\n";

  std::cout << "(with     implicit_value, with --option=another ) option is '" << res1b << "'\n";
  std::cout << "(with     implicit_value, with --option another ) option is '" << res1a << "'\n";

}