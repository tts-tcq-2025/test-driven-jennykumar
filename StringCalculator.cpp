#include "StringCalculator.h"
#include "ExtractDelimiters.h"
#include "SplitNumbers.h"
#include "ParseandValidate.h"
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <numeric>

namespace {

//  Helper: Checks if input has a custom delimiter line
bool isCustomDelimiter(const std::string& input) {
    return input.rfind("//", 0) == 0;
}

//  Helper: Extracts header and remaining string
std::pair<std::string, std::string> parseHeaderAndBody(const std::string& input) {
    size_t newlinePos = input.find('\n');
    if (newlinePos == std::string::npos)
        throw std::invalid_argument("Invalid delimiter declaration.");

    std::string header = input.substr(2, newlinePos - 2);
    std::string body = input.substr(newlinePos + 1);
    return { header, body };
}

}   // namespace

std::pair<std::vector<std::string>, std::string> parseDelimitersAndNumbers(
const std::string& input) {
    std::vector<std::string> delimiters = {",", "\n"};
    std::string numbers = input;

    if (isCustomDelimiter(input)) {
        auto [header, body] = parseHeaderAndBody(input);
        delimiters = extractDelimiters(header);
        numbers = body;
    }

    return {delimiters, numbers};
}

int sumNumbers(const std::vector<int>& numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}

int StringCalculator::add(const std::string& input) {
    if (input.empty())
        return 0;

    auto [delimiters, numbers] = parseDelimitersAndNumbers(input);

    auto tokens = splitNumbers(numbers, delimiters);
    auto validNumbers = parseAndValidate(tokens);

    return sumNumbers(validNumbers);
}
