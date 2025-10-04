#include "DelimiterParser.h"
#include <regex>
#include <algorithm>
#include <string>

std::string DelimiterParser::parse(const std::string& numbers) {
    if (!hasCustomDelimiterFormat(numbers)) {
        return ",";
    }

    size_t newlinePos = numbers.find('\n');
    if (newlinePos == std::string::npos) {
        return ",";
    }

    return extractDelimiterFromHeader(numbers.substr(2, newlinePos - 2));
}

bool DelimiterParser::hasCustomDelimiterFormat(const std::string& numbers) {
    return numbers.length() >= 4 && numbers.substr(0, 2) == "//";
}

std::string DelimiterParser::extractDelimiterFromHeader(const std::string& delimiterPart) {
    if (hasBracketFormat(delimiterPart)) {
        return delimiterPart.substr(1, delimiterPart.length() - 2);
    }
    return delimiterPart;
}

bool DelimiterParser::hasBracketFormat(const std::string& delimiterPart) {
    return delimiterPart.length() >= 2 &&
           delimiterPart[0] == '[' &&
           delimiterPart[delimiterPart.length() - 1] == ']';
}

std::string DelimiterParser::extractNumbers(const std::string& numbers) {
    if (!hasCustomDelimiterFormat(numbers)) {
        return numbers;
    }
    return extractNumbersAfterDelimiterHeader(numbers);
}

std::string DelimiterParser::extractNumbersAfterDelimiterHeader(const std::string& numbers) {
    size_t newlinePos = numbers.find('\n');
    if (newlinePos == std::string::npos || newlinePos + 1 >= numbers.length()) {
        return numbers;
    }
    return numbers.substr(newlinePos + 1);
}

std::string DelimiterParser::normalize(const std::string& numbersPart,
                                       const std::string& delimiter) {
    std::string result = numbersPart;
    if (delimiter != ",") {
        result = replaceDelimiterWithComma(result, delimiter);
    }
    std::replace(result.begin(), result.end(), '\n', ',');
    return result;
}

std::string DelimiterParser::replaceDelimiterWithComma(const std::string& text,
                                                       const std::string& delimiter) {
    std::string escapedDelimiter = delimiter;
    std::regex specialChars(R"([-[\]{}()*+?.,\^$|#\s])");
    escapedDelimiter = std::regex_replace(escapedDelimiter, specialChars, R"(\$&)");

    std::regex delimiterRegex(escapedDelimiter);
    return std::regex_replace(text, delimiterRegex, ",");
}
