# Workshop #2: References, Dynamic Memory, Function Overloading
* Version 0.9

In this workshop, you will use File scope variables, Reuse your previously developed modules and overload functions, Dynamically allocate, reallocate (resize) and deallocate (free) memory.

## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- Overload functions.
- Dynamic Memory Allocation and Management
- Use References to pass back information through arguments of a function.
- Use default value for arguments of a function.

## Submission Policy

This workshop is divided into two coding parts and one non-coding part:

- Part 1: A step-by-step guided workshop, worth 50% of the workshop's total mark that is due on **Thursday at 23:59:59** of the week of your scheduled lab.
> Please note that the part 1 section is **not to be started in your first session of the week**. You should start it on your own before the day of your OOP244 class and join the first session of the week to ask for help and correct your mistakes (if there are any).
- Part 2 (**DIY**): A Do It Yourself type of workshop that is much more open-ended and is worth 50% of the workshop's total mark. This part is due on **Sunday at 23:59:59** of the week of your scheduled lab.  
- *reflection*: non-coding part, to be submitted together with *DIY* part. The reflection doesn't have marks associated with it but can incur a **penalty of max 40% of the whole workshop's mark** if your professor deems it insufficient (you make your marks from the code, but you can lose some on the reflection).
- Submissions of part 2 that do not contain the *reflection* (that is the **non-coding part**) are not considered valid submissions and are ignored.


If at the deadline the workshop is not complete, there is an extension of **one day** when you can submit the missing parts.  **The code parts that are submitted late receive 0%.**  After this extra day, the submission closes; if the workshop is incomplete when the submission closes (missing at least one of the coding or non-coding parts), **the mark for the entire workshop is 0%**.

Every file that you submit must contain (as a comment) at the top:<br />
**your name**, **your Seneca email**, **Seneca Student ID** and the **date** when you completed the work.

If the file contains only your work or work provided to you by your professor, add the following message as a comment at the top of the file:

> I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


If the file contains work that is not yours (you found it online or somebody provided it to you), **write exactly which part of the assignment is given to you as help, who gave it to you, or which source you received it from.**  By doing this you will only lose the mark for the parts you got help for, and the person helping you will be clear of any wrongdoing.

## Compiling and Testing Your Program

All your code should be compiled using this command on `matrix`:

```bash
g++ -Wall -std=c++11 -g -o ws file1.cpp file2.cpp ...
```

- `-Wall`: the compiler will report all warnings
- `-std=c++11`: the code will be compiled using the C++11 standard
- `-g`: the executable file will contain debugging symbols, allowing *valgrind* to create better reports
- `-o ws`: the compiled application will be named `ws`

After compiling and testing your code, run your program as following to check for possible memory leaks (assuming your executable name is `ws`):

```bash
valgrind -s --leak-check=full ws
```

To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use *diff* available on `matrix`.

> Note: All the code written in workshops and the project must be implemented in the **sdds** namespace.

# Part 1 - LAB (50%)

Land borders need to keep track of the Cars passing through when they come into the country. In this workshop we will use the concepts learnt this week to develop a small application that receives information about passing cars and keeps them in memory and then prints a report of their information at the end.

## Reusing code
Copy the cStrTools module from the previous lab and add it to this project.

### cString Data entry
In this lab, we need to receive cStrings from the console that contain spaces. To do so we need to know the features of the **cin** object which is not covered yet. Therefore the following function is provided to you to do what we need for now, until we learn how to work with the **cin** object. 

Add the following function to your cStrTools module (code in cpp file and prototype in the header file):

```C++
   // reads a cString upto maxSize characters or upto the delimiter character,
   // whichever comes first (skipping leading white space characters but accpting
   // spaces in the cString)
   void read(char* cString, unsigned int maxSize, char delimiter) {
      char ch=0;
      unsigned int i=0;
       // skipping leading white space chars
      do {   
         cin.get(ch); // reads one character from input
      } while (isSpace(ch));
      // read char by char util hitting delimiter or maxSize
      for (i = 0; i < maxSize && ch != delimiter;i++) {
         cString[i] = ch;
         // read the cString stopping at the size limit
         if (i < maxSize-1) cin.get(ch); 
      }       
      cString[i] = 0; // make sure the cString is null terminated
   }
```
In the prototype of the function provide a new line (```'\n'```) character as a default value for the third parameter (the delimiter). Therefore if the function is called with two parameters, the delimiter will be the new line character by default.

#### Usage example
```C++
   char name[51];
   cout << "Please enter your name: ";
   read(name, 50);
   cout << "Hello " << name <<"!" << endl;
```
Execution:  
```Text
Please entere your name: Fred Al Soley<ENTER>
Hello Fred Al Soley!
```
### Implementation

#### Car

Create a module called ```Car```.

In the module, create a structure called ```Car``` to hold the following information for a passing Car.

- License Plate of the Car; a Character cString capable of holding a maximum of 8 characters (8+1 for null byte)
- **Make and model** of the Car; a character pointer to hold the **make and model** of the car dynamically as a cString.<br /> 
    >Although a "make and model" of a Car is not typically more than 60 characters, to conserve memory, after reading the make and model in a local cString of 60 characters(function scope), we will store it in a dynamically allocated memory to the same size of the entry.
- Time; kept in an integer in military format (ie. **30** is 0:30 AM and **1325** is 1:25 PM)

Have this structure in ```Car.h```

#### Dynamic Array of Cars

In ```Car.cpp``` create a pointer to a Car structure. 

This pointer will hold a dynamic array of Car structures with an initial size (that we call **allocation size**). As cars pass the border the elements of the dynamic array will be set to the information of the car until the array is full. In this case, a new array of dynamic cars with more memory will be allocated (the old size + allocation size) to replace the old array.   

#### End of the day report
The execution of the programs starts at 0:01 in the morning and ends at midnight. 

When the program ends, a time-stamped report will be generated for all the cars that passed the border that day.
Before the program ends all the memory allocated during execution will be deallocated (deleted);

### Function implementation:
#### File scoped variables
Create the following four variables in ```Car.cpp``` to be used for memory management and tracking:
- **Car Pointer**; A Car pointer to hold the dynamic array of cars (We call this **"The Car Pointer"** in this text)
- **Allocation size**; an integer to hold the memory allocation and expansion size when needed
    >When testing you set this to be a small number (like 2) so you can easily test your memory resizing.
- Number of Cars; an integer to hold the number of cars currently in the dynamic array of cars pointed by ```The Car Pointer```
- **Car Array Size**; an integer to hold the current allocation size of the array. This value is the maximum size that the **Number Of Cars** can grow up to (before reallocation for expansion). 

#### ```void VBPLE_Title();```
Prints the following message:  
```Text
Vehicle Border Passing Log Entry
Enter the data in the following format:
Make and model,LicensePlate,MilitaryTime<ENTER>
Exit the program by entering the following:
X,<ENTER>
```
and goes to new line.

#### ```void initialize(int allocSize);```
Initializes [the four Car.cpp](#file-scoped-variables) variables as follows:
- sets the ```number of cars``` to zero
- sets the ```Car Array Size``` and the ```Allocation Size``` to the argument **allocSize**
- dynamically allocates an array of Cars to the size of ```Allocation Size``` and keeps the address in ```The Car Pointer```

####   ```void deallocate(Car& C);```
Deletes the allocated memory pointed by the ```make and model``` pointer in the ``Car`` structure, then set it to ```nullptr```.

#### ```bool read(Car& C);```
Overload the Read Function:<br />
Read the information of a car passing the border in a comma-separated format from the console and dynamically hold the **make an model** in the ```make and model``` pointer of the Car structure. Return true if a Car is read from the console or return false if "X," is entered instead.

No validation is done by this function on the data.

- create a boolean flag and set it to false
- create a local cString to hold 60 Characters to read the **make and model**
- call the cStrTools ```read``` function to read the make and model up to 60 characters or the comma character **(',')**;
- if the make and model is not equal to "X" then 
    - set the boolean flag to true
    - allocate a dynamic array of characters pointed by the ```make and model ``` of the Car structure to the size of the make and model red from the console (plus the null byte) and copy the make and model into it.
    - read the license plate up to 8 characters or up to the comma character **(',')**;
    - read the integer value and store it in the time variable of the Car structure.
- return the boolean flag.

#### ```void print(const Car& C);```
print the car in the following format:
```Time: Make and model, license plate<NEWLINE```

#### ```void record(const Car& C);```
Records the passage of a car by adding its information to the [Car Array](#file-scoped-variables) as follows:

- if the [number of cars](#file-scoped-variables) is equal to the size of the [Car Array](#file-scoped-variables) it means that the  [Car Array](#file-scoped-variables) is full, we have to enlarge it to make room for more entry
    - in a temporary local car pointer dynamically allocate an array of cars to the size of ```the car array + the allocation size```.
    - copy all the cars from the old array to the new array (but do not deallocate the individual old cars since their make and model in memory are now pointed by the cars in the new array)
    - delete the old car array by deleting ```The Car Pointer```
    - set ```The Car Pointer``` to the value of the temporary local car pointer
    - update the carr array size to the new size
- copy the ```car argument``` after the last occupied element of the car array pointed by ```The Car Pointer``` and add one to the ```number of cars```.

See the illustration bellow:   
- [HTML](lab/ResizingCarArray.md)
- [PDF](lab/ResizingCarArray.pdf) 
- [Power point](lab/ResizingCarArray.pptx)

#### ```void endOfDay()``` 
This function is called at the end of the program.

- The function will go through all the elements of the car array pointed by ```The Car Pointer``` and prints them using the print function and then deallocates the printed Car to make sure there is no memory leak. (using the deallocate function)
- then it will delete the car array pointed by ```The Car Pointer``` and sets it to ```nullptr```.


## Tester Program
```C++
/* ------------------------------------------------------
Workshop 2 part 1
Module: N/A
Filename: main.cpp
Version 1
Author	Fardad Soleimanloo
Revision History
-----------------------------------------------------------
Date       Reason
-----------------------------------------------------------*/
#include "Car.h"
using namespace sdds;

int main(){
   Car C;
   VBPLE_Title();
   // the value "2" is passed to make testing easier
   // in the tester program on submission it will be set to higher value
   initialize(2);
   while (read(C)) {
      record(C);
   }
   endOfDay();
}
```
## Execution Sample

```Text
Vehicle Border Passing Log Entry
Enter the data in the following format:
Make and model,LicensePlate,MilitaryTime<ENTER>
Exit the program by entering the following:
X,<ENTER>
Toyota C-HR,VYEEDG,0001
Alfa Romeo Giulia,OVQXIQ,0004
Buick Encore GX,ZIQSUF,0007
Jeep Gladiator,YFQOSQ,1010
Chevrolet Impala,MWPBNW,1013
Volkswagen Atlas Cross Sport,ESIJDW,1116
Toyota Prius Prime,AECYJV,1319
Lexus RZ,QONGCT,1622
Tesla Model S,MCGSVD,2225
X,
1: Toyota C-HR,VYEEDG
4: Alfa Romeo Giulia,OVQXIQ
7: Buick Encore GX,ZIQSUF
1010: Jeep Gladiator,YFQOSQ
1013: Chevrolet Impala,MWPBNW
1116: Volkswagen Atlas Cross Sport,ESIJDW
1319: Toyota Prius Prime,AECYJV
1622: Lexus RZ,QONGCT
2225: Tesla Model S,MCGSVD

```
### Data Entry

```Text
Copy and paste all the lines into the terminal instead of typing them.
Pasting in the terminal is usually done only by right clicking the mouse.

Toyota C-HR,VYEEDG,0001
Alfa Romeo Giulia,OVQXIQ,0004
Buick Encore GX,ZIQSUF,0007
Jeep Gladiator,YFQOSQ,1010
Chevrolet Impala,MWPBNW,1013
Volkswagen Atlas Cross Sport,ESIJDW,1116
Toyota Prius Prime,AECYJV,1319
Lexus RZ,QONGCT,1622
Tesla Model S,MCGSVD,2225
X,

```

## PART 1 Submission (lab)

When submitting your code, the main file ["main_prof.cpp"](lab/main_prof.cpp) will be used to test your program with a much larger [set of data](lab/car.csv). To make the data entry easier the data will be redirected to the workshop executable as ```ws < car.csv```.  By doing this the student does not need to enter the information manually.

Read the comments in ["main_prof.cpp"](lab/main_prof.cpp) to see the details.

### Files to submit:  

```Text
cStrTools.cpp
cStrTools.h
Car.cpp
Car.h
main.cpp
```

### Submission Process:


Upload your the files listed above to your `matrix` account. Compile and run your code using the `g++` compiler as shown in [Compiling and Testing Your Program](#compiling-and-testing-your-program) and make sure that everything works properly.

Then, run the following command from your account
- replace `profname.proflastname` with your professor’s Seneca userid
- replace **??** with your subject code (2**00** or 2**44**)
- replace **#** with the workshop number
- replace **X** with the workshop part number (**1** or **2**) 
```text
~profname.proflastname/submit 2??/w#/pX
```

and follow the instructions.

> **⚠️Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Re-submissions will attract a penalty.


# DIY (50%) 

A research lab requires an application to go through thousands of DNA samples and find all the matches to their sample. 

A DNA strand representation is done through combinations of the characters 'a', 'c', 'g' and 't' with no spaces in between. These combinations are kept as a cString of characters in a comma-separated file with a 6 digit integer id attached to each sample as follows:


```Text
243245,acccgttcgattcagtcgatcgatcgggatattgcaaa<NEWLINE>
```

Each DNA strand is between 100 to 1000 characters. 

The number of DNA strands in the data file could be millions. This amount is different in each data file.

Your responsibility is to write a library of functions in a module called "DNA" that can support the main program provided to have the following execution outcome:

The ids in the file are not sorted. Your search results must be sorted based on the Ids of the DNA strands in ascending order:


```Text
Enter DNA data file name: lowBaseDnaSmall.csv
DNA search program
Enter a DNA squence (max 100 chars)
> gtcc
4 matches found:
1) 444136:
atattttccactgaacggtccagatcgacgatcggggtgtaacagttcatctttggtataccctctccggcgttagatatggtcgaaacgggaacggctag
======================================================================
2) 448885:
ctgatgcagatggattgcgataacggagcgcaatgtgcaatacgggccttcgggaaacggctcgtccgtttcccgaacgcggaacgcaaagaacatgaca
======================================================================
3) 469926:
cggaccacggcccccgtcccccgcatgttcgacgagtggatagagttgagatccatccctttcctagcgtcattgttgcgatacgattgtagtgagcagct
======================================================================
4) 489349:
ccccttttaccaaatcgaagcttttgtgcgaatgtggtcttattgtacgtccgtctcacaggtgactcacactgtccgctctactgagaagcctcctatgc
======================================================================
Enter a DNA squence (max 100 chars)
> gtacct
No match found!
Enter a DNA squence (max 100 chars)
> !
DNA Search Program Closed.

```


## Tester Program
```C++
/* ------------------------------------------------------
Workshop 2 part 2
Module: N/A
Filename: main.cpp
Version 1
Author	Fardad Soleimanloo
Revision History
-----------------------------------------------------------
Date       Reason
-----------------------------------------------------------*/
#include <iostream>
#include "cStrTools.h"
#include "DNA.h"
using namespace std;
using namespace sdds;
int main() {
   bool done = false;
   char dna[101];
   char filename[256];
   cout << "Enter DNA data file name: ";
   cin >> filename;
   if (beginSearch(filename)) {
      while (!done) {
         cout << "Enter a DNA squence (max 100 chars)" << endl << "> ";
         read(dna, 100);
         if (strCmp(dna, "!") == 0) {
            done = true;
         }
         else {
            if (read(dna)) {
               sort();
               displayMatches();
               deallocate();
            }
            else {
               cout << "No match found!" << endl;
            }
         }
      }
      endSearch();
   }
   return 0;
}
```

## Mandatory Functions

### ```bool beginSearch(const char *filename);```
It will try to open the file and initialize any requirements needed for the application. Returns true if the file is opened successfully and returns false it fails to open the file.

### ```bool read(const char* subDNA);```
Dynamically creates an array of DNA records to the number of matches found in the file and stores the matches in them. Returns true if at least one match is found and false if no match is found in the records.

### ```void sort()```
Sorts the dynamic array of DNA matches found in the file based on the ids in ascending order.

### ```void displayMatches()```
Displays the dynamic DNA records in the following format.

```Text
row) ID:
DNA strand
======================================================================
```

### ```void deallocate()```
Deallocates all the dynamic memory within the DNA array elements and the DNA array itself.

### ```void endSearch()```
Finalizes the program by releasing the resources allocated by the program (like closing the data file and etc...). 

And then Prints:  
```Text
DNA Search Program Closed.
```

## Execution Sample
[Sample execution on `dna.csv` file](DIY/ExecutionSample.md)

## Reflection

Study your final solutions for each deliverable of the workshop, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop.  **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this workshop and mention any issues that caused you difficulty.

You may be asked to talk about your reflection (as a presentation) in class.

## Part 2 Submission (DIY)

### Files to submit:  

```reflect.txt``` and:
```Text
cStrTools.cpp
cStrTooos.h
DNA.cpp
DNA.h
main.cpp
```

### Data Entry

To Be Announced Shortly

## Submission Process:

Upload your the files listed above to your `matrix` account. Compile and run your code using the `g++` compiler as shown in [Compiling and Testing Your Program](#compiling-and-testing-your-program) and make sure that everything works properly.

Then, run the following command from your account
- replace `profname.proflastname` with your professor’s Seneca userid
- replace **??** with your subject code (2**00** or 2**44**)
- replace **#** with the workshop number
- replace **X** with the workshop part number (**1** or **2**) 
```text
~profname.proflastname/submit 2??/w#/pX
```

and follow the instructions.

> **⚠️Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Re-submissions will attract a penalty.
