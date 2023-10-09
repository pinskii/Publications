#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


bool isDivisibleByThree(int num) {
    return num % 3 == 0;
}

bool hasRemainderOne(int num) {
    return num % 3 == 1;
}

bool hasRemainderTwo(int num) {
    return num % 3 == 2;
}

/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v) {
    // Partition the vector into three sections
    auto first_divisible = std::partition(v.begin(), v.end(), isDivisibleByThree);
    auto first_remainder_one = std::partition(first_divisible, v.end(), hasRemainderOne);
    auto first_remainder_two = std::partition(first_remainder_one, v.end(), hasRemainderTwo);

    // Sort each section in ascending order
    std::sort(v.begin(), first_divisible);
    std::sort(first_divisible, first_remainder_one);
    std::sort(first_remainder_one, first_remainder_two);
    std::sort(first_remainder_two, v.end());

    return EXIT_SUCCESS;
}




