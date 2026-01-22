#include <iostream>
#include <regex>
#include "debug.h"

#include "../include/cxxopts.hpp"

int main(int argc, const char* argv[])
{
  // ^[_[:alpha:]][_[:alnum:]]*$
  // std::regex pat{"(A)*(B*)"};
  std::string p = "--([[:alnum:]][-_[:alnum:]\\.]+)(=(.*))?" "|" 
    "-([[:alnum:]])(=(.*)|(.*))";
  std::vector<std::pair<std::string, std::string>> vm = {
    //{"(.*?)", "AB"},
    //{"A", "AB"},
    //{"X(AB?)", "X"},
    //{"X(AB?)", "XA"},
    //{R"(<(.*?)>(.*?)</(.*?)>)", "<b>dark</b> side of <b>life</b>"},
    //{R"(<(.*?)>(.*?)</\1>)", "<b>dark</b> side of <b>life</b>"},
    //{R"(<(.*)>(.*)</(.*)>)", "<b>dark</b> side of <b>life</b>"},
    //{R"(.*<(.*)>(.*)</(.*)>.*)", "Be wary of <b>dark</b> side of <b>life</b>."},
    //{R"(<(.*)>(.*)</\1>)", "<b>dark</b> side of <b>life</b>"},
    {p, "-o=hi"},
    {p, "--option=hi"},
    {p, "--option"},
    {p, "-abo"},
    {p, "-abo=hi"},
  };
  

  for (auto p : vm) {
    std::regex pat(p.first);
    std::smatch match;
    std::regex_match(p.second, match, pat);

    DEBUG(p.first, p.second);

    for(int i=0; i<match.size(); i++) {
      DEBUG(i, match[i], match[i].matched);
    }
  }


  std::vector<std::pair<std::string, std::string>> vs = {
    {"A", "AAB"},
    {R"(<(.*?)>(.*?)</(.*?)>)", "<b>dark</b> side of <b>life</b>"},
    //{R"(<(.*?)>(.*?)</\1>)", "<b>dark</b> side of <b>life</b>"},
    //{R"(<(.*)>(.*)</(.*)>)", "<b>dark</b> side of <b>life</b>"},
    //{R"(.*<(.*)>(.*)</(.*)>.*)", "Be wary of <b>dark</b> side of <b>life</b>."},
    //{R"(<(.*)>(.*)</\1>)", "<b>dark</b> side of <b>life</b>"},
  };

  std::cout << "----------------\n";

  for (auto p : vs) {
    DEBUG(p.first, p.second);

    std::regex pat(p.first);
    std::smatch match;
    std::regex_search(p.second, match, pat);


    for(int i=0; i<match.size(); i++) {
      DEBUG(i, match[i], match[i].matched);
    }
  }
}
