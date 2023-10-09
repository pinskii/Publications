#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;

bool parillinen(int a) {
    if ( a % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Return an iterator which points to the last even integer of the vector
 *        If the value is not found, return v.rend()
 *
 * @param v the vector to be scanned through
 * @return std::vector<int>::reverse_iterator
 */
std::vector<int>::reverse_iterator findLastEven(std::vector<int>& v)
{
    std::vector<int>::reverse_iterator p;
    p = std::find_if(v.rbegin(), v.rend(), parillinen);
    if (p != v.rend()) {
        return p;
    }
    else {
        return v.rend();
    }
}

