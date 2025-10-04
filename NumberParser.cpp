#include "NumberParser.h"
#include <sstream>
#include <vector>
#include <string>

std::vector<int> NumberParser::parse(const std::string& normalizedNumbers) {
    std::vector<int> nums;
    std::stringstream ss(normalizedNumbers);
    std::string num;

    while (std::getline(ss, num, ',')) {
        if (!num.empty()) {
            nums.push_back(std::stoi(num));
        }
    }
    return nums;
}
