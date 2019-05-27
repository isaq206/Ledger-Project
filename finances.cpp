#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;
/*************************************************************************
* This method is used for grabbing the file name.
*************************************************************************/
void grabInFile(string & fileName) 
{
   cout << "Enter record name: ";
   cin >> fileName;
   cout << endl;
}

/*************************************************************************
* This method is used to read in the text file. The ! in the actual text
* file is used as a sort of key for the program to know where the end of one 
* data entry is.
*************************************************************************/
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
/*************************************************************************
* This method is used to save the data contained in the local vector structure.
* text file. The ! in the actual text file is used as a sort of key for the 
* program to know where the end of one data entry is.
*************************************************************************/
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

/*************************************************************************
* This method is used to update the contents of the text file once it has
* been loaded in or a new document has been created. The user will not need
* to type or even worry/know about the ! in the source file. The program
* takes care of that.
*************************************************************************/
void updateData(vector <string> &recordContent) 
{
   cin.ignore();
   string choice = "\0";
   cout << "Where do you want to start updating? (1, 2, 3,...) Based on \"Review Data\" option in main menu. \nYou can type \"end\""
        << "if you want to update at end of file. Type \"Back\" if you want to go back to main menu.\n\n" << ">";
   cin >> choice;
   cout << endl;

   if(choice == "Back" || choice == "back")
   {   
      return;
   }

   else if(choice == "end" || choice == "End")
   {
      string data;
      int index = 0;

//This line was used for debugging and figuring out which if the logic will make it go to.
//cout << "This means it is in the \"Update at the end\"\n";

      cout << "*When finished, please enter \'done\' when finished updating.\n";
      cout << endl;
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

   else
   {
      string data;
      int index = 0;

//This line was used for debugging and figuring out which if the logic will make it go to.
//cout << "This means it is in the \"Update somewhere besides end\"\n";

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
}

/*************************************************************************
* This method is used to create a new text file. The ! in the actual text
* file is used as a sort of key for the program to know where the end of one 
* data entry is.
*************************************************************************/
void createData(vector <string> & recordContent, string & fileName)
{
   string newData; //for when a new file is made
   int index = 0;

   recordContent.clear(); //empty whatever is in here so we don't mix data

   cout << "*NOTE: Press enter after each entry to then enter next entry. Type \'done\' when finished with document.\n";
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
