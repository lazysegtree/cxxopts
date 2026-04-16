#ifndef CXXOPTS_HEADER
#define CXXOPTS_HEADER "../include/cxxopts.hpp"
#endif

#include CXXOPTS_HEADER

#include <iostream>
#include <string>
#include <vector>

namespace {

struct TestCase
{
  std::string name;
  std::string desc;
  std::size_t start;
  std::size_t allowed;
  bool tab_expansion;
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
test_format_description_regressions()
{
  const std::vector<TestCase> tests = {
    {
      "Long word does not drop trailing character",
      "01234567890",
      13,
      10,
      false,
      "0123456789\n"
      "             0"
    },
    {
      "Consecutive explicit newlines keep following text",
      "a\n\nb",
      13,
      10,
      false,
      "a\n"
      "\n"
      "             b"
    },
    {
      "Trailing newline does not create whitespace-only continuation",
      "abc\n",
      13,
      10,
      false,
      "abc\n"
    },
    {
      "Spaces before explicit newline are trimmed",
      "abc   \nxyz",
      13,
      10,
      false,
      "abc\n"
      "             xyz"
    },
  };

  auto failures = 0;

  for (const auto& tc : tests)
  {
    try
    {
      cxxopts::HelpOptionDetails option{
        "o",
        {"opt"},
        tc.desc,
        false,
        "",
        false,
        "",
        "",
        false,
        true
      };

      const auto actual = cxxopts::format_description(
        option,
        tc.start,
        tc.allowed,
        tc.tab_expansion
      );

      if (actual != tc.expected)
      {
        std::cerr << "FAIL: " << tc.name << '\n';
        std::cerr << "  desc:     \"" << escape(tc.desc) << "\"\n";
        std::cerr << "  start:    " << tc.start << '\n';
        std::cerr << "  allowed:  " << tc.allowed << '\n';
        std::cerr << "  expected: \"" << escape(tc.expected) << "\"\n";
        std::cerr << "  actual:   \"" << escape(actual) << "\"\n";
        ++failures;
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << "FAIL: " << tc.name << '\n';
      std::cerr << "  desc:     \"" << escape(tc.desc) << "\"\n";
      std::cerr << "  start:    " << tc.start << '\n';
      std::cerr << "  allowed:  " << tc.allowed << '\n';
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
  const auto failures = test_format_description_regressions();

  if (failures != 0)
  {
    std::cerr << failures << " format_description regression test(s) failed\n";
    return 1;
  }

  std::cout << "All format_description regression tests passed\n";
  return 0;
}
