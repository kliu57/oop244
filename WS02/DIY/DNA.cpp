/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Jan 30 2022

Workshop 2 part 2
Module: DNA
Desc:   Module for DNA object and functions
Filename: DNA.cpp
-----------------------------------------------------------*/

#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

#include "DNA.h"
#include "cStrTools.h"

namespace sdds {

	int numDNA;					// number of DNA currently in array of DNA objects
	int dnaArraySize;			// current size of array of DNA objects
	DNA* dnaArrayPtr = nullptr;	// pointer to array of DNA objects
	ifstream f;					// object that holds connection to data file

	bool validateStrand(const char *strand, int minLen) {

		bool validChar = true;
		int strandLen = strLen(strand);

		if (strandLen < minLen) {
			validChar = false;	// strand is immediately invalid if does not meet min length 
		}

		for (int i = 0; i < strandLen && validChar; i++) {	// go through every char in this string
			validChar = false;	// char must be validated by the end of this iteration

			for (int k = 0; k < STRAND_NUM_ALLOWED_CHARS; k++) {
				if (strand[i] == STRAND_ALLOWED_CHARS[k]) {	// check if character match an allowed character
					validChar = true;	// current character is found to be valid, moving on
					k = STRAND_NUM_ALLOWED_CHARS;
				}
			}
			// if current character is not validated at this point, the loop will end
		}

		// returns true if all the characters are validated, false if any are not
		return validChar;
	}

	bool beginSearch(const char *filename) {
		bool result = false;

		cout << "DNA search program" << endl;	// print opening message

		f.open(filename);		// connects input filename to ifstream object

		if (f.is_open()) {		// proceed if file opened successfully
			result = true;
			numDNA = 0;
		}

		return result;
	}

	void deallocate() {
		cout << "DEALLOCATE FUNC CALLED" << endl;

		for (int i = 0; i < numDNA; i++) {	
			delete [] dnaArrayPtr[i].strandPtr;			// deallocate dynamic memory for strand
			dnaArrayPtr[i].strandPtr = nullptr;
		}

		delete [] dnaArrayPtr;	// deallocate dynamic memory for array of dnas
		dnaArrayPtr = nullptr;

		numDNA = 0;			// set numDNA to 0 for next search
		dnaArraySize = 0;	// set array size counter to 0 for next search
	}

	bool read(const char* subDNA) {

		int matchFound = false;	// returned at the end of function
		bool abort = false;		// set this to true when we find an error and want to exit loop
		int idNum = -1;
		char delim = '\0';
		char strand[MAX_STRAND_LEN+1] = {0};
		int strandLen = 0;
		int newDnaArraySize = 0;		// for use when alloc more dynamic memory
		DNA* newDnaArrayPtr = nullptr;	// for use when alloc more dynamic memory

		if (f.is_open()) {
			while (f.good() && !abort) {

				idNum = readPositiveInt(&f, MIN_ID_SIZE, MAX_ID_SIZE);	// read id

				if (idNum != -1) {	// valid id was read

					if (f.good()) {	// EOF not reached after id so proceed

						f.get(delim);	// reads one character (delimiter)

						if (f.good() && delim == ',') {		// valid delimiter was read

							read(&f, strand, MAX_STRAND_LEN);	// read strand
							strandLen = strLen(strand);

							if (validateStrand(strand, MIN_STRAND_LEN)) {	// valid strand was read

								if (strStr(strand, subDNA) != nullptr) {	// check for DNA match

									if (numDNA == 0) {	// check if this is the first match found
										matchFound = true;
										dnaArrayPtr = new DNA[ALLOCATION_SIZE];		// allocate dynamic memory for array of DNA objects
										dnaArraySize = ALLOCATION_SIZE;
									}

									if (numDNA == dnaArraySize) {	// check if dynamic array is full

										newDnaArraySize = dnaArraySize + ALLOCATION_SIZE;	// increase array size

										newDnaArrayPtr = new DNA[newDnaArraySize];     // allocate dynamic memory to new larger array

										// copy all the DNA from old to new array
										for (int i = 0; i < dnaArraySize; i++) {
											newDnaArrayPtr[i] = dnaArrayPtr[i];
										}

										delete [] dnaArrayPtr;		// deallocate memory of old array
										dnaArrayPtr = newDnaArrayPtr;
										newDnaArrayPtr = nullptr;
										dnaArraySize = newDnaArraySize;
									}

									dnaArrayPtr[numDNA].id = idNum;							// store id in dynamic array

									dnaArrayPtr[numDNA].strandPtr = new char[strandLen+1];	// alloc dynamic memory for strand data
									strCpy(dnaArrayPtr[numDNA].strandPtr, strand);			// store strand in dynamic array

									numDNA++;	// increase counter of number of objects in dynamic array
								}
							} else {
								cout << "\n**Unexpected Error in runThru- Invalid strand read**\n";
								abort = true;
							}
						} else {
							cout << "\n**Unexpected Error in runThru- Invalid delimiter read**\n";
							abort = true;
						}
					} else {
						cout << "\n**Unexpected Error in runThru- EOF reached following id read**\n";
						abort = true;
					}
				} else if (idNum == -1 && !f.eof()) {
					cout << "\n**Unexpected Error in runThru- Invalid id read**\n";
					abort = true;
				} else {
					// read an invalid ID! but it is ok its EOF
				}
			} // end of while loop
		} else {
			cout << "\n**Unexpected Error in runThru- File is not open**\n";
		}

		f.clear();		// reset the file so this function can run again
		f.seekg(0);		// set the position of the character to be extracted from input stream back to starting point

		return matchFound;
	}

	void sort() {	// uses selection sort
		int i, j, m;
		DNA temp;

		for (i = 0; i < numDNA; i++) {
			m = i;
			for (j = i + 1; j < numDNA; j++)
				if (dnaArrayPtr[j].id < dnaArrayPtr[m].id) {
					m = j;
				}
			if (m != i) {
				temp = dnaArrayPtr[i];
				dnaArrayPtr[i] = dnaArrayPtr[m];
				dnaArrayPtr[m] = temp;
			}
		}
	}

	void displayMatches() {
		cout << numDNA << " matches found:" << endl;		// display num matches found
		for (int i = 0; i < numDNA; i++) {
			cout << (i+1) << ") ";							// display row number
			cout << dnaArrayPtr[i].id << ":" << endl;		// display id
			cout << dnaArrayPtr[i].strandPtr << endl;		// display DNA strand
			cout << "======================================================================" << endl;
		}
	}

	void endSearch() {
		f.close();                 // close source file
		cout << "DNA Search Program Closed." << endl;
	}
}