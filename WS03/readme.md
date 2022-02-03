# Workshop #3: Member Functions and Privacy
* version 1.1  
   * Part 1 // (v1.1) minor fixed applied
   * Part 2 
 

In this workshop, you will use member functions, privacy, safe empty state and formatting the output to complete your work.

## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities:

- to define a class type
- to privatize data within the class type
- to instantiate objects of class type
- to use member functions to query the state of an object
- to use member functions to change the state of an object
- to use standard library facilities to format data inserted into the output stream
- to describe to your instructor what you have learned in completing this workshop

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

# Part 1 (50%) The Train Class

Code a Train class that holds the information for a Train. The class must have private data members to include the following information:
a) the name of a train,
b) the number of people on a train, and
e) the speed of a train (km/hour).

Declare three C++ constants, namely MAX_NAME_LEN, MAX_PEOPLE and MAX_SPEED. Set MAX_NAME_LEN to 20, MAX_PEOPLE to 1000 and MAX_SPEED to 320.

Declare three private data members. Declare an array to hold th e name of a train, not exceeding MAX_NAME_LEN characters. Declare an integer variable for the number of people on a train. Declare a double variable for the speed of a train.

Store your class definition in a header file named Train.h and your member function definitions in an implementation file named Train.cpp.

Declare and implement the following member functions.

The member function set( ):
     ```void set(const char*, int, double);```
It uses three input parameters to initialize a Train object. It receives the name of the train, the number of people on the train and the speed of the train. It validates the data values received and uses these data values to set the respective data members, only if all of them are valid. 
            
All the data values are valid if a) the first parameter is not nullptr and the length of the name is greater than zero, b) the number of people is between zero and MAX_PEOPLE (inclusive), and c) the speed is between zero and MAX_SPEED (inclusive). You must use strncpy() to copy the first MAX_NAME_LENGTH characters from the input parameter to the data member that holds the name of a train.

If the data values are invalid, the member function initializes the Train object to a safe empty state. You may use your own definition of a safe empty state. However, you must document your definition as comments. Otherwise you will lose marks.

The member function getNumberOfPeople:
    ```int getNumberOfPeople() const;```
This query returns the  number of people on a train.

The member function getName: 
   ``` const char* getName() const; ```
This query returns the name of a train.

The member function getSpeed:
    ```double getSpeed() const;```
This query returns the speed of a train.
   
The member function isSafeEmpty: 
     ```bool isSafeEmpty() const;```
This query returns true if the Train object is in a safe empty state; false otherwise.

The member function display: 
    ```void display() const;```
This member function sends the information about a Train to standard output in the following format if the object holds valid data values.
```
NAME OF THE TRAIN : XXXXXXXXXXX<ENDL>
NUMBER OF PEOPLE  : XXXX<ENDL>
SPEED             : XXXX.XX km/h<ENDL>
```
If the object is in a safe empty state, the function displays the following message:
```Safe Empty State!```

## Testing Program
```
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
#include "Train.h"
using namespace sdds;

int main() {

	Train trains[7];

	trains[0].set(nullptr, 100, 123.55);;
	trains[1].set("", 100, 123.55);
	trains[2].set("VIA Rail Abitibi", -100, 123.45);
	trains[3].set("VIA Rail Abitibi", 100, -123.45);
	trains[4].set("VIA Rail Abitibi", 100, 5000);
	trains[5].set("Seneca Express", -1, -1);
	trains[6].set("VIA Rail Abitibi", 333, 115.95);

	cout << "----------------------------------------" << endl;
	cout << "1. Testing the validation logic." << endl;
	cout << "(only trains[6] should be valid)" << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < 7; ++i)
	{
		cout << "trains[" << i << "]: "
			<< (trains[i].isSafeEmpty() ? "not valid" : "valid") << endl;
	}
	cout << "----------------------------------------" << endl << endl;

	//
	cout << "----------------------------------------" << endl;
	cout << "2. Testing the display function." << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < 7; ++i)
	{
		trains[i].display();
	}
	cout << "----------------------------------------" << endl << endl;

	cout << "----------------------------------------" << endl;
	cout << "3. Testing the member functions." << endl;
	cout << "----------------------------------------" << endl;

	Train t2;

	t2.set("Bullet Train", 100, 245.95);

	cout << t2.getNumberOfPeople()
		 << ','
		 << t2.getName()
		 << ','
		 << t2.getSpeed() << endl;
	cout << "----------------------------------------" << endl << endl;

	return 0;
}
 
```

## Sample Output
```
----------------------------------------
1. Testing the validation logic.
(only trains[6] should be valid)
----------------------------------------
trains[0]: not valid
trains[1]: not valid
trains[2]: not valid
trains[3]: not valid
trains[4]: not valid
trains[5]: not valid
trains[6]: valid
----------------------------------------

----------------------------------------
2. Testing the display function.
----------------------------------------
Safe Empty State!
Safe Empty State!
Safe Empty State!
Safe Empty State!
Safe Empty State!
Safe Empty State!
NAME OF THE TRAIN : VIA Rail Abitibi
NUMBER OF PEOPLE  : 333
SPEED             : 115.95 km/h
----------------------------------------

----------------------------------------
3. Testing the member functions.
----------------------------------------
100,Bullet Train,245.95
----------------------------------------

```
## PART 1 Submission 

### Files to submit:  

```Text
Train.h
Train.cpp
w3_part1_Tester.cpp

```
Upload your source code and data file to your `matrix` account. Compile and run your code using the `g++` compiler as the execution sample above and make sure that everything works properly.

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

## Part 2: DIY
Declare and implement two member functions and a global function that will change the state of a Train object. These functions will NOT change the state of a Train object if it is in a safe empty state. Note: Review the testing program and the sample output in order to understand the behaviour of these three functions. 

The member function ```loadPeople``` changes the number of people on a train. The value of the input parameter is used to increase or decrease the number of people on  a train. It must make sure that the number of people will not be negative or exceed MAX_PEOPLE. It returns true if the operation succeeds. It returns false if the Train object is in a safe empty state.

The member function ```changeSpeed``` changes the speed of a train. The value of the input parameter is used to increase or decrease the speed of  a train. It must make sure that the speed of a train will not be negative or exceed MAX_SPEED. It returns true if the operation succeeds. It returns false if the Train object is in a safe empty state.

A global function ```transfer``` moves as many passengers as possible from the second Train to the first Train. It has two parameters (first, second) that reference two Train objects. The function must make sure that the number of people on both Train objects will not be negative or exceed MAX_PEOPLE. It returns the number of people that have been moved to the first Train. It returns -1 if any of the Train objects is in a safe empty state. 

## Testing Program
```
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
#include "Train.h"
using namespace seneca;

int main() {
	Train trains[3];

	trains[1].set("Bullet Train", 100, 245.95);
	trains[2].set("VIA Rail Abitibi", 250, 115.95);
	trains[0] = trains[1];  // Watch out!

	cout << "----------------------------------------" << endl;
	cout << "1. Testing changeSpeed." << endl;
	cout << "----------------------------------------" << endl;

	trains[1].changeSpeed(15);
	trains[2].changeSpeed(-30);
	trains[1].display();
	trains[2].display();

	trains[1].changeSpeed(500);
	trains[2].changeSpeed(-600);
	trains[1].display();
	trains[2].display();

	cout << "----------------------------------------" << endl << endl;

	cout << "----------------------------------------" << endl;
	cout << "2. Testing loadPeople." << endl;
	cout << "----------------------------------------" << endl;

	trains[1].loadPeople(101);
	trains[2].loadPeople(-55);
	trains[1].display();
	trains[2].display();

	trains[1].loadPeople(1500);
	trains[2].loadPeople(-2000);
	trains[1].display();
	trains[2].display();

	cout << "----------------------------------------" << endl << endl;

	cout << "----------------------------------------" << endl;
	cout << "3. Testing transfer." << endl;
	cout << "----------------------------------------" << endl;

	transfer(trains[1], trains[2]);
	trains[1].display();
	trains[2].display();

	trains[2].loadPeople(955);

	transfer(trains[2], trains[0]);
	trains[2].display();
	trains[0].display();  // Watch out!

	cout << "----------------------------------------" << endl << endl;

	cout << "----------------------------------------" << endl;
	cout << "4. Testing transfer (safe empty states)." << endl;
	cout << "----------------------------------------" << endl;
	
	trains[0].set(nullptr, -1, -1); // safe empty state
	cout << ( transfer( trains[0], trains[1] ) ) << endl;
	cout << ( transfer( trains[1], trains[0] ) ) << endl;
	
	cout << "----------------------------------------" << endl << endl;
	return 0;
}
```
## Sample Output
```
----------------------------------------
1. Testing changeSpeed.
----------------------------------------
NAME OF THE TRAIN : Bullet Train
NUMBER OF PEOPLE  : 100
SPEED             : 260.95 km/h
NAME OF THE TRAIN : VIA Rail Abitibi
NUMBER OF PEOPLE  : 250
SPEED             : 85.95 km/h
NAME OF THE TRAIN : Bullet Train
NUMBER OF PEOPLE  : 100
SPEED             : 320.00 km/h
NAME OF THE TRAIN : VIA Rail Abitibi
NUMBER OF PEOPLE  : 250
SPEED             : 0.00 km/h
----------------------------------------

----------------------------------------
2. Testing loadPeople.
----------------------------------------
NAME OF THE TRAIN : Bullet Train
NUMBER OF PEOPLE  : 201
SPEED             : 320.00 km/h
NAME OF THE TRAIN : VIA Rail Abitibi
NUMBER OF PEOPLE  : 195
SPEED             : 0.00 km/h
NAME OF THE TRAIN : Bullet Train
NUMBER OF PEOPLE  : 1000
SPEED             : 320.00 km/h
NAME OF THE TRAIN : VIA Rail Abitibi
NUMBER OF PEOPLE  : 0
SPEED             : 0.00 km/h
----------------------------------------

----------------------------------------
3. Testing transfer.
----------------------------------------
NAME OF THE TRAIN : Bullet Train
NUMBER OF PEOPLE  : 1000
SPEED             : 320.00 km/h
NAME OF THE TRAIN : VIA Rail Abitibi
NUMBER OF PEOPLE  : 0
SPEED             : 0.00 km/h
NAME OF THE TRAIN : VIA Rail Abitibi
NUMBER OF PEOPLE  : 1000
SPEED             : 0.00 km/h
NAME OF THE TRAIN : Bullet Train
NUMBER OF PEOPLE  : 55
SPEED             : 245.95 km/h
----------------------------------------

----------------------------------------
4. Testing transfer (safe empty states).
----------------------------------------
-1
-1
----------------------------------------
```
## Reflection

Study your final solutions for each deliverable of the workshop, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop.  **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this workshop and mention any issues that caused you difficulty.

You may be asked to talk about your reflection (as a presentation) in class.

## DIY Submission (Part 2)
### Files to submit:  
```Text
Train.h
Train.cpp
w3_part2_Tester.cpp
reflect.txt
```

Upload your source code and data file to your `matrix` account. Compile and run your code using the `g++` compiler as shown above and make sure that everything works properly.

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

