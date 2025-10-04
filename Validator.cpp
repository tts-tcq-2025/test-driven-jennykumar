#include "Validator.h"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>

void Validator::validate(const std::vector<int>& nums) {
    std::vector<int> negatives = findNegativeNumbers(nums);
    if (!negatives.empty()) {
        throw std::invalid_argument(buildNegativeNumbersMessage(negatives));
    }
}

std::vector<int> Validator::findNegativeNumbers(const std::vector<int>& nums) {
    std::vector<int> negatives;
    std::copy_if(nums.begin(), nums.end(), std::back_inserter(negatives),
                 [](int num) { return num < 0; });
    return negatives;
}

std::string Validator::buildNegativeNumbersMessage(const std::vector<int>& negatives) {
    std::string message = "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        if (i > 0) message += ", ";
        message += std::to_string(negatives[i]);
    }
    return message;
}
