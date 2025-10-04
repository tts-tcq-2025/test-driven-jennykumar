#include "StringCalculator.h"
#include "DelimiterParser.h"
#include "NumberParser.h"
#include "Validator.h"
#include <numeric>
#include <string>
#include <vector>

StringCalculator::StringCalculator()
    : delimiterParser(std::make_unique<DelimiterParser>()),
      numberParser(std::make_unique<NumberParser>()),
      validator(std::make_unique<Validator>()) {}

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiter = delimiterParser->parse(numbers);
    std::string numbersPart = delimiterParser->extractNumbers(numbers);
    std::string normalizedNumbers = delimiterParser->normalize(numbersPart, delimiter);

    std::vector<int> nums = numberParser->parse(normalizedNumbers);

    validator->validate(nums);

    return std::accumulate(nums.begin(), nums.end(), 0, [](int sum, int n) {
        return n <= 1000 ? sum + n : sum;
    });
}
