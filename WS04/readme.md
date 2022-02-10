# Workshop #4: Constructors, Destructors, and the *this* object
* Version 0.9
(Under review)


## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:


- Create default and overloaded constructors
- Create destructors
- Initialize class member variables 
- Release member pointers


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


# Part 1 - lab (50%) 
## `CarInventory` Module
Design and implement a class named `CarInventory` that stores the following information for a car entry:
* Type of the car (i.e SUV)
* The brand of the car (i.e Volvo)
* The model of the car (i.e XC90)
* The year of the car (i.e 2021)
* The code for the car inventory (i.e 100)
* The price of the car (i.e 90000)

Each object of the class `CarInventory` can be created in either of the following ways:
* By default set everything to null and 0
* Provide the type, brand, and model of the car
* Provide all the required information

The `CarInventory` provides functionalities to reset the information, add information, print the information, check the validity of the information, and check if two entries are the same. Details of these will be provided below.

## Implementation
Create a class named `CarInventory` and add the following members.

### Private Member Variables

```C++
char* m_type;
char* m_brand;
char* m_model;
int m_year;
int m_code;
double m_price;
```
#### Valid CarInventory member variable values  
```Text
type, not null
brand, not null
model, not null
year >= 1990
code, three digit integer
price > 0
```
### Constructors
```C++
CarInventory();
```
The default constructor will initialize the member variables by calling the `resetInfo()` method (the details of this method will be provided in the **Private Member** section.

--------------------------------------------------------

```C++
CarInventory(const char* type, const char* brand, const char* model, int year, int code, double price);
```
This constructor will dynamically keep the values of the C-string argument in their corresponding attributes and set the rest of the attributes the corresponding argument values if they pass validation. Otherwise it will reset the information (see **void resetInfo()**)<br />

When instantiated using this constructor, if the **year**, **code** or **price** arguments are not provided they will be set to **2022**, **100** and **1**  using default values for the arguments.

--------------------------------------------------------
### Destructor
This destructor should deallocate the dynamically allocated memory in type, brand, and model.
--------------------------------------------------------

### Private Member
```C++
void resetInfo();
```
This method resets the values for all member variables by setting type, brand, and model to **nullptr** and setting the year, code, and price to 0.

--------------------------------------------------------
### Public Members
```C++
CarInventory& setInfo(const char* type, const char* brand, const char* model, int year, int code, double price);
```
This method will first deallocate all the allocated memory and then sets the attributes to the corresponding arguments exactly like the 6 argument constructor. <br />
Note: this function does not have any default values for its arguments.<br />
In the end, it will return the reference of the current object.


--------------------------------------------------------
```C++
void printInfo() const;
```
This method prints the values of all the member variables on the screen in following format.<br />
Order:<br />
TYPE,BRAND,MODEL,YEAR,CODE,PRICE<br />
Spacing:
```text
| 10  spaces | 16        spaces | 16        spaces | 9999 |  999 | 999999.99 |
```

--------------------------------------------------------
```C++
bool isValid() const;
```
This method returns whether all member variables have valid values or not based on the criteria stated at the [Private Member Variables](#valid-carinventory-member-variable-values).

--------------------------------------------------------
```C++
bool isSimilarTo(const CarInventory& car) const;
```
This function is to check whether the type, make, brand and year of an object of `CarInventory` are equal to another object of this class. The function will return `true` only if all those values match. 

--------------------------------------------------------
Also, implement a global function in the `sdds` namespace to check whether there are duplicate entries in the entire inventory.
```C++
bool find_similar(CarInventory car[], const int num_cars)
```
It returns `true` if it finds two `CarInventory` objects that have similar information in the car array. See below for the function implementation logic:
```C++
for (int i = 0; i < num_cars; i++){
  for (int j = i+1; j < num_cars; j++){
    if (car[i] is Simialr to car[j]){
        // match is found
    }
  }
}
```
--------------------------------------------------------

### Tester Program
```C++
#include<iostream>
#include<iomanip>
#include "CarInventory.h"
using namespace std;
using namespace sdds;

int main()
{
	const int num_cars = 6;
	bool invalid_data = false;
	CarInventory cars[num_cars] = {
		{},
		{"suv", "volvo", "xc90"},
		{"Truck", "Ford", "F 150", 2021, 105, 55000},
		{"Sedan", "BMW", "M550i", 2022, 101, 91000},
		{"Truck", "Tesla", "Cybertruck", 2021, 102, 65000},
		{"Sedan", "BMW", "M550i"}
	};
	
	if (cars[2].setInfo("SUV", "Volvo", "XC90", 2019, 109, 80000).isValid()) {
		cout << "Information was set correctly!" << endl;
	}
	else {
		cout << "Information was set incorrectly!" << endl;
	}
	if(cars[1].setInfo("SUV", "Volvo", "XC90",1234,1,1).isValid()){ 
		cout << "Information was set correctly!" << endl;
	}
	else {
		cout << "Information was set incorrectly!" << endl;
	}


	cout << setw(60) << "----- Car Inventory Information -----" << endl << endl;;
	cout << "| Type       | Brand            | Model            | Year | Code |     Price |" << endl;
	cout << "+------------+------------------+------------------+------+------+-----------+" << endl;
	for (int i = 0; i < num_cars; i++) {
		if (cars[i].isValid())
			cars[i].printInfo();
		else
			invalid_data = true;
	}
	
	if (invalid_data) {
		cout << endl;
		cout << setfill('*') << setw(60) << "*" << endl;
		cout << "*  WARNING: There are invalid data in the inventory!      *" << endl;
		cout << setfill('*') << setw(60) << "*" << endl;
	}
	if (find_similar(cars, num_cars)) {
		cout << endl;
		cout << setfill('+') << setw(60) << "+" << endl;
		cout << "+  WARNING: There are similar entries in the inventory!   +" << endl;
		cout << setfill('+') << setw(60) << "+" << endl;
	}
	return 0;
}
```
### Expected Output
```Text
Information was set correctly!
Information was set incorrectly!
                       ----- Car Inventory Information -----

| Type       | Brand            | Model            | Year | Code |     Price |
+------------+------------------+------------------+------+------+-----------+
| SUV        | Volvo            | XC90             | 2019 |  109 |  80000.00 |
| Sedan      | BMW              | M550i            | 2022 |  101 |  91000.00 |
| Truck      | Tesla            | Cybertruck       | 2021 |  102 |  65000.00 |
| Sedan      | BMW              | M550i            | 2022 |  100 |      1.00 |

************************************************************
*  WARNING: There are invalid data in the inventory!      *
************************************************************

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+  WARNING: There are similar entries in the inventory!   +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
```

### Files to submit:  

```Text
CarInventory.h
CarInventory.cpp
main.cpp
```

### Data Entry

No Data Entry required.

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



# PART 2 - DIY (50%)


Create a module for a robot deployed by a Control Room. A robot object displays the details of the robots in the designated areas.

The class name is called `Robots` and should hold the following information for a robot:
* Name (Dynamic Cstring)
* Location (Dynamic Cstring)
* Weight (double)
* Width (double)
* Height (double)
* Speed (double)
* Deployed (YES|NO)

### Public and mandatory functions, constructors, and destructor

#### Constructors
* Default constructor for a robot with no information to set the robot into an empty state
* Constructor with 7 arguments to initialize the robot information in the following order:<br />
name, location, weight, width, height, speed, deployment


#### Destructor
* The destructor must handle any potential memory leak.

#### Functions
##### Modifiers
* `set`: to set the robot information (same order as the constructor)
* `setLocation`: to set the robot location
* `setDeployed`: to set the robot deployment status (true or false)

##### Queries
* `getName`: to return the robot name  
* `getLocation`: to return the robot location
* `isDeployed`: to return if a robot is deployed
* `isValid`: to return if the robot information is valid
* `speed`: to return the speed of the robot
-----------------------------------
* `display`: to display the information in the following format. (Numbers on top are not printed; they are used as a ruler)
```Text
Name, Location, Weight, Width, Height, Speed, Deployed:
         1         2         3         4         5         6         7         8 
12345678901234567890123456789012345678901234567890123456789012345678901234567890
| NAME       | LOCATION        | 9999.9 | 9999.9 | 9999.9 | 9999.9 | NO/YES   |
Example:
| R2D2       | Tatooine        |  123.9 |   14.5 |   32.0 |   12.2 | YES      |
```

#### The Control Room stand alone report function
```C++
int conrtolRooomReport(const Robot robot[], int num_robots);
```
This function receives an array of robots and prints a report of their information and a summary that prints the total number of deployed robots and the information of the fastest robot in the array.

If during the printout of the array an invalid robot is detected, printing stops and the index of the invalid robot in the array is returned. 
  
If no Invalid robot is detected, the summary is printed and the value -1 is returned.

Function execution sample for an array of robots with the fourth robot being invalid:
```Text
                        ------ Robot Control Room -----
                    ---------------------------------------
| Robot ID   | Location        | Weight |  Width | Height |  Speed | Deployed |
|------------+-----------------+--------+--------+--------+--------+----------|
| C3PO       | Control Room    |   10.0 |    4.0 |    1.0 |    2.1 | NO       |
| KC1        | kitchen         |   25.3 |    4.5 |    2.0 |    2.2 | NO       |
| BR1        | bedroom         |    5.2 |    2.5 |    1.0 |    2.2 | YES      |
```
And the function will return `3`

Function execution sample for an array of valid robots:
```Text
                        ------ Robot Control Room -----
                    ---------------------------------------
| Robot ID   | Location        | Weight |  Width | Height |  Speed | Deployed |
|------------+-----------------+--------+--------+--------+--------+----------|
| C3PO       | Control Room    |   10.0 |    4.0 |    1.0 |    2.1 | NO       |
| KC1        | kitchen         |   25.3 |    4.5 |    2.0 |    2.2 | NO       |
| BR1        | bedroom         |    5.2 |    2.5 |    1.0 |    2.2 | YES      |
| D3PO       | Control Room    |   10.0 |    4.0 |    1.0 |    2.1 | NO       |
| KC2        | kitchen         |   20.6 |    5.0 |    2.0 |    3.5 | YES      |
| BR2        | bedroom         |   25.3 |    6.5 |    2.5 |    3.1 | YES      |
|=============================================================================|
| SUMMARY:                                                                    |
| 3  robots are deployed.                                                     |
| The fastest robot is:                                                       |
| Robot ID   | Location        | Weight |  Width | Height |  Speed | Deployed |
|------------+-----------------+--------+--------+--------+--------+----------|
| KC2        | kitchen         |   20.6 |    5.0 |    2.0 |    3.5 | YES      |
|=============================================================================|
```
And the function will return `-1`.

> You may add as many additional functions to the robot module as you like to accomplish this task

### Tester Program
```C++
#include <iostream>
#include "Robot.h"

using namespace std;
using namespace sdds;

int main()
{
	const int num_robots = 6;
	int broken_robot = 0;
	char replacmentName[] = "C3PO";
	Robot robot[num_robots] = {
		{},
		{"KC1", "kitchen", 25.33, 4.55, 2, 2.2, false},
		{"BR1", "bedroom", 5.22, 2.54, 1, 2.2, true},
		{"Broken", "Bedroom", 10.12, 2.5,1.55, 0, true},
		{"KC2", "kitchen", 20.56, 5, 2, 3.5, true},
		{"BR2", "bedroom", 25.32, 6.5, 2.5, 3.1, true}
	};
	
	while ( (broken_robot = conrtolRooomReport(robot, num_robots) ) >= 0) {
		cout << endl << "Attention: There is a broken robot! Fixing the problem..." << endl;
		robot[broken_robot].set(replacmentName, "Control Room", 10.0, 4, 1, 2.09, false).display();
		replacmentName[0]++;
		cout << "Replacement Provided!" << endl << endl;
	}

	return 0;
}
```

### Expected Output
```Text
                        ------ Robot Control Room -----
                    ---------------------------------------
| Robot ID   | Location        | Weight |  Width | Height |  Speed | Deployed |
|------------+-----------------+--------+--------+--------+--------+----------|

Attention: There is a broken robot! Fixing the problem...
| C3PO       | Control Room    |   10.0 |    4.0 |    1.0 |    2.1 | NO       |
Replacement Provided!

                        ------ Robot Control Room -----
                    ---------------------------------------
| Robot ID   | Location        | Weight |  Width | Height |  Speed | Deployed |
|------------+-----------------+--------+--------+--------+--------+----------|
| C3PO       | Control Room    |   10.0 |    4.0 |    1.0 |    2.1 | NO       |
| KC1        | kitchen         |   25.3 |    4.5 |    2.0 |    2.2 | NO       |
| BR1        | bedroom         |    5.2 |    2.5 |    1.0 |    2.2 | YES      |

Attention: There is a broken robot! Fixing the problem...
| D3PO       | Control Room    |   10.0 |    4.0 |    1.0 |    2.1 | NO       |
Replacement Provided!

                        ------ Robot Control Room -----
                    ---------------------------------------
| Robot ID   | Location        | Weight |  Width | Height |  Speed | Deployed |
|------------+-----------------+--------+--------+--------+--------+----------|
| C3PO       | Control Room    |   10.0 |    4.0 |    1.0 |    2.1 | NO       |
| KC1        | kitchen         |   25.3 |    4.5 |    2.0 |    2.2 | NO       |
| BR1        | bedroom         |    5.2 |    2.5 |    1.0 |    2.2 | YES      |
| D3PO       | Control Room    |   10.0 |    4.0 |    1.0 |    2.1 | NO       |
| KC2        | kitchen         |   20.6 |    5.0 |    2.0 |    3.5 | YES      |
| BR2        | bedroom         |   25.3 |    6.5 |    2.5 |    3.1 | YES      |
|=============================================================================|
| SUMMARY:                                                                    |
| 3  robots are deployed.                                                     |
| The fastest robot is:                                                       |
| Robot ID   | Location        | Weight |  Width | Height |  Speed | Deployed |
|------------+-----------------+--------+--------+--------+--------+----------|
| KC2        | kitchen         |   20.6 |    5.0 |    2.0 |    3.5 | YES      |
|=============================================================================|

```
# Reflection

Study your final solutions for each deliverable of the workshop, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop.  **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this workshop and mention any issues that caused you difficulty.

You may be asked to talk about your reflection (as a presentation) in class.

## Part 2 Submission (DIY)

### Files to submit:  

```reflect.txt``` and:
```Text
Robot.cpp
Robo.h
main.cpp
```

### Data Entry

No data entry required!

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
