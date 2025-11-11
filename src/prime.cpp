#include "prime.h"

#include <cmath>

int Prime(int number) {
    if (number <= 1) {
        return 0;
    }
    int iter = std::sqrt(number);
    for (int k = 2; k <= iter; ++k) {
        if (number % k == 0) {
            return 0;
        }
    }
    return 1;
}