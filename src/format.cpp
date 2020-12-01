#include <string>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long InputSec) {
    long minutes = InputSec / 60;
    long hours = minutes / 60;
    long seconds = int(InputSec % 60);
    minutes = int(minutes % 60);
    std::string result = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);

    return result;
}