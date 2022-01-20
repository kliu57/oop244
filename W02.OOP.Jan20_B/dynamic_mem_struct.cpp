 // Dynamic Memory Allocation
 // matrix: g++ -std=c++11 dynamic_mem2_s19.cpp
 // updated on 9/08/2020
 
 
 #define _CRT_SECURE_NO_WARNINGS
 #include <cstring>
 #include <iostream>
 #include <iomanip>
 using namespace std;

 // a struct type
 struct Student{
    int number;
    float marks[2];
 };

 void show (const Student&);  // an UNMODIFIABLE C++ reference parameter

 int main() {

     /* Part 1 - Allocate memory for ONE structure. */

     Student* studentPtr = nullptr;  // 1. Declare a pointer, INITIALIZED BY nullptr.

     studentPtr = new Student;       // 2. Allocate memory for ONE structure.

     (*studentPtr).number = 9999;
     studentPtr->marks[0] = 88.5;
     studentPtr->marks[1] = 44.7;

     // Display the values in the structure.
     cout << "studnet number: " << (*studentPtr).number << endl
	      << fixed << setprecision(2) 
	      << "marks #1: " << studentPtr->marks[0] << endl
	      << "marks #2: " << studentPtr->marks[1] << endl;

     //show( *studentPtr );  

     delete studentPtr;    // 3. Dealloacte the memory storage (to avoid memory leak)!!!
     studentPtr = nullptr;

     /* Part 2 - Allocate memory for an ARRAY of structures. */

     // 1. Declare a pointer.
     Student* students = nullptr; 

     int size;

     cout << ">Enter the number of students : ";
     cin >> size;

     // 2. Allocate an ARRAY of structures dynamically (i.e. at run time).
     students = new Student[size]; 

     // Store values in the array of structures.
     for (int i = 0; i < size; i++) {
	  cout << ">Student Number (integer): ";
	  cin  >> students[i].number;

	  cout << ">Student Marks 1: ";
	  cin  >> students[i].marks[0];

	  cout << ">Student Marks 2: ";
	  cin  >> students[i].marks[1];
     }

     cout << "...The array of structures has the following data:\n";

     for (int i = 0; i < size; i++) {

	  cout << students[i].number << ": " 
	       << fixed << setprecision(2) 
	       << students[i].marks[0] << ", " 
	       << students[i].marks[1]
	       << endl;
     }

     /* Part 3: C++ reference parameter */

     cout << "\nPart 3: Display the last student in the array." << endl;

     show( students[size-1] ); // the last student in the array

     // 3. Deallocate memory storage (to avoid memory leaks)!!!
     delete [] students;   // Be careful: []!
     students = nullptr;

     return 0;
 }

 // sref: a const C++ reference parameter
 void show(  const Student& sref ){  

      cout << "...Use an unmodifieable C++ reference parameter." << endl;
      cout << ".......student number: " << sref.number << endl;
      cout << fixed << setprecision(2);
      cout << ".......student marks #1: " << sref.marks[0] << endl;
      cout << ".......student marks #2: " << sref.marks[1] << endl;

      //sref.number = -1111;
      //sref.marks[0] = -99.55;
 }
				   
