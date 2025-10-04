#include <gtest/gtest.h>
#include "StringCalculator.h"
#include <stdexcept>
#include <string>

// ----------------------------
// Shared Test Data Structures
// ----------------------------
struct TestCaseData {
    std::string input;
    int expected;
    std::string description;
};

struct InvalidCaseData {
    std::string input;
    std::string expectedMessage;
    std::string description;
};

// ----------------------------
// Test Fixtures
// ----------------------------
class StringCalculatorTest : public ::testing::Test {
 protected:
    StringCalculator calculator;
};

// ----------------------------
// Utility Helpers
// ----------------------------
void ExpectAddResult(StringCalculator& calc, const TestCaseData& data) {
    EXPECT_EQ(data.expected, calc.Add(data.input))
        << "Failed for: " << data.description;
}

void ExpectThrowsInvalidArgument(StringCalculator& calc, const InvalidCaseData& data) {
    try {
        calc.Add(data.input);
        FAIL() << "Expected std::invalid_argument for: " << data.description;
    } catch (const std::invalid_argument& e) {
        std::string message = e.what();
        EXPECT_NE(message.find("negatives not allowed"), std::string::npos)
            << "Message should contain 'negatives not allowed' for: " << data.description;
        EXPECT_NE(message.find(data.expectedMessage), std::string::npos)
            << "Message should contain '" << data.expectedMessage << "' for: " << data.description;
    }
}

// ----------------------------
// Empty Input Test
// ----------------------------
TEST_F(StringCalculatorTest, EmptyStringReturnsZero) {
    EXPECT_EQ(0, calculator.Add(""));
}

// ----------------------------
// Basic Addition Tests
// ----------------------------
class BasicAdditionTest : public ::testing::TestWithParam<TestCaseData> {
 protected:
    StringCalculator calculator;
};

TEST_P(BasicAdditionTest, HandlesVariousInputs) {
    ExpectAddResult(calculator, GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    SingleAndMultipleNumbers,
    BasicAdditionTest,
    ::testing::Values(
        TestCaseData{"1", 1, "single number"},
        TestCaseData{"5", 5, "single digit"},
        TestCaseData{"42", 42, "double digit"},
        TestCaseData{"1,2", 3, "two numbers with comma"},
        TestCaseData{"3,4", 7, "different two numbers"},
        TestCaseData{"8,7", 15, "larger two numbers"},
        TestCaseData{"1,2,3", 6, "three numbers"},
        TestCaseData{"1,2,3,4", 10, "four numbers"},
        TestCaseData{"1,2,3,4,5", 15, "five numbers"}
    )
);

// ----------------------------
// Delimiter Tests
// ----------------------------
class DelimiterTest : public ::testing::TestWithParam<TestCaseData> {
 protected:
    StringCalculator calculator;
};

TEST_P(DelimiterTest, HandlesVariousDelimiters) {
    ExpectAddResult(calculator, GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    AllDelimiterTypes,
    DelimiterTest,
    ::testing::Values(
        TestCaseData{"1\n2,3", 6, "mixed newline and comma"},
        TestCaseData{"1\n2\n3,4", 10, "multiple newlines with comma"},
        TestCaseData{"//;\n1;2", 3, "semicolon delimiter"},
        TestCaseData{"//*\n1*2*3", 6, "asterisk delimiter"},
        TestCaseData{"//|\n1|2|3|4", 10, "pipe delimiter"},
        TestCaseData{"//[***]\n1***2***3", 6, "triple asterisk delimiter"},
        TestCaseData{"//[abc]\n1abc2abc3abc4", 10, "text delimiter"},
        TestCaseData{"//[::]\n1::2::3::4::5", 15, "double colon delimiter"}
    )
);

// ----------------------------
// Large Number Filtering Tests
// ----------------------------
class LargeNumberFilterTest : public ::testing::TestWithParam<TestCaseData> {
 protected:
    StringCalculator calculator;
};

TEST_P(LargeNumberFilterTest, FiltersLargeNumbers) {
    ExpectAddResult(calculator, GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    NumberFiltering,
    LargeNumberFilterTest,
    ::testing::Values(
        TestCaseData{"2,1001", 2, "number over 1000 ignored"},
        TestCaseData{"1000,2", 1002, "exactly 1000 included"},
        TestCaseData{"1,2,1001,9999", 3, "multiple large numbers ignored"},
        TestCaseData{"1000", 1000, "exactly 1000 alone"},
        TestCaseData{"1001", 0, "exactly 1001 ignored"},
        TestCaseData{"0,5,0", 5, "zero values included"}
    )
);

// ----------------------------
// Negative Number Tests
// ----------------------------
class NegativeNumberTest : public ::testing::TestWithParam<InvalidCaseData> {
 protected:
    StringCalculator calculator;
};

TEST_P(NegativeNumberTest, ThrowsOnNegativeNumbers) {
    ExpectThrowsInvalidArgument(calculator, GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    NegativeValidation,
    NegativeNumberTest,
    ::testing::Values(
        InvalidCaseData{"-1", "-1", "single negative number"},
        InvalidCaseData{"1,-2", "-2", "negative in middle"},
        InvalidCaseData{"1,-2,-3,4", "-2", "multiple negatives (check first)"},
        InvalidCaseData{"-5,-10", "-5", "multiple negatives only"}
    )
);

// ----------------------------
// Integration & Edge Cases
// ----------------------------
TEST_F(StringCalculatorTest, ComplexScenarioIntegrationTest) {
    EXPECT_EQ(6, calculator.Add("//[***]\n1***2***3***1001"));
    EXPECT_EQ(15, calculator.Add("1\n2,3\n4,5"));
}
