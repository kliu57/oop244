#ifndef SDDS_TEMPS_H_
#define SDDS_TEMPS_H_
#include <iostream>

#include "Collection.h"
#include "Displayable.h"

namespace sdds {

    // select function template
    // loop through array of objects and compare each element with an object of the same type
    // if the two match, the element will be added to a Collection object returned at end
    template <typename type>
    Collection<type> select(type objArray[], int size, type obj) {
        int numMatches = 0;
        int coll_index = 0;

        // loop through array once to check how many matches
        for (int i = 0; i < size; i++) {
            if (objArray[i] == obj) {
                numMatches++;
            }
        }

        // create Collection object of same size as number of matches
        Collection<type> coll(numMatches);

        // loop through array again and set the Collection elements to the matches found
        for (int i = 0; i < size; i++) {
            if (objArray[i] == obj) {
                coll[coll_index++] = objArray[i];
            }
        }

        // return the Collection
        return coll;
    }

    // prints the elements of a Collection object after printing a title in separate lines
    template <typename type>
    void printCollection(const Collection<type>& coll, const char title[]) {
        int size = coll.size();
        
        

        // first print the title
        cout << title << endl;

        if (size) {
            // loop through the elements of the Collection and print each element in a new line
            for (int i = 0; i < size; i++) {
                
                cout << coll[i] << endl;            // print one element plus newline
                //coll[i].display(cout);   // why doesnt this work?
            }
        }


    }

}

#endif // ! SDDS_TEMPS_H_