#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

void grabInFile(string & fileName) 
{
   cout << "Enter record name: ";
   cin >> fileName;
   cout << endl;
}

void readInFile(string fileName, vector <string> &recordContent) throw (const char*) 
{
   ifstream fin;
   fin.open(fileName);

   if (fin.fail())
      throw ("Error: Cannot read file.");

   if (!recordContent.empty())
      recordContent.clear();

   string fileContent;  //This variable is for the data that is being read in exclusively
   string contentToPush = "";  //This variable is going to be the on eused as a medium for pushing back onto the vector
   int indexForContent = 0;
   int indexForRecord = 0;


   getline(fin, fileContent);

   while(fileContent[indexForContent] != '\0')
   {
      if(fileContent[indexForContent] != '!')
      {
         contentToPush += fileContent[indexForContent];
         indexForContent++;
      }
      else if(fileContent[indexForContent] == '!')
      {
         recordContent.push_back(contentToPush);
//This line was used for debugging purposes.
//         cout << recordContent[indexForRecord] << endl;
         contentToPush.clear();
         indexForRecord++;
         indexForContent++;
      }
   }

   fin.close();
}

void saveData(string fileName, vector <string> recordContent) throw (const char*)
{
   ofstream fout;
   fout.open(fileName);

   if (fout.fail()) {
      throw ("Error: Cannot save file.");
   }

   int counter = 0;
   for (vector <string>::iterator it = recordContent.begin(); it != recordContent.end(); it++, counter++)
   {
      fout << recordContent[counter] << " !";
   }

   fout.close();
}

void updateData(vector <string> &recordContent) 
{
   string choice;
   cout << "Where do you want to start updating? (1, 2, 3,...) Based on \"Review Data\" option in main menu. \nYou can type \"end\""
        << "if you want to update at end of file. Type \"Back\" if you want to go back to main menu.\n\n" << ">";
   cin >> choice;

   if(choice == "Back" || choice == "back")
      return;

   if(choice != "end" || choice != "End")
   {
      string data;
      int index = 0;

      cout << "When finished, please enter \'done\' when finished updating.\n";
      cin.ignore();
      do
      {
         cout << "Enter data. Press enter when finished with each input: ";
         getline(cin, data);
         if(data != "done")
         {
            int count = recordContent.size();
            int designation;
            istringstream ss (choice);
            ss >> designation; 

            recordContent.push_back(recordContent[count-1]);


            for(vector<string>::reverse_iterator it = recordContent.rbegin(); count > designation; ++it)
            {
               recordContent[count] = recordContent[count-1];
//               cout << recordContent[count] << endl;
               count--;
            }
            recordContent[count] = data;
         }
//         cin.ignore();
      }
      while(data != "done");

      cout << endl;
      return;
   }


   else
   {
      string data;
      int index = 0;

      cout << "*When finished, please enter \'done\' when finished updating.\n";
      cin.ignore();
      do
      {
         cout << "Enter data. Press enter when finished with each input: ";
         getline(cin, data);
         if(data != "done")
         {
            recordContent.push_back(data);
            cout << recordContent[index] << endl;
            index++;
         }
         cin.ignore();
      }
      while(data != "done");
   
      cout << endl;
      return;
   }
}

void createData(vector <string> & recordContent, string & fileName)
{
   string newData; //for when a new file is made
   int index = 0;

   recordContent.clear(); //empty whatever is in here so we don't mix data

/*
   cout << "Please enter new data.\n";
   cin.ignore();
   getline(cin, newData);
*/

   cout << "*NOTE: You can only file with 100 things at a time. If you want to enter\n multiple pieces of information into the file, "
   << "type one space and then a \'!\' right after.\n Otherwise, please enter \'done\' when finished updating.\n";
   cin.ignore();
   do
   {  
      cout << "Enter data: ";
      getline(cin, newData);
      if(newData != "done")
      {  
         try
         {
            recordContent.push_back(newData);
         }
         catch(std::bad_alloc)
         {
            cout << "Cannot push_back new data" << endl;
         }
         cout << recordContent[index] << endl;
         index++;
         cin.ignore();
      }
      else
      {
         cin.ignore();
      }
   }
   while(newData != "done");

   grabInFile(fileName);
   cout << endl;
   saveData(fileName, recordContent);
}

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
