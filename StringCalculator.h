#pragma once
#include <string>
#include <vector>
#include <memory>
#include "DelimiterParser.h"
#include "NumberParser.h"
#include "Validator.h"

class DelimiterParser;
class NumberParser;
class Validator;

class StringCalculator {
 public:
    StringCalculator();
    int Add(const std::string& numbers);

 private:
    std::unique_ptr<DelimiterParser> delimiterParser;
    std::unique_ptr<NumberParser> numberParser;
    std::unique_ptr<Validator> validator;
};
