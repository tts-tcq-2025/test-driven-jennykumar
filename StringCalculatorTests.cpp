#include <string>
#include "StringCalculator.h"
#include <iostream>

void test(const std::string& desc, const std::string& input, int expected) {
    StringCalculator calc;
    try {
        int result = calc.add(input);
        if (result == expected)
            std::cout << "[PASS] " << desc << ": " << result << "\n";
        else
            std::cout << "[FAIL] " << desc
            << ": Expected " << expected
            << ", got " << result
            << "\n";
    } catch (const std::exception& ex) {
        std::cout << "[EXCEPTION] " << desc << ": " << ex.what() << "\n";
    }
}

int main() {
    test("Empty input", "", 0);
    test("Single number", "1", 1);
    test("Two numbers", "1,2", 3);
    test("Multiple numbers", "1,2,3,4", 10);
    test("Newline as delimiter", "1\n2,3", 6);
    test("Custom delimiter ';'", "//;\n1;2", 3);
    test("Custom delimiter '***'", "//[***]\n1***2***3", 6);
    test("Multiple delimiters [*][%]", "//[*][%]\n1*2%3", 6);
    test("Multiple delimiters of varying length", "//[**][%%%]\n1**2%%%3", 6);
    test("Number > 1000 ignored", "2,1001", 2);

    try {
        StringCalculator calc;
        calc.add("1,-2,3,-4");
    } catch (const std::exception& e) {
        std::cout << "[PASS] Negative number throws: " << e.what() << "\n";
    }

    return 0;
}
