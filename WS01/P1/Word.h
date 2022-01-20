/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Thu Jan 20 2020

Workshop 1 part 1
Module: Word
Desc:   A module to hold the functions and constant values related to word statistics processing
Filename: Word.h
-----------------------------------------------------------*/

#ifndef SDDS_WORD_H
#define SDDS_WORD_H 

namespace sdds {

	const int MAX_WORD_LEN = 21;
	const int MAX_NO_OF_WORDS = 500;
	const int SORT_BY_OCCURANCE = 1;
	const int SORT_ALPHABETICALLY = 0;

	struct Word {
		char letters[MAX_WORD_LEN];
		int count;
	};

    int searchWords(const Word words[], int num, const char word[]);

    int readWord(char* word, FILE* fptr, int maxLen);

    void addWord(Word words[], int* index, const char newWord[]);

    void title(const char* value, int len);     // uses iomanip header file

    void endList();

    void totalWordsStat(int totNoWrds, int totalOverAll, int longestWord);

    void print(const Word* w, int gotoNextLine, int len);   // uses iomanip header file

    int findMaxLen(const Word words[], int noOfWords);

    void listWords(const Word words[], int noOfWords, const char* theTitle);

    void swap(Word* p1, Word* p2);

    void sort(Word words[], int cnt, int sortType);

    int totalCount(const Word* words, int num);

    void wordStats(const char* filename);

    void programTitle();
}

#endif // ! SDDS_WORD_H