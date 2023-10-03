/**
 * iteration2.cc
 *
 * Print every second item of a list starting from the first item
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration2.hh"
using namespace std;


void printEverySecond(const list<int>& lst)
{
    std::list<int>::const_iterator it = lst.begin();

    bool print = true; 

    while (it != lst.end()) {
        if (print) {
            std::cout << *it << " ";
        }

        ++it;
        print = !print; 
    }

    std::cout << std::endl;
}
