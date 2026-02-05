// No LLM
#include <iostream>
#include "../debug.h"

#include "CLI11.hpp"

int main(int argc, const char* argv[])
{
    CLI::App app{"App description"};

    std::string filename = "default";
    bool help = false;
    bool help2 = false;
    app.add_option("-f,--file", filename, "A help string");
    app.add_option("-?,--??,--help?", help, "show_help")->default_val(true);
    app.add_option("-&,--$$,--))?,-#", help2, "show_help")->default_val(true);

    CLI11_PARSE(app, argc, argv);

    if(help) {
        std::cout << "Help me" << std::endl;
    }
    if(help2) {
        std::cout << "Help me 2" << std::endl;
    }
    return 0;
}

/*
```
➜  cxxopts git:(lazysegtree) ✗ g++ example/cli11/ques.cpp && ./a.out --help
App description


./a.out [OPTIONS]


OPTIONS:
  -h,     --help              Print this help message and exit
  -f,     --file TEXT         A help string
  -?,     --??, --help? BOOLEAN [1]
                              show_help
  -&, -#, --$$, --))? BOOLEAN [1]
                              show_help
➜  cxxopts git:(lazysegtree) ✗ g++ example/cli11/ques.cpp && ./a.out --help\? true --\)\)\? true
Help me
Help me 2
➜  cxxopts git:(lazysegtree) ✗
```
*/