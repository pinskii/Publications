/**
 * iteration1.cc
 *
 * Print all items of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration1.hh"
using namespace std;


void printAllItems(const list<int>& lst)
{
    std::list<int>::const_iterator it = lst.begin();

    while (it != lst.end()) {
        std::cout << *it << " ";
        ++it;
    }

    std::cout << std::endl;
}
