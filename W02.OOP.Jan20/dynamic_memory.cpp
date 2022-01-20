 // Dynamic Memory Allocation in C++
 // - allocate an array of CHARACTERS dynamically (i.e. at run-time)
 // - 3 steps
 
 // matrix: g++ -std=c++11
 // updated on 9/08/2020
 
 #define _CRT_SECURE_NO_WARNINGS
 #include <cstring>
 #include <iostream>
 using namespace std;

 int main() {

     char waste[1000]; // a static array - size of array is fixed at compile time
                        // take up 10 000 bytes
                        // one byte per char
                        // when we store a short string we waste alot of memory

     /* Part 1 - static memory */

     cout << "Enter an English word (without any blank space): ";
     cin >> waste;
               

     int n = strlen(waste);

     cout << "The English word contains " << n << " characters."
	  << "\nHow much memory storage is wasted?" << endl;    

     /*Part 2 - Dynamic Memory Allocation */

     int m;
	
     cout << "\n>>> Please enter the number of characters in the English word: ";
     cin >> m;
                 // >> input operator - get user input, store in var m

     // STEP 1. Declare a pointer of a given data type.
     char* word = nullptr;        
            // we are storing characters, thus we use char*
            // if we are storing int, we use int* intPtr;
            // for DMA we always start with a pointer
            // always have to initialize (assign default value)
                    // if you do not valgrind will give you error msg and you cant submit
            // nullptr - null pointer
                // pointers need to be inititalized to nullptr
                
     // STEP 2. Allocate memory storage at run-time.
     word = new char [m+1];    // why m+1, not m?

            // if the user types 3 characters, m = 3
            // we allocate 4 characters
            // keyword new is called an operator
                // asks the runtime system for memory
                // c++ program will allocate memory at RUNTIME
            // word is a pointer
                // the value of a pointer can only be an addresss
            // we should draw a diagram when doing DMA

     // assumption: memory allocation is successful
     // store a string at the memory storage

	  cout << ">>> Please enter the English word: ";
	
	  cin >> word;  // What is "ice" store?

                // word is NOT an array
                // word is char pointer
                // word is address of first char
                // after I type ice, where is the string stored?
                        // a) at word FALSE
                        // b) at a block of mem storage pointed by word TRUE
                // an array of 4 characters that has been allocated dynamically
                // the pointer word allows us to access this block of memory
                // if we lose the beginning address this is called a memory leak
                    // if we overwrite the value of word - called a memory leak error
        
	  /* for (int k=0; k<strlen(word); k++)
		cout << word[k] << endl;
	   */        

	 cout << "### You have entered this English word: " << word
	      << "\n### It has " << strlen(word) << " characters." << endl;

     // STEP 3. Release the memory storage to avoid MEMORY LEAK!
     delete [] word;    // everytime you do DMA, you must do step 3
                        // must do it when you leave the scope of a fcn or the scope of a main program
                        // when we did word = new char [m+1];
                            // we requested memory from runtime system
                            // we need to return (release the memory storage) the memory to the runtime system
                        // if you don't use this, when we run valgrind it will give us error msg telling you your program has memory leaks

     word = nullptr;
     
     return 0;
 }
