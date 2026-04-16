#include "../../include/cxxopts.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace {

std::string
escape(const std::string& text)
{
  std::string escaped;
  escaped.reserve(text.size());

  for (char ch : text)
  {
    switch (ch)
    {
    case '\n':
      escaped += "\\n";
      break;

    case '\t':
      escaped += "\\t";
      break;

    default:
      escaped += ch;
      break;
    }
  }

  return escaped;
}

int
test_full()
{
  struct TestCase
  {
    std::string name;
    cxxopts::Options parser;
    std::vector<std::pair<std::string, std::string>> opts;
    std::vector<std::string> positionals;
    std::string expected;
  };

  TestCase tests[] = {
    {
      "Basic test",
      cxxopts::Options("prog_abc", "This is a sample program for snake jazz")
        .positional_help("Positional help")
        .custom_help("Custom help")
        .set_width(15),
      {{"o,opt", "Sample description"}},
      {"o"},
      "This is a\n"
      "sample program\n"
      "for snake jazz\n"
      "Usage:\n"
      "prog_abc Custom\n"
      "help Positional\n"
      "help\n"
      "\n"
      "  -o, --opt  Sample\n"
      "             descriptio\n"
      "             n\n"
    },
    {
      "Custom help manual newline",
      cxxopts::Options("prog")
        .custom_help("Custom\nHelp")
        .set_width(12),
      {{"o,opt", "desc"}},
      {},
      "\n"
      "Usage:\n"
      "prog Custom\n"
      "Help\n"
      "\n"
      "  -o, --opt  desc\n"
    },
    {
      "Description spaces before explicit newline",
      cxxopts::Options("prog")
        .set_width(18),
      {{"o,opt", "alpha   \nbeta"}},
      {},
      "\n"
      "Usage:\n"
      "prog [OPTION...]\n"
      "\n"
      "  -o, --opt  alpha\n"
      "             beta\n"
    },
    {
      "Description blank line is preserved",
      cxxopts::Options("prog")
        .set_width(18),
      {{"o,opt", "alpha\n\nbeta"}},
      {},
      "\n"
      "Usage:\n"
      "prog [OPTION...]\n"
      "\n"
      "  -o, --opt  alpha\n"
      "\n"
      "             beta\n"
    },
    {
      "Description trailing newline is preserved",
      cxxopts::Options("prog")
        .set_width(18),
      {{"o,opt", "alpha\n"}},
      {},
      "\n"
      "Usage:\n"
      "prog [OPTION...]\n"
      "\n"
      "  -o, --opt  alpha\n"
      "\n"
    },
    {
      "Description leading newline is preserved",
      cxxopts::Options("prog")
        .set_width(18),
      {{"o,opt", "\nalpha"}},
      {},
      "\n"
      "Usage:\n"
      "prog [OPTION...]\n"
      "\n"
      "  -o, --opt  \n"
      "             alpha\n"
    },
    {
      "Custom help trailing newline is preserved",
      cxxopts::Options("prog")
        .custom_help("Custom\n")
        .set_width(12),
      {{"o,opt", "desc"}},
      {},
      "\n"
      "Usage:\n"
      "prog Custom\n"
      "\n"
      "\n"
      "  -o, --opt  desc\n"
    },
    {
      "Tab expansion happens before description wrapping",
      cxxopts::Options("prog")
        .set_width(26)
        .set_tab_expansion(true),
      {{"o,opt", "a\tb"}},
      {},
      "\n"
      "Usage:\n"
      "prog [OPTION...]\n"
      "\n"
      "  -o, --opt  a       b\n"
    },
  };

  auto failures = 0;

  for (auto& tc : tests)
  {
    try
    {
      for (const auto& opt : tc.opts)
      {
        tc.parser.add_options()(opt.first, opt.second);
      }
      tc.parser.parse_positional(tc.positionals);

      const auto actual = tc.parser.help();
      if (actual != tc.expected)
      {
        std::cerr << "FAIL: " << tc.name << '\n';
        std::cerr << "  expected: \"" << escape(tc.expected) << "\"\n";
        std::cerr << "  actual:   \"" << escape(actual) << "\"\n";
        ++failures;
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << "FAIL: " << tc.name << '\n';
      std::cerr << "  exception: " << e.what() << '\n';
      ++failures;
    }
  }

  return failures;
}

} // namespace

int
main()
{
  const auto failures = test_full();

  if (failures != 0)
  {
    std::cerr << failures << " full_help test(s) failed\n";
    return 1;
  }

  std::cout << "All full_help tests passed\n";
  return 0;
}
