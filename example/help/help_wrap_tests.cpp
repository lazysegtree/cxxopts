#include "../../include/cxxopts.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace {

struct TestCase
{
  std::string name;
  std::string text;
  std::size_t allowed;
  std::size_t start;
  std::string expected;
};

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
test_wrap()
{
  const std::vector<TestCase> tests = {
    {
      "Plain Newline",
      "\n",
      3,
      3,
      "\n"
    },
    {
      "Manual newlines",
      "abc\ndef\nghi",
      3,
      0,
      "abc\n"
      "def\n"
      "ghi"
    },
    {
      "Basic wrap",
      "abc def ghi",
      3,
      0,
      "abc\n"
      "def\n"
      "ghi"
    },
    {
      "Word splitting",
      "abcdefghi",
      3,
      0,
      "abc\n"
      "def\n"
      "ghi"
    },

    {
      "Clamping with manual newlines",
      "\na\n\nbcdef",
      3,
      3,
      "\n"
      "   a\n"
      "\n"
      "   bcd\n"
      "   ef"
    },
    {
      "Trailing newline is preserved",
      "abc\n",
      3,
      3,
      "abc\n"
    },
    {
      "Trailing spaces after final newline preserve newline",
      "abc\n   ",
      5,
      2,
      "abc\n"
    },
    {
      "Whitespace around final newline preserves blank line",
      "   \n   ",
      5,
      2,
      "\n"
    },
    {
      "Consecutive newlines stay consecutive",
      "a\n\nb",
      3,
      3,
      "a\n"
      "\n"
      "   b"
    },
    {
      "Leading spaces do not create blank lines",
      "   abc",
      3,
      3,
      "abc"
    },
    {
      "Exact fit with separating space stays on one line",
      "a b",
      3,
      0,
      "a b"
    },
    {
      "Exact fit with longer words stays on one line",
      "abc def",
      7,
      0,
      "abc def"
    },
    {
      "Exact fit with separating tab stays on one line",
      "a\tb",
      3,
      0,
      "a\tb"
    },
    {
      "Whitespace wrap keeps the trailing word",
      "abc def",
      4,
      2,
      "abc\n"
      "  def"
    },
    {
      "Empty string stays empty",
      "",
      3,
      0,
      ""
    },
    {
      "Whitespace only stays empty",
      "   ",
      3,
      2,
      ""
    },
    {
      "Exact fit word stays on one line",
      "abc",
      3,
      0,
      "abc"
    },
    {
      "Internal spaces are preserved when no wrap is needed",
      "a   b",
      10,
      0,
      "a   b"
    },
    {
      "Whitespace runs at wrap boundaries keep all words",
      "23423   23424      343",
      10,
      3,
      "23423\n"
      "   23424\n"
      "   343"
    },
    {
      "Wrapped line followed by newline",
      "abcd\n",
      3,
      2,
      "abc\n"
      "  d\n"
    },
    {
      "Wrapped line followed by newline 2",
      "abcd\nef",
      3,
      2,
      "abc\n"
      "  d\n"
      "  ef"
    },
    {
      "Edge case of minimum width",
      "abc\n\nx  y\n  z",
      1,
      1,
      "a\n"
      " b\n"
      " c\n"
      "\n"
      " x\n"
      " y\n"
      " z"
    },
    {
      "0 allowed",
      "abc",
      0,
      1,
      "",
    },
    {
      "trailing spaces before an explicit newline",
      "abc   \nxyz",
      5,
      0,
      "abc\n"
      "xyz"
    },
    {
      "Consecutive trailing newlines are preserved",
      "a\n\n",
      3,
      2,
      "a\n"
      "\n"
    }
  };

  auto failures = 0;

  for (const auto& tc : tests)
  {
    try
    {
      auto actual = cxxopts::wrap_text(tc.text, tc.allowed, tc.start);
      if (actual != tc.expected)
      {
        std::cerr << "FAIL: " << tc.name << '\n';
        std::cerr << "  input:    \"" << escape(tc.text) << "\"\n";
        std::cerr << "  allowed:  " << tc.allowed << '\n';
        std::cerr << "  start:    " << tc.start << '\n';
        std::cerr << "  expected: \"" << escape(tc.expected) << "\"\n";
        std::cerr << "  actual:   \"" << escape(actual) << "\"\n";
        ++failures;
        //std::exit(0);
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << "FAIL: " << tc.name << '\n';
      std::cerr << "  input:    \"" << escape(tc.text) << "\"\n";
      std::cerr << "  allowed:  " << tc.allowed << '\n';
      std::cerr << "  start:    " << tc.start << '\n';
      std::cerr << "  exception: " << e.what() << '\n';
      ++failures;

        //std::exit(0);
    }
  }

  return failures;
}

int
test_full()
{
  struct {
    std::string name;
    cxxopts::Options parser;
    std::vector<std::pair<std::string, std::string>> opts;
    std::vector<std::string> positionals;
    std::string expected;
  } tests[] = {
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
      for(auto opt : tc.opts) {
        tc.parser.add_options()(opt.first, opt.second);
      }
      tc.parser.parse_positional(tc.positionals);

      auto actual = tc.parser.help();;
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
  auto failures = test_wrap();

  if (failures != 0)
  {
    std::cerr << failures << " wrap_text test(s) failed\n";
    return 1;
  }
  failures = test_full();
  if (failures != 0)
  {
    std::cerr << failures << " full_help test(s) failed\n";
    return 1;
  }

  std::cout << "All wrap_text and full_help tests passed\n";
  return 0;
}
