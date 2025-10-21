#pragma once
#include <vector>
#include <string>

#ifdef __cplusplus
extern "C++" {
std::vector<std::string> splitNumbers(
    const std::string& input,
    const std::vector<std::string>& delimiters
);
};

#endif
