/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Thu Jan 20 2020

Workshop 1 part 1
Module: WordStat
Desc:   main module that is caller of the initial functions of the WordStat program
Filename: WordStat.cpp
-----------------------------------------------------------*/

#include <iostream>
#include "Word.h"
using namespace sdds;
using namespace std;
int main() {
	char filename[256];
	programTitle();
	cout << "Enter filename: ";
	cin >> filename;
	wordStats(filename);
	return 0;
}