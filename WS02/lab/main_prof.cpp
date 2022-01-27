/* ------------------------------------------------------
Workshop 2 part 1
Module: N/A
Filename: main_prof.cpp
Version 1
Author	Fardad Soleimanloo
Revision History
-----------------------------------------------------------
Date       Reason
-----------------------------------------------------------
this main will be tested as follows by redirecting the input
from a file so the students don't have to the entry.

If you like to run this test first compile your code an then

On linux execute the following (if ws is name of the executable)
> valgrind ws < car.csv

on windows, 
Either copy car.csv to the debug directory of the project and execute 
thefollowing from command line
> lab < car.csv <ENTER>

or right click on the project name in solution explorer 
and select the following
lab(porject name)->properties->Configuation Properties->Debugging
Then On the right in the Command Argument text box type "< car.csv"

Note that doing this after execution, the output window will not 
remain open. To keep it from closing at the end you must add a break
point to the end of the main function and press "F5" to compile and run.

*/
#include "Car.h"
using namespace sdds;
int main(){
   Car C;
   initialize(10); 
   while (read(C)) {
      record(C);
   }
   endOfDay();
}
