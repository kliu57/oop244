# Workshop #9: Derived Classes and Resources
- Version 1.1 (added `#include <fstream>` to main.cpp)
- Version 1.2 (Corrected saveHtml() filename in `main_prof.cpp` at submission time)

In this workshop, you are to code/complete two classes:
- **Text:** A class that can read the contents of a text file into memory and insert it into ostream.
- **HtmlText**: A **Text** Class that has a title and can insert the text contents of the class into ostream in simple HTML format. 

## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- Apply [the rule of three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)) and its derived class.
- Use your acquired skills throughout the semester to read a file into dynamically allocated memory.
- describe what you have learned in completing this workshop


## Submission Policy


The workshop is divided into one coding part and one non-coding part:

- Part 1: worth 100% of the workshop's total mark, is due on **Thursday at 23:59:59** of the week of your scheduled lab.
- Part 2 (reflection): non-coding part, is due on **Sunday at 23:59:59** of the week of your scheduled lab. The reflection doesn't have marks associated with it but can incur a **penalty of max 40% of the whole workshop's mark** if your professor deems it insufficient (you make your marks from the code, but you can lose some on the reflection).

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


# Lab (Part 1, 100%)

## Text class

**Text** class is created by a default constructor that sets the class to an empty state.


### Character pointer attribute for content (private)
Text class has only one attribute (**m_content**) that holds the content of the text file dynamically. 

### Methods
#### const char& operator[](int index)const; (protected)
This index operator provides read-only access to the content of the text for the derived classes of Text.

The behaviour of the operator is not defined if the index goes out of bounds or if the content is null.

#### The rule of three
Implement the rule of three so the allocated memory is managed properly in case of copying and assignment.

#### read
Receives an istream reference and returns it at the end.
- deallocates the content
- allocates memory to the [size of the file on the disk](#getfilelength) + 1 (for the null byte).
- reads the file into the allocated memory (character by character to the end)
- if any data is read, it will clear() the state of the istream object, otherwise, it will leave it as is.

#### write
Receives an ostream reference and returns it at the end of the function.

This virtual function will insert the content of the Text class into the ostream if **m_content** is not null. Also, this function does not change the content of a file.

### Helper functions

#### insertion and extraction overload into ostream and from istream
Overload the insertion and extraction operators using the write and read methods

### Usage Sample

If the file **test.txt" has the following content:
```text
abc\ndefg
```

Having the following code snippet:
```C++
Text T;
Text Y;
ifstream test("test.txt");
test >> T;
Y = T;
Text Z = Y;
T = Z;
cout << "*" << T << "*" << endl;
```
The output will be:
```Text
*abc
defg*

```

### getFileLength
To be able to allocate dynamic memory and read the content of a file into the memory, you need to know the size of the text file in bytes.

The following function returns the number of bytes in an istream object or the value zero if the stream is in an invalid state.

```C++
  int getFileLength(std::istream& is)  {
      int len{};
      if (is) {
         // save the current read position
         std::streampos cur = is.tellg();
         // go to the end
         is.seekg(0, ios::end);
         // let what is the positions (end position = size)
         len = is.tellg();
         // now go back to where you were.
         is.seekg(cur);
      }
      return len;
   }
```
> You can either add this as a method to the Text class or add it as a utility method in your Utils class (if you are using the Utils class in the workshop.)


## HtmlText class

**HtmlText** class is inherited from the **Text** for an HTML conversion. Make sure, like the **Text** class, [the rule of three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)) is implemented here.

HtmlText add a character pointer as an attribute for holing the title of the HTML file (**m_title**)

**HtmlText** class is created using an argument for the title of the HTML conversion and overrides the virtual write function of the base class.

**HtmlText** is created using title. The constructor will keep the title dynamically as a property. If the provided title is null, the HTML file will have no title, but it is still a valid HTML file. 

### char* m_title property
Holds the title of the HTML conversion dynamically.

### Text::write override

This override will convert the text file to a simple HTML format when writing file as follows:

First the open tags for html page, header and title are inserted into ostream proceeding with the open body tag. Then for all the content of the file when writing: 
- **less than operator(<)** is replaced by ```"&lt;"``` characters
- **greater than operator(>)** is replaced by ```"&gt;"``` characters
- **newline ('\n')** is replaced by ```"<br />\n"``` characters 
- **space character(' ')**:  if more than one, except from the first, the rest are replaced by ```"&nbsp;"```

In the end, the close tags for body and HTML tags are inserted.

You can use your own logic to implement the above, or use the following guidelines:

To accomplish the above do the insertion into ostream as follows:
- create a boolean variable and set it to false to keep track of the occurrence of multiple spaces (let's call it **MS** for Multiple Spaces)
- insert ```"<html><head><title>"```
- if **m_title** is not null, insert the title, otherwise insert ```"No Title"```
- insert ```"</title></head>\n<body>\n"```
- if the **m_title** property is not null insert ```"<h1>" << m_title << "</h1>\n"```
- loop through all the elements of the m_content (using the protected index operator) and convert the characters as follows:
```Text
  Based on the value of the current element in the loop
  In case the value is a space
     if MS is true insert "&nbsp;"
     otherwise set MS to true and then insert a space (' ')
  In case the value is '<'
     insert "&lt;" and set the MS to false
  In case the value is '>'
     insert "&gt;" and set the MS to false
  In case the value is newline '\n'
     insert "<br />\n" and set the MS to false
  In all other cases
     set the MS to false and insert the current value, unchanged.
```
- at the end insert ```"</body>\n</html>"``` to end the html page.



## Tester program

> Another version of this program with a larger data file, that is used for submission, is added to this directory at submission  under the name **main_prof.cpp**

```C++
/* ------------------------------------------------------
Workshop 9 part 1
Module: N/A
Filename: main.cpp
Version 1.1
Author: Fardad Soleimanloo  22/03/26
Revision History
-----------------------------------------------------------
Date       Reason
22/03/27   Missed #include <fstream>
-----------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include "HtmlText.h"
#include "Text.h"
using namespace std;
using namespace sdds;
void show(Text T)  {
   cout << "*" << T << "*" << endl;
}
void saveHtml(HtmlText H) {
   ofstream("dcwrLittle.html")<<H;
}
void displayFile(const char* filename) {
   cout << "File: " << filename << endl;
   cout << "==================================================" << endl;
   ifstream fin(filename);
   char ch = 0;
   while (fin.get(ch)) {
      cout << ch;
   }
   cout << endl << "==================================================" << endl;
}
int main() {
   Text T;
   Text Y;
   Text Z;
   ifstream test("test.txt");
   ifstream dcwrLittle("dcwrLittle.txt");
   test >> T;
   dcwrLittle >> Y;
   Y = T;
   Z = Y;
   show(Y);
   HtmlText H1("Derived Classes and Resources");
   HtmlText H2;
   HtmlText H3;
   dcwrLittle.seekg(0);
   dcwrLittle >> H1;
   dcwrLittle.seekg(0);
   dcwrLittle >> H2;
   H2 = H1;
   H3 = H2;
   saveHtml(H3);
   displayFile("dcwrLittle.html");
   return 0;
}
```
## output

```Text
*abc
defg*
File: dcwrLittle.html
==================================================
<html><head><title>Derived Classes and Resources</title></head>
<body>
<h1>Derived Classes and Resources</h1>
Design classes with dynamically allocated resources to model the components of a programming solution<br />
Define the copy constructor and assignment operator for a derived class with a resource<br />
Identify the copy constructor and copy assignment operator defaults for a derived class<br />
"If you use pointers, you have to think about resource management" (Stroustrup, 1997)<br />
<br />
Inheritance hierarchies that access resources at multiple levels require intervention. &nbsp;Managing relationships between the special member functions in a hierarchy with multiple resources involves ensuring that the appropriate calls between these functions are made. &nbsp;The definitions of some copy constructors and copy assignment operators in the hierarchy may require explicit coding of the connections to their base class counterparts. <br />
<br />
This chapter describes how to define the constructors and the copy assignment operators in a hierarchy that access multiple resources and how to call their base class counterparts. <br />
<br />
<br />
CONSTRUCTORS AND DESTRUCTOR<br />
<br />
Each constructor of a derived class calls a constructor of its base class. &nbsp;By default, that constructor is the no-argument constructor. &nbsp;To override this default, we insert an explicit call to the base class constructor. <br />
<br />
Destructors in an inheritance hierarchy do not require any intervention, since each class in the hierarchy has but one destructor and each destructor calls its sole base class counterpart automatically. <br />
<br />
Example<br />
<br />
Let us upgrade the definition of our Student class to accommodate a client-defined number of grades. &nbsp;We store the grades in dynamic memory and store the address of that memory in a resource instance pointer. <br />
<br />
The upgraded definition of our Student class contains a resource instance pointer:<br />
<br />
 // Student.h<br />
<br />
 #include &lt;iostream&gt;<br />
 const int NC = 30;<br />
<br />
 class Person {<br />
 &nbsp;&nbsp;&nbsp;&nbsp;char name[NC+1];<br />
 &nbsp;&nbsp;public:<br />
 &nbsp;&nbsp;&nbsp;&nbsp;Person();<br />
 &nbsp;&nbsp;&nbsp;&nbsp;Person(const char*);<br />
 &nbsp;&nbsp;&nbsp;&nbsp;void display(std::ostream&) const; <br />
 };<br />
<br />
 class Student : public Person {<br />
 &nbsp;&nbsp;&nbsp;&nbsp;int no;<br />
 &nbsp;&nbsp;&nbsp;&nbsp;float* grade;<br />
 &nbsp;&nbsp;&nbsp;&nbsp;int ng;<br />
 &nbsp;&nbsp;public:<br />
 &nbsp;&nbsp;&nbsp;&nbsp;Student();<br />
 &nbsp;&nbsp;&nbsp;&nbsp;Student(int);<br />
 &nbsp;&nbsp;&nbsp;&nbsp;Student(const char*, int, const float*, int); <br />
 &nbsp;&nbsp;&nbsp;&nbsp;~Student();<br />
 &nbsp;&nbsp;&nbsp;&nbsp;void display(std::ostream&) const;<br />
 };</body>
</html>
==================================================
```
## Submission
### Files to submit
```Text
Text.h
Text.cpp
HtmlText.h
HtmlText.cpp
main.cpp
```

#### Custom code submission

If you have any additional custom code, (i.e. functions, classes etc) that you want to reuse in this workshop save them under a module called Utils (`Utils.cpp and Utils.h`) and submit them with your workshop using the instructions in the "[Submitting Utils Module](#submitting-utils-module)" section.

### Data Entry

Follow the instructions in the tester program

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

#### Submitting Utils Module
To have your Utils module compiled with your workshop and submitted, add a **u** to the part number of your workshop (i.e **u**p1 for part one and **u**p2 for part two) and issue the following submission command instead of the above:
```text
~profname.proflastname/submit 2??/w#/upX
```
See [Custom Code Submission](#custom-code-submission) section for more detail

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
