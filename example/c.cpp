#include <iostream>

#include "../include/cxxopts.hpp"

int
main(int argc, const char* argv[])
{
  std::cout << "Started\n";
  cxxopts::Options options("MyProgram", "One line description of MyProgram");

  //-··-d,·--debug2·······0123456789012345678␊
  //-·····················␊
  //-01234567890123456789012345678901234567890
  // Width 40 actually eats the last 9
  // TODO: Confirm this

  options.add_options()("d,debug2", "01234567890123456789") // a bool parameter
    ("debug3", "\n\n\n")                                    // a bool parameter
    ("debug4", "\nabc")                                     // a bool parameter
    ("debug5", "                                     abc")  // a bool parameter
    // Wrong. Space wrapping incorrectly
    // With width=40
    //-abc··abc··abc··abc·␊
    //-·abc··abc··abc··␊
    //-abc··abc··abc␊
    ("debug6",
     "abc  abc  abc  abc  abc  abc  abc  abc  abc  abc") // a bool parameter
    ("debug7", "abc\nabc\n\n\n\n\nabc")
    //-······--debug8·······a·a·a·a·a·a·a·a·a·␊
    //-·····················a·a·a·a·a·a·a·a·a·␊
    //-0123456789012345678901234567890123456789
    // Invalid width on values 40. Actuall taking 39 spaces
    // Also trailing spaces are not trimmed...
    ("debug8", "a a a a a a a a a a a a a a a a a a a a a a a a a a")
    // If you dont set tab_expansion, default settings
    // suck bad and don't wrap correctly
    //  this will very well expand beyond 40 width
    // This is a bit wierd. No clear fix write now
    // maybe always set tab expansion to true
    ("debug9", "a\ta\ta\ta\ta\ta\ta\ta\ta\ta")
    // TODO: This prints questions mark chars.
    // we do size++ for each char, maybe we don't handle unicode well
    ("d10", "😀😀😀😀😀😀😀😀😀😀😀😀😀😀")
    ("i,integer", "Int param",cxxopts::value<int>())
    ("f,file", "File name", cxxopts::value<std::string>())
    ("v,verbose", "Verbose output",
      cxxopts::value<bool>()->default_value("false"))("h,help", "Print usage");

  options.set_width(40);
  auto result = options.parse(argc, argv);
  if (1 || result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  std::cout << result.arguments_string() << std::endl;
}

/*

The function to format description is buggy

https://github.com/jarro2783/cxxopts/blob/c01a048d888608f546144a7b4187029ec05a6f17/include/cxxopts.hpp#L2176-L2301


There are many things wrong here, like doing `desc += " "; ` for some wired
reason, and many fragile stuff during iterations.

the function lack unit tests

*/