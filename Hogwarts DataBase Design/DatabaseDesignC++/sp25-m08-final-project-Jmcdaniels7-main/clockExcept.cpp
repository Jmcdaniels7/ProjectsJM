#include "clockExcept.h"

invalid_AmPmType::invalid_AmPmType(std::string tod) : invalid_argument(tod + " is not a valid time of day.") {}

invalid_Hour::invalid_Hour(std::string errMsg) : invalid_argument(errMsg) {}