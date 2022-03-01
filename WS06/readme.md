# Workshop #6: Classes and resources, IO operators
# version 1.0 

In this workshop, you will implement a class with overloaded constructors. Then you will overload IO operators that will be used to read and write on the screen and files.

## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- define and implement multiple constructors
- define and implement the rule of three
- Read formatted data using `istream`
- Write formatted data using `ostream`
- Overload the extraction and insertion operators for I/O, using iostream 

## Submission Policy

This workshop is divided into two coding parts and one non-coding part:

- Part 1: A step-by-step guided workshop, worth 50% of the workshop's total mark that is due on **Thursday at 23:59:59** of the week of your scheduled lab.
> Please note that the part 1 section is **not to be started in your first session of the week**. You should start it on your own before the day of your OOP244 class and join the first session of the week to ask for help and correct your mistakes (if there are any).
- Part 2 (**DIY**): A Do It Yourself type of workshop that is much more open-ended and is worth 50% of the workshop's total mark. This part is due on **Sunday at 23:59:59** of the week of your scheduled lab.  
- *reflection*: non-coding part, to be submitted together with *DIY* part. The reflection doesn't have marks associated with it but can incur a **penalty of max 40% of the whole workshop's mark** if your professor deems it insufficient (you make your marks from the code, but you can lose some on the reflection).
- Submissions of part 2 that do not contain the *reflection* (that is the **non-coding part**) are not considered valid submissions and are ignored.


If at the deadline the workshop is not complete, there is an extension of **one day** when you can submit the missing parts.  **The code parts that are submitted late receive 0%.**  After this extra day, the submission closes; if the workshop is incomplete when the submission closes (missing at least one of the coding or non-coding parts), **the mark for the entire workshop is 0%**.

## Citation

Every file that you submit must contain (as a comment) at the top:<br />
**your name**, **your Seneca email**, **Seneca Student ID** and the **date** when you completed the work.

### For work that is done entirely by you (ONLY YOU)

If the file contains only your work or the work provided to you by your professor, add the following message as a comment at the top of the file:

> I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

### For work that is done partially by you.

If the file contains work that is not yours (you found it online or somebody provided it to you), **write exactly which part of the assignment is given to you as help, who gave it to you, or which source you received it from.**  By doing this you will only lose the mark for the parts you got help for, and the person helping you will be clear of any wrongdoing.

> - Add the citation to the file in which you have the borrowed code
> - In the 'reflect.txt` submission of part 2 (DIY), add exactly what is added to which file and from where (or whom).

> :warning: This [Submission Policy](#submission-policy) only applies to the workshops. All other assessments in this subject have their own submission policies.

### If you have helped someone with your code

If you have helped someone with your code. Let them know of these regulations and in your 'reflect.txt' of part 2 (DIY), write exactly which part of your code was copied and who was the recipient of this code.<br />By doing this you will be clear of any wrongdoing if the recipient of the code does not honour these regulations.

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

## Before starting with part 1, we will introduce two functions 

These two member functions are available in istream:

```C++
setstate(); 
peek();
```

- **setstate()** manually sets the status of the istream object to the desired state. In our case we will be calling `setstate` as follows to manually set any object of istream (like cin) to a **fail** state:

```C++
// Examples:
// assuming there is a funciton called readData as follows
istream& readData(istream& istr){
    type variable{};
    istr >> variable;
    if(/*logic for variable being invalid*/){
        istr.setstate(ios::failbit); // this manually sets istr to failure
                                     // if the variable is readable but not acceptable
    }
    return istr;
}
// Or:

int getAge(){
    int age{};
    cin >> age;
    if(age < 19){
        cin.setstate(ios::failbit); // this sets cin to fail if the age is bellow 19
    }
    return age;
}

void someLogic(){
    cout << "Enter your name: ";
    int age = getAge();
    if(cin.fail()){
       cout << "You are not old enough to consume alcoholic drinks in Ontario!" <<endl; 
       cin.clear();
    }
}

```

- **peek()** it peeks and checks the next character without extracting it from the keyboard. With this function, you can check and see what is the next character before reading it. 
setting m_name to nullptr before constructor invocation 

```C++
// Example
char next;
int value;

cout <<"Enter a number: ";
next = cin.peek();
if(next < '0' || next >'9'){ // checking if the next character in keyboard is not a digit
    cout << "You did not enter a number!";
}
else{
    cin >> value;
}
cin.ignore(1000, '\n'); // flush the invalid value or everything after the number.
```

## Part 1 - lab (50%), The HealthCard class

Your task for this part of your workshop is to complete the implementation of a class called HeathCard. This class encapsulates some basic health-card information of a person in Ontario using the following attributes:

```C++
 class HealthCard {
      char* m_name{}; 
      long long m_number;
      char m_vCode[3];
      char m_sNumber[10];
    public:
      ...
   };
```

- **m_name** to hold the full name of a person which is Dynamically allocated
- **m_number** to hold the main health card number 
- **m_vCode** Version code of the card
- **m_sNumber** Stock Control Number


### Validation
These values are validated (considered **valid**) as follows:
   - Full name is a Cstring that is not null and not empty.
   - The main health number consists of 10 digits (>999999999 and <9999999999)
   - The version number consists of two characters
   - The Stock control number consists of nine characters
   
The HeathCard class is to validate and store the above information via initialization and data entry from istream.

Also, the HeathCard class must comply with the rule of three. (i.e. the implementation of copy constructor, copy assignment and destructor)

Although the name of the HealthCard is dynamically held, we can assume that the maximum length for a name is 55 characters. This value should be kept in a constant global variable so it can be changed at compile-time if needed.

```C+
   const int MaxNameLength = 55;
```

Finally, A HeathCard object should reveal its status (of being valid or invalid) via a Boolean type conversion overload (a true outcome means the object is valid and a false outcome means it is invalid).

To accomplish the above and have an organized and modular code, implement these private methods to help you with the implementation of the whole logic: (you can add more if you like to)

### Private Methods

#### bool validID(const char* name, long long number, const char vCode[] , const char sNumber[]) const; 
Returns true is the four parts of the ID card are valid. (see [Validation](#validation))

#### void setEmpty();
Sets the HeathCard object to a recognizable empty (invalid) state by setting **m_name** to nullptr;

#### void allocateAndCopy(const char* name);
- Free the memory pointed by **m_name** 
- Allocate enough memory to store **name** Cstring
- Copy the Cstring pointed by **name** into the newly allocated memory pointed by **m_name**

#### void HealthCard::extractChar(istream& istr, char ch) const;
"peek()" and see if the next character in the keyboard buffer is the same as the **ch** argument 
  - If it is the same, Remove it from the keyboard and throw it away! (i.e. istr.ignore())
  - If not:
    - Ignore all the remaining characters (up to 1000 characters) or the value of ch (use istr.ignore(int n,char c))
    - Set the istream into a fail state (use istr.setstate(iso::failbit))
#### ostream& printIDInfo(ostream& ostr)const;
Inserts the three parts related to the main card number, version code and stock number of the health card information into the **istr** object in the following format:

`1234567890-AB, XY7652341`

and then returns the **istr** object reference


#### void set(const char* name, long long number, const char vCode[], const char sNumber[]);
Validates the arguments,  reallocates memory for the name and sets the object attributes to their corresponding values.
- If the name and the three parts are valid (see [Validation](#validation)) `call the private function to validate`
    - Calls the **reallocateAndCopy** function to set the name
    - Sets the three parts to their values (m_number, m_vCode, m_sNumber)
- If not, it deletes the memory pointed by **m_name** and sets the object to a safe empty state (**setEmpty()**)

#### Constructors
The HeathCard can either get created with no values (default constructor) into a safe empty state or use all four values. 

> Instead of overloading the constructor you can use one constructor with the default values for the four parameters, (i.e nullptr, 0, {}, {} ) and remember to reuse the **set** function for the latter case. 

> Note that since the **m_name** attribute is initialized in the class definition to be **nullptr**, there is no need to worry about setting it to **nullptr** before calling the set function.

### Rule of three
#### Copy Constructor
`HeathCard(const HeathCard& hc);`
- if the **hc** object is valid it will set the values of the current object to those of the incoming argument (**hc** using assignment to *this).

#### Copy Assignment operator overload
`HeathCard& operator=(const HeathCard& hc);`
- First, it will make sure that this is not a "self-copy" by comparing the address of the current object and the address of the incoming argument.
  - If it is not a self copy this function works exactly like the copy constructor
- If it is a self copy don't perform any action 
At the end return the reference of the current object.

#### Destructor
deletes the memory pointed by **m_name**.

### Boolean type conversion operator
Returns true if **m_name** is not nullptr, else it will return false

### ostream& print(ostream& ostr, bool toFile = true) const;
If the current object is in a valid state it inserts the values of the card information in two different formats based on the value of the **toFile** argument:
- if **toFile** is true, prints the data in a comma-separated format:
    - prints the name
    - print comma
    - print the health card ID information using the private function printIDInfo
- if **toFile** is false prints the data in the following format:
    - In 50 characters, left-justified and padded with dots ('.'): prints the name
    - print the health card ID information using the private function printIDInfo
- At the end, it returns the **ostr** reference

### istream& read(istream& istr);
Reads the Contact information in following format:
- name
- comma
- main health number
- dash
- version number characters
- comma
- stock control number


Example: `Luke Skywalker,1231231234-XL,AF1234567`

#### implementation

- define local variables for the four parts.
- using istream::get() read the name up to **MaxNameLength** or a comma (do not extract comma)
- extract a comma using **extractChar** private function
- extract the main health number into a local variable (istr >> m_number;)
- extract a dash **'-'** using **extractChar** private function
- extract the version number code into a vCode local variable using get for 3 char or up to ',' whichever comes first
- extract a comma **','** using **extractChar** private function
- extract the stock control number to the local variable (using get to read 10 char or up to '\n' whichever comes first)
- extract a new line character **'\n'** (using **extractChar** private function)
- if **istr** is not in a failure state
    - all data were read successfully, use the **set** private function to set values of the object to read value
- before returning, clear the state using istr.clear() and ignore the remaining of the line until '\n'
- at the end return the **istr** reference

### insertion operator overload
`ostream& operator<<(ostream& ostr, const Contact& hc);`

if **hc** is valid it will print it using the **print** function on the screen and not on File, (i.e. onFile is false). Otherwise, it will print `"Invalid Card Number"`.

In the end, it will return the **ostr** reference.

### extraction operator overload
`istream& operator>>(istream& istr, Contact& hc)`

returns the **read** method of the **hc** argument.

## The tester program
```C++
// Workshop #6:
// Version: 1.0
// File name: main.cpp
// Date: 2021/12/02
// Author: Wail Mardini
// Description:
// This file tests the lab section of your workshop
///////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include "HealthCard.h"
using namespace std;
using namespace sdds;

int noOfRecs(const char* filename);
void showFile(const char* filename);
HealthCard ReadCardFromFile(istream& istr);
void dataEntryTest();
void validationTest();


int main() {
   int i;
   int recs = noOfRecs("HealthCardInfo.csv");
   HealthCard C{ "Gandalf The Grey",111,"XL","123234LA"};
   ifstream CardFile("HealthCardInfo.csv");
   ofstream goodCardFile("goodInfo.csv");
   validationTest();
   dataEntryTest();
   for (i = 0; i < recs; i++) {
      C = ReadCardFromFile(CardFile);
      cout << C << endl;
      if (CardFile) 
          C.print(goodCardFile, true);
   }
   if (i == recs)
      cout << "\nAll records were read successfully!" << endl;
   else {
      cout << "Read " << i - 1 << " out of " << recs << " Records successfully" << endl;
      cout << "Record number " << i << " is invalid!" << endl;
   }
   showFile("goodInfo.csv");
   return 0;
}

void validationTest() {
   int i;
   HealthCard C[]{
      {"Fred Soley", 1234567890,"AB","WQ1234567"},
      {nullptr, 1234567890,"AB","WQ1234567" },
      {"Fred Soley", 123456789,"B","WQ1234567" },
      {"Fred Soley", 1234567890,"AB","WQ123456" },
      {"Fred Soley", 1234567890,"AB","WQ1234567" },
      {"Fred Soley", 234567890,"AB","Q1234567" },
      {"Fred Soley", 234567890,"B","WQ1234567" },
      {"Fred Soley", 1234567890,"B","Q1234567" },
   };
   cout << "Validation Test" << endl;
   for (i = 0; i < 8; cout << C[i++] << endl);
}

int noOfRecs(const char* filename) {
   int num = 0;
   ifstream file(filename);
   while (file) num += (file.get() == '\n');
   return num;
}

void showFile(const char* filename) {
   ifstream file(filename);
   char ch;
   cout << "Contents of " << filename << endl << "----------------------------------------------------------------" << endl;
   while (file.get(ch)) {
      cout << ch;
   }
}

void dataEntryTest() {
    HealthCard C{ "Fred Soley", 1234567890,"AB","WQ123456" };
   cout << endl << "Data entry test." << endl;
   cout << "Enter the test data using copy and paste to save time:" << endl << endl;
   
   cout << "Enter the following:" << endl
      << ">Person Name,1231231234-XL,AF1234567" << endl << ">";
   cin >> C;

   cout << "HealthCard Content:" << endl << C << endl;

   cout << "Enter the following:" << endl
       << ">Person Name,1231231234-XL,AF123456" << endl << ">";
   cin >> C;
   cout << "HealthCard Content:" << endl << C << endl;

   cout << "Enter the following:" << endl
       << ">Person Name,1231231234-L,AF1234567" << endl << ">";
   cin >> C;
   cout << "HealthCard Content:" << endl << C << endl;

   cout << "Enter the following:" << endl
       << ">Person Name,1231231234-,AF1234567" << endl << ">";
   cin >> C;
   cout << "HealthCard Content:" << endl << C << endl;

   cout << "Enter the following:" << endl
       << ">Person Name,131231234-XL,AF1234567" << endl << ">";
   cin >> C;
   cout << "HealthCard Content:" << endl << C << endl;
   
   cout << "Enter the following:" << endl
       << ">Person Name 1231231234-XL,AF1234567" << endl << ">";
   cin >> C;
   cout << "HealthCard Content:" << endl << C << endl;
}


HealthCard ReadCardFromFile(istream& istr) {
   HealthCard C;
   istr >> C;
   return C;
}
```
## Tester output
```text
Validation Test
Fred Soley........................................1234567890-AB, WQ1234567
Invalid Health Card Record
Invalid Health Card Record
Invalid Health Card Record
Fred Soley........................................1234567890-AB, WQ1234567
Invalid Health Card Record
Invalid Health Card Record
Invalid Health Card Record

Data entry test.
Enter the test data using copy and paste to save time:

Enter the following:
>Person Name,1231231234-XL,AF1234567
>Person Name,1231231234-XL,AF1234567
HealthCard Content:
Person Name.......................................1231231234-XL, AF1234567
Enter the following:
>Person Name,1231231234-XL,AF123456
>Person Name,1231231234-XL,AF123456
HealthCard Content:
Invalid Health Card Record
Enter the following:
>Person Name,1231231234-L,AF1234567
>Person Name,1231231234-L,AF1234567
HealthCard Content:
Invalid Health Card Record
Enter the following:
>Person Name,1231231234-,AF1234567
>Person Name,1231231234-,AF1234567
HealthCard Content:
Invalid Health Card Record
Enter the following:
>Person Name,131231234-XL,AF1234567
>Person Name,131231234-XL,AF1234567
HealthCard Content:
Invalid Health Card Record
Enter the following:
>Person Name 1231231234-XL,AF1234567
>Person Name 1231231234-XL,AF1234567
HealthCard Content:
Invalid Health Card Record
Invalid Health Card Record
2Person Name2.....................................1231231234-XL, AF1234567
Invalid Health Card Record
4Person Name3.....................................1231231234-XL, AF1234567
Invalid Health Card Record
Invalid Health Card Record
Invalid Health Card Record
8Person Name7.....................................1231231234-XL, AF1234567
Invalid Health Card Record
Invalid Health Card Record
11Person Name10...................................1231231234-XL, AF1234567
12Person Name11...................................1231231234-XL, AF1234567
13Person Name12...................................1231231234-XL, AF1234567
14Person Name13...................................1231231234-XL, AF1234567
15Person Name.....................................1231231234-XL, AF1234567
Invalid Health Card Record
17Person Name.....................................1231231234-XL, AF1234567
18Person Name.....................................1231231234-XL, AF1234567
Invalid Health Card Record
20P...............................................1231231234-XL, AF1234567
21Person Name.....................................1231231234-XL, AF1234567
22Person Name.....................................1231231234-XL, AF1234567
Invalid Health Card Record
24Person Name.....................................1231231234-XL, AF1234567
25Person Name.....................................1231231234-XL, AF1234567

All records were read successfully!
Contents of goodInfo.csv
----------------------------------------------------------------
2Person Name2,1231231234-XL, AF1234567
4Person Name3,1231231234-XL, AF1234567
8Person Name7,1231231234-XL, AF1234567
11Person Name10,1231231234-XL, AF1234567
12Person Name11,1231231234-XL, AF1234567
13Person Name12,1231231234-XL, AF1234567
14Person Name13,1231231234-XL, AF1234567
15Person Name,1231231234-XL, AF1234567
17Person Name,1231231234-XL, AF1234567
18Person Name,1231231234-XL, AF1234567
20P,1231231234-XL, AF1234567
21Person Name,1231231234-XL, AF1234567
22Person Name,1231231234-XL, AF1234567
24Person Name,1231231234-XL, AF1234567
25Person Name,1231231234-XL, AF1234567
```

### Files to Submit
```Text
HealthCard.h
HealthCard.cpp
w6p1_tester.cpp
HealthCardInfo.csv
```

#### Custom code submission

If you have any additional custom code, (i.e. functions, classes etc) that you want to reuse in this workshop save them under a module called Utils (`Utils.cpp and Utils.h`) and submit them with your workshop using the instructions in the "[Submitting Utils Module](#submitting-utils-module)" section.

### Data Entry

??? explain what data  will be used for submission and testing

### Submission Process:

Upload the files listed above to your `matrix` account. Compile and run your code using the `g++` compiler as shown in [Compiling and Testing Your Program](#compiling-and-testing-your-program) and make sure that everything works properly.

Then, run the following command from your account
- replace `profname.proflastname` with your professor’s Seneca userid
- replace **??** with your subject code (2**00** or 2**44**)
- replace **#** with the workshop number
- replace **X** with the workshop part number (**1** or **2**) 
```text
~profname.proflastname/submit 2??/w#/pX
```
and follow the instructions.

#### Submitting Utils Module
To have your Utils module compiled with your workshop and submitted, add a **u** to the part number of your workshop (i.e **u**p1 for part one and **u**p2 for part two) and issue the following submission command instead of the above:
```text
~profname.proflastname/submit 2??/w#/upX
```
See [Custom Code Submission](#custom-code-submission) section for more detail

> **⚠️Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Re-submissions will attract a penalty.



# Part 2 - DIY (50%)  The Name Class

##### An Empty String (before we begin)
> In this part of the workshop, we refer to a Cstring as empty if it has no characters or it has only spaces. So ```""``` and ```"     "``` are both considered empty strings it this senario.

## Name
Create a class encapsulating a Name. 

A Name object encapsulates three parts; First name, Middle name, and last name. The lengths of all three parts are unknown and should be kept dynamically.

### construction
A Name object can be created in four different ways:
1- No argument. In this case, the Name is in a safe empty state.
2- One argument (Cstring). Only the first name is set.
3- Two arguments (Cstring), First name and last name are set.
4- Three arguments (Cstring), First, Middle and Last names are set.

For the latest three, if any of the parts of the name provided are null or [empty](#an-empty-string), the name object will be set into an empty state. 

### Rule of three
A name can be safely copied or assigned to another name and its destruction will cause no memory leak.

### Short form. 
The name must have a modifier method called "setShort" that accepts a boolean argument. If the argument passed is true, the middle name will be abbreviated when printed. ([See Insertion to ostream](#insertion-to-ostream) for more detail)

### Adding a Cstring
A Cstring can be added to a Name object using a += operator, returning the reference of the object as follows.

When a Cstring is added to the name, it will be used to set the next available part of the name:
- If the first name is null, it will set the first name. Otherwise, if the middle name is null it will set the middle name, or else, if the last name is null, it will set the last name. 
- If the name has all the three parts, the operation fails and sets the object into an invalid empty state.
- If there are spaces in the Cstring the operation fails. The Name object is then set to an invalid state
- If the string is null or  [empty](#an-empty-string) the operation is aborted and the object will not change.

## Extraction from istream
Using operator>>, a Name can be extracted from the istream.
A name entry is space separated ending with a newline. 
A valid name can be:
```text
1. FirstName<NEW LINE>
2. FirstName<SPACE>LastName<NEW LINE>
3. FirstName<SPACE>MiddleName<SPACE>LastName<NEW LINE>
```
If after the third part a new line is not immediately following  the last name the object is set to an invalid state:
```text
FirstName<SPACE>MiddleName<SPACE>LastName<SPACE>Whatever
```
> Hint: use the standard C++ string class to read the name parts from the console before dynamic memory allocation. See the example under the "String Class" section in [Input and Operators Chapter](https://ict.senecacollege.ca/~oop244/pages/content/custo.html). Note that this is the only case in which you are allowed to use the standard C++ string class.

## Insertion to ostream
Using operator<<, a Name can be inserted into ostream. 

When a name is inserted into ostream and all three parts are not null, they will be printed separated by a space:

```text
{"Homer", "Jay", "Simpson"}  
is printed as
Homer Jay Simpson
```

If the Name is set to be displayed in [Short format](#short-version) the middle name will be abbreviated:

```text
{"Homer", "Jay", "Simpson"}  
is printed as
Homer J. Simpson
```

If the middle name is null, then the first and last name is printed separated by a space:

```text
{"Bart", nullptr,  "Simpson"}
is printed as
Bard Simpson
```

If the middle name and last name are null, then the name is printed:

```text
{"Lisa", nullptr,  nullptr}
is printed as
Lisa
```

If the name is invalid ```Bad Name``` is printed.

## State of validity (type conversion)
If a Name object is casted to the Boolean type it should return false if it is in an invalid empty state otherwise it should return true; (A Name is valid if at least the first name is not null)

## Tester program

```C++
/* ------------------------------------------------------
Workshop 6 part 2
Module: N/A
Filename: main.cpp
Version 1
Author: Fardad Soleimanloo  22/02/06
Revision History
-----------------------------------------------------------
Date       Reason
-----------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include "Name.h"
using namespace sdds;
using namespace std;

void printNames(const Name* n, int size=1) {
   cout << "Names;" << endl << "First (Middle) Last" << endl;
   for (int i = 0; i < size; i++) {
      cout << n[i] << endl;
   }
}
// get a copy of the Name
void printName(Name N, bool shortOnly= false) {
   if (!shortOnly) {
      N.setShort(false);
      cout << "Name: " << N << endl;
   }
   N.setShort(true);
   if (!shortOnly) cout << "Short: ";
   cout << N << endl;
}

void nameTester(const char* prompt) {
   Name N;
   cout << prompt;
   cin >> N;
   if (N) {
      printName(N);
   }
   else {
      cout << N << " entry!!!" << endl;
      cin.ignore(1000, '\n');
   }
}

int main() {
   Name A[4] = { {"Homer"},{"Homer", "Simpson"}, {"Homer", "Jay", "Simpson"} };
   Name N = "Milhouse";
   printNames(A, 4);
   nameTester("Enter the follwing:\n> Homer Jay Simpson Adams\n> ");
   nameTester("Enter the follwing:\n> Homer Jay Simpson\n> ");
   nameTester("Enter the follwing:\n> Homer Simpson\n> ");
   nameTester("Enter the follwing:\n> Homer\n> ");
   cout << N << "+= \"\": " << (N += "") << endl;
   cout << N << "+= \"    \": " << (N += "   ") << endl;
   cout << N << "+= Van: " << (N += "Van") << endl;
   cout << N << "+= Houten: " << (N += "Houten") << endl;
   cout << N << "+= Adams: " << (N += "Adams") << endl;
   cout << A[3] << "+= Fred: " << (A[3] += "Fred") << endl;

   A[1] = A[2];
   cout << "An assigned name: " << A[1] << endl;
   A[2] = A[2];
   cout << "A self assigned name: " << A[1] << endl;
   ifstream names("names.txt");
   cout << endl << "Names in the file in short form:" << endl
      << "-------------------------------" << endl;
   while (names) {
      // this will call operator>> since ifstream is an istream but for files
      names >> N;
      if (names) {
         if (N) {
            printName(N, true);
         }
         else {
            cout << "--------------Bad record!!!" << endl;
            names.clear();
            names.ignore(1000, '\n');
         }
      }
   }

   return 0;
}
```




## Reflection

Study your final solutions for each deliverable of the workshop, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop.  **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this workshop and mention any issues that caused you difficulty.

You may be asked to talk about your reflection (as a presentation) in class.

## Part 2 - DIY Submission 
### Files to submit:  
```text
Name.h
Name.cpp
main.cpp
```
#### Custom code submission

If you have any additional custom code, (i.e. functions, classes etc) that you want to reuse in this workshop save them under a module called Utils (`Utils.cpp and Utils.h`) and submit them with your workshop using the instructions in the "[Submitting Utils Module](#submitting-utils-module)" section.

### Data Entry

??? explain what data  will be used for submission and testing

### Submission Process:

Upload your the files listed above and your data file to your `matrix` account. Compile and run your code using the `g++` compiler as shown in [Compiling and Testing Your Program](#compiling-and-testing-your-program) and make sure that everything works properly.

Then, run the following command from your account
- replace `profname.proflastname` with your professor’s Seneca userid
- replace **??** with your subject code (2**00** or 2**44**)
- replace **#** with the workshop number
- replace **X** with the workshop part number (**1** or **2**) 
```text
~profname.proflastname/submit 2??/w#/pX
```
and follow the instructions.

#### Submitting Utils Module
To have your Utils module compiled with your workshop and submitted, add a **u** to the part number of your workshop (i.e **u**p1 for part one and **u**p2 for part two) and issue the following submission command instead of the above:
```text
~profname.proflastname/submit 2??/w#/upX
```
See [Custom Code Submission](#custom-code-submission) section for more detail

> **⚠️Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Re-submissions will attract a penalty.

