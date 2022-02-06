/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Feb 6 2020

Module: BitStuffing
Desc:   program which duplicates the work of the data link layer
Filename: bitstuffing.cpp
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int main() {
	int dataSize = 15;				// size of the initial data
	char* data = nullptr;
	int numConsecutiveOnes = 0;		// counter for number of ones
	char* newData = nullptr;		// will be used when we need to change the data
	int k = 0;
	int m = 0;

	data = new char[dataSize+1];		// allocate dynamic memory
	strcpy(data, "011111101111110");	// Assume this is the data sent to the data link layer from the network layer

	char flag[9] = "01111110";		// flag delimiter
	int flagSize = 8;

	// Show the data stream before stuffing with the number of characters in the array
	cout << "Before Stuffing: " << data << " -- " << dataSize << " characters" << endl;

	// count the number of 1s and if there are 5 1s in sequence, insert a 0 into the data stream

	for (int i = 0; i < dataSize; i++) {	// go through each character in array

		if (data[i] == '1') {		// check if character is a one
			
			if (numConsecutiveOnes == 5) {	// if counter has reached 5 meaning this is the sixth one
				
				newData = new char[dataSize+2];	// allocate dynamic memory for new array
	
				// copy everything before the sixth one to the new array
				for (k = 0; k < i; k++) {
					newData[k] = data[k];
				}

				// append a zero
				newData[k] = '0';

				// copy the rest to the new array
				for (k; k < dataSize; k++) {
					newData[k+1] = data[k];
				}

				// append null byte to the end
				newData[++k] = '\0';

				dataSize++;		// update data size tracking

				delete [] data;	// deallocate memory of old array
				data = newData;	// set pointer to point to new array
				newData = nullptr;

				numConsecutiveOnes = 1;	// update counter
				i++;	// this is increased to skip over the 0 we just added
			}
			else {
				numConsecutiveOnes++;	// increase counter
			}
		} else {
			numConsecutiveOnes = 0;	// character is not a one so reset the one counter
		}
	}

	// Show the data stream after stuffing with the number of characters in the array
	cout << "After Stuffing:  " << data << " -- " << dataSize << " characters" << endl;

	// bit stuffing complete, now attach flags to front and end
	
	newData = new char[dataSize+flagSize*2+1];	// allocate dynamic memory for new array

	// append flag to start
	k = 0;
	for (m = 0; m < flagSize; m++) {
		newData[k++] = flag[m];
	}

	// append data after flag
	for (m = 0; m < dataSize; m++) {
		newData[k++] = data[m];
	}

	// append flag to end
	for (m = 0; m < flagSize; m++) {
		newData[k++] = flag[m];
	}

	// append null byte to the end
	newData[k] = '\0';

	delete [] data;	// deallocate memory of old array
	data = newData;	// set pointer to point to new array
	newData = nullptr;
	dataSize += flagSize*2;	// update size tracking

	cout << "After framing: " << data << endl;	// Show the synchronous frame with the flag delimiters appended

	delete [] data;		// free memory at the end of program
	data = nullptr;

	return 0;
}