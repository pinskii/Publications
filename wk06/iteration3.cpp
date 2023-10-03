/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;


void printHalf(const list<int>& lst)
{
    std::list<int>::const_iterator it = lst.begin();
    int half_size = lst.size() / 2;

    for (int i = 0; i < half_size; ++i) {
        std::cout << *it << " ";
        ++it;
    }

    std::cout << std::endl;
}
