#ifndef string_helper_h
#define string_helper_h

#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

/**
 * @brief Split given string with given delimiter
 */
extern vector<std::string> split(const string &s, char delimiter);

#endif