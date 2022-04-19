# Workshop #10: Function Templates
Version 1.0

In this workshop, you are to code two function templates:
- "select": to select several elements out of an array to if they match another.
- "printCollection": print the content of a class template 



## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- Code function templates
- Use class templates
- Describe what you have learned in completing this workshop


## Submission Policy


The workshop is divided into one coding part and one non-coding part:

- Part 1: worth 100% of the workshop's total mark, is due on **Wednesday Apr 13th at 23:59:59** .
- Part 2 (reflection): non-coding part, is due on **Friday Apr 15th at 23:59:59**. The reflection doesn't have marks associated with it but can incur a **penalty of max 40% of the whole workshop's mark** if your professor deems it insufficient (you make your marks from the code, but you can lose some on the reflection).

**The code that is submitted late receives 0%.**  
On Sunday at midnight the submission closes; if the workshop is incomplete when the submission closes (missing at least one of the coding or non-coding parts), **the mark for the entire workshop is 0%**.

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



# PART 1 (100%)

Look at the code provided in the **Collection** template module, study it and understand it. The Collection class is a template that works like a dynamic array of objects with a constant size and supports the rule of three. The code snippet below demonstrates how Collection works:  

```C++
int i;
Collection<double> dbls(4);
for(i=0;i<4;i++){
    dbls[i] = 1.1 + i;
}
cout << "There are " << dbls.size() << " items in the Collection:" << endl;
for(i=0;i<4;i++){
    cout << dbls[i] << " ";
}
cout << endl;
```
Output:
```Text
There are 4 items in the Collection!
1.1 2.1 3.1 4.1
```

## Supplied Modules:
- Collection
- Displayable 
- Employee
- Student
- Car

**Do not modify these modules!**  Look at the code and make sure you understand them.


# temps module
Create a module called `temps` and add the following two function templates to it:

## `select` function template
Loop through an array of objects (received as an argument) and compare each element with an object of the same type (also received as an argument). If the two match (using the `==` operator) the element will be added to a Collection object that will be returned at the end.

### Arguments:
- a constant array of objects to select from
- the size of the array
- a constant reference of an object (same type as the objects in the array)

### Returns
- Collection of the same type as the argument object.

### implementation
- The first loop through the array to find out how many many matches are found. 
- Create a collection object of the same size (number of matches)
- Loop through the array again and set the Collection elements to the matches found.
- A the end return the Collection.

## `printCollection` function template
Prints the elements of a Collection object after printing a title in separate lines.

### Arguments 
- a constant Collection object reference 
- a constant character Cstring for title

This function template returns nothing

### implantation

First print the title, then loop through the elements of the Collection up to its size and print each element of the Collection in a newline.

### Template type requirements
Have a comment section for each function and explain what requirements each type of your template must have to be able to work with your logic.

**Then also copy these comments to the part 2 reflection of the workshop.**

## The main module
```C++
/*------------------------------------------------------
Workshop 10 part 1
Module: N/A
Filename : main.cpp
Version 1.0
Author : Fardad Soleimanloo  22/04/01
Revision History
-----------------------------------------------------------
Date       Reason
----------------------------------------------------------- */

#include <iostream>
#include "Car.h"
#include "Employee.h"
#include "Student.h"
#include "Collection.h"
#include "temps.h"
using namespace std;
using namespace sdds;

int main(){

 Student S[7] = { { 22345, "Lisa Simpson", "EAC150"}, {12345, "Bart Simpson", "EAC150"},
                   { 24567, "Ralph Wiggum", "IPC144"}, {56789, "Milhouse Van Houten","IPC144"},
                   { 67890, "Todd Flanders", "BTP200"}, {34567, "Nelson Muntz", "BTP200"},{33223, "Magie Simpson", "EAC150"} };
  Employee E[6] = { Employee(213456, "Carl Carlson", 1000), Employee(122345, "Mindy Simmons", 2000), 
                    Employee(435678, "Lenny Leonard", 1000), Employee(546789, "Waylon Smithers", 3000), 
                    Employee(657890, "Frank Grimes", 3000), Employee(364567, "Homer Simpson", 1000) };
  Car C[7] = { Car("GVBT01", "Tesla","Model S"), Car("BBCDEF", "BMW","320"),
               Car("CDEFG", "Ford","Festiva"),Car("GVAB24", "Tesla","Cyber Truck"), Car("BCDEFG", "Ford","Explorer"),
               Car("AFGHIJ", "Nissan","Maxima"),Car("GVDD99", "Tesla","Model 3") };
  int vals[10] = { 4, 6, 4,  67, 4, 6, 7, 5, 4, 6 };
  
  
  Collection<Car> teslas = select(C, 7,C[0]);
  Collection<Student> classmates = select(S,7, S[0]);
  Collection<Employee> colleagues = select(E,6, E[0]);
  Collection<int> numbers = select (vals, 10, vals[0]);
 
  
  printCollection(teslas, "Tesla Cars:");
  printCollection(classmates, "Classmates:");
  printCollection(colleagues, "Colleagues:");
  printCollection(numbers, "Fours:");
  return 0;
}


```
## output

```Text
Tesla Cars:
GVBT01 Tesla Model S
GVAB24 Tesla Cyber Truck
GVDD99 Tesla Model 3
Classmates:
22345, Lisa Simpson, EAC150
12345, Bart Simpson, EAC150
33223, Magie Simpson, EAC150
Colleagues:
213456, Carl Carlson, 1000
435678, Lenny Leonard, 1000
364567, Homer Simpson, 1000
Fours:
4
4
4
4

```

# Part 1 submission

## Files to submit
```Text
Collection.h
Car.h
Car.cpp
Employee.h
Employee.cpp
Student.h
Student.cpp
Displayable.h
Displayable.cpp
main.cpp
temps.h
```


### Data Entry

No data entry is needed.

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





# PART2: Reflection

Study your final solutions for each deliverable of the workshop **and the most recent milestones of the project**, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop.  **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this workshop and **the project milestones** and mention any issues that caused you difficulty.


## Reflection Submission (part 2)


Upload the **reflect.txt** to your `matrix` account. 

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
