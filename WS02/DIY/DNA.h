/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Jan 30 2020

Workshop 2 part 2
Module: DNA
Desc:   Module for DNA object and functions
Filename: DNA.h
-----------------------------------------------------------*/

#ifndef SDDS_DNA_H
#define SDDS_DNA_H 

namespace sdds {

    const int MIN_STRAND_LEN = 100;
    const int MAX_STRAND_LEN = 1000;
    const int MIN_ID_SIZE = 100000;
    const int MAX_ID_SIZE = 999999;
    const int ALLOCATION_SIZE = 12;
    const char STRAND_NUM_ALLOWED_CHARS = 4;
    const char STRAND_ALLOWED_CHARS[STRAND_NUM_ALLOWED_CHARS+1] = "acgt";

    struct DNA {
        int id;
        char* strandPtr;   // stores pointer to dna strand char array 
    };

    // check if the strand is valid
    // strand must have a min length and only contain allowed chars
    bool validateStrand(const char *strand, int strandLen);

    // try to open the file and initialize any requirements needed for the application
    // Returns true if the file is opened successfully and returns false it fails to open the file
    bool beginSearch(const char *filename);

    // deletes allocated memory pointed by the make and model pointer in the Car structure, then set it to nullptr
    void deallocate();

    // Dynamically creates an array of DNA records to the number of matches found in the file and stores the matches in them
    // Returns true if at least one match is found and false if no match is found in the records
    bool read(const char* subDNA);

    // Sorts the dynamic array of DNA matches found in the file based on the ids in ascending order
    void sort();

    // formats and prints car object
    void displayMatches();

    // function called at the end of the program
    // closes file, deallocates memory and prints closing message
    void endSearch();
}

#endif // ! SDDS_DNA_H