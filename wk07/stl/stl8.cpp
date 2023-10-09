#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;

bool isSmaller(int a, int limit) {
    return a < limit;
}

/**
 * @brief Remove from vector v all elements with value less than the limit
 * @param v a vector whose values are to be erased if less than limit
 * @param limit a threshold whose lower values are removed
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int removeLessThan(std::vector<int>& v, int limit)
{
    auto newEnd = std::remove_if(v.begin(), v.end(), [limit](int a) {
            return isSmaller(a, limit);
        });

        // Erase the elements that were moved to the end
        v.erase(newEnd, v.end());
    return EXIT_SUCCESS;
}

