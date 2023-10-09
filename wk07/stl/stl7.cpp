#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    int i;
    int j;
    int median;
    int center;
    if (v.size() == 0) {
        return NOT_FOUND;
    }
    std::sort(v.begin(), v.end());
    if (v.size() % 2 == 0) {
        i = v.size() / 2;
        j = i - 1;
        median = (v[i] + v[j]) / 2;

        return median;
    }

    else {
        i = v.size() / 2;
        median = v[i];
        return median;
    }

}

