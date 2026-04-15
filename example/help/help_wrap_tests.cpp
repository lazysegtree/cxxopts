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

} // namespace

int
main()
{
  const auto failures = test_wrap();

  if (failures != 0)
  {
    std::cerr << failures << " wrap_text test(s) failed\n";
    return 1;
  }

  std::cout << "All wrap_text tests passed\n";
  return 0;
}
