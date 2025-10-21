#include "ExtractDelimiters.h"
#include <vector>
#include <string>
#include <regex>

std::vector<std::string> extractDelimiters(const std::string& header) {
    std::vector<std::string> delimiters;
    std::regex multiDelim(R"(\[(.*?)\])");

    auto begin = std::sregex_iterator(header.begin(), header.end(), multiDelim);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
        delimiters.push_back((*it)[1]);

    if (delimiters.empty())
        delimiters.push_back(header);  // single-char delimiter

    return delimiters;
}
