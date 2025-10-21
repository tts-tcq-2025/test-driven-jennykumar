#include "NegativeError.h"
#include <vector>
#include <string>
#include <sstream>

std::string formatNegativeError(const std::vector<int>& negatives) {
    std::ostringstream err;
    err << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        err << negatives[i];
        if (i < negatives.size() - 1) err << ", ";
    }
    return err.str();
}
