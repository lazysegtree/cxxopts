#ifndef DEBUGH
#define DEBUGH

#include <iostream>
#ifndef ONLINE_JUDGE
    #define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else 
    #define DEBUG(...) 
#endif

template<typename T, typename S> std::ostream& operator << (std::ostream &os, const std::pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = std::decay<decltype(*std::begin(std::declval<C>()))>, typename std::enable_if<!std::is_same<C, std::string>::value>::type* = nullptr>
std::ostream& operator << (std::ostream &os, const C &c) {bool f = true; os << "["; 
for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;}return os << "]";}
template<typename T> void debug(std::string s, T x) {std::cout << "" << s << " = " << x << "\n";}
template<typename T, typename... Args> void debug(std::string s, T x, Args... args) 
{for (int i=0, b=0; i<(int)s.size(); i++) {if (s[i] == '(' || s[i] == '{') b++; else if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {
std::cout<< s.substr(0, i) << " = " << x << " | ";debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}}

#endif