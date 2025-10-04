#pragma once
#include <vector>
#include <string>

class Validator {
 public:
    void validate(const std::vector<int>& nums);

 private:
    std::vector<int> findNegativeNumbers(const std::vector<int>& nums);
    std::string buildNegativeNumbersMessage(const std::vector<int>& negatives);
};
