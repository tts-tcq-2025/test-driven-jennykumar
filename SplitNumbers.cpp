#include "SplitNumbers.h"
#include <vector>
#include <string>
#include <regex>

std::vector<std::string> splitNumbers
(const std::string& input, const std::vector<std::string>& delimiters) {
    std::string pattern = "(";
    for (size_t i = 0; i < delimiters.size(); ++i) {
        std::string escaped = std::regex_replace(delimiters[i], std::regex(R"([\[\]\*\+\?\^\$\\\.\|\(\)])"), R"(\\$&)");
        pattern += escaped;
        if (i < delimiters.size() - 1) pattern += "|";
    }
    pattern += ")";
    std::regex re(pattern);
    std::sregex_token_iterator it(input.begin(), input.end(), re, -1);
    std::sregex_token_iterator end;
    return { it, end };
}
