/**
 * iteration4.cc
 *
 * Print all items of a list in a reverse order
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration4.hh"
using namespace std;


void printReverse(const list<int>& lst)
{
    std::list<int>::const_reverse_iterator it = lst.rbegin();
    
    while (it != lst.rend()) {
        std::cout << *it << " ";
        ++it;
    }

    std::cout << std::endl;
}
