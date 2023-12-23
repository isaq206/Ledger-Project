#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
#include "record.h"
//using namespace std;

/*************************************************************************
* Main method. What else can I say.
*************************************************************************/
int main() 
{
   //INPUT VARIABLES
   char choice;

   //INTEGER VARIABLES
   int reviewCounter; //Used in showing location of each item in vector when reviewing the contents.

   //BEGINNING OF IMPLEMENTATION

   do {
       std::cout << "What would you like to do?\n N - Create new document.\n L - Load The Data.\n U - Update Finances.\n R - Review Data.\n S - Save The Data\n Q - Exit Program" 
      << std::endl << "\n>";
       std::cin >> choice;
       std::cout << std::endl;

      switch(choice) {
         case 'N':
         case 'n':
            //createData(recordContent, fileName);
            break;
         case 'L':
         case 'l':
            try 
            {
              // grabInFile(fileName);
              // readInFile(fileName, recordContent);
            }
            catch (const char* e)
            {
                std::cout << e << std::endl;
            }
            break;
         case 'U':
         case 'u':
            //updateData(recordContent);
            break;
         case 'R':
         case 'r':

            break;
         case 'S':
         case 's':
            //grabInFile(fileName);
            //saveData(fileName, recordContent);
            break;
         case 'Q':
         case 'q':
            return 0;
      } 
   }
   while(choice);
}
