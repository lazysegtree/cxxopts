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
