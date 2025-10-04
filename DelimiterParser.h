#pragma once
#include <string>

class DelimiterParser {
 public:
    std::string parse(const std::string& numbers);
    std::string extractNumbers(const std::string& numbers);
    std::string normalize(const std::string& numbersPart, const std::string& delimiter);

 private:
    bool hasCustomDelimiterFormat(const std::string& numbers);
    std::string extractDelimiterFromHeader(const std::string& delimiterPart);
    bool hasBracketFormat(const std::string& delimiterPart);
    std::string extractNumbersAfterDelimiterHeader(const std::string& numbers);
    std::string replaceDelimiterWithComma(const std::string& text, const std::string& delimiter);
};
