#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
#include "record.h"
using namespace std;

/*************************************************************************
* Main method. What else can I say.
*************************************************************************/
int main() 
{
   //DATA-CONTENT VARIABLES
   string fileName = "\0";  //Used in retrieving file name for fstream when loading and saving.
   vector <string> recordContent;  //This is the main data structure for the program. It will contain and retain any data you put in it until you load in another file.
   vector <string>::iterator it;  //This is a simple iterator for the vector object when we want to review the contents of the vector.

   //INPUT VARIABLES
   char choice;

   //INTEGER VARIABLES
   int reviewCounter; //Used in showing location of each item in vector when reviewing the contents.

   //BEGINNING OF IMPLEMENTATION

   do {
      cout << "What would you like to do?\n N - Create new document.\n L - Load The Data.\n U - Update Finances.\n R - Review Data.\n S - Save The Data\n Q - Exit Program" 
      << endl << "\n>";
      cin >> choice;
      cout << endl;

      switch(choice) {
         case 'N':
         case 'n':
            createData(recordContent, fileName);
            break;
         case 'L':
         case 'l':
            try 
            {
               grabInFile(fileName);
               readInFile(fileName, recordContent);
            }
            catch (const char* e)
            {
               cout << e << endl;
            }
            break;
         case 'U':
         case 'u':
            updateData(recordContent);
            break;
         case 'R':
         case 'r':
            for (it = recordContent.begin(), reviewCounter = 0; it != recordContent.end(); it++) 
            {
               cout << reviewCounter << ". " << *it << endl;
               reviewCounter++;
            }
            cout << endl;
            break;
         case 'S':
         case 's':
            grabInFile(fileName);
            saveData(fileName, recordContent);
            break;
         case 'Q':
         case 'q':
            return 0;
      } 
   }
   while(choice);
}
