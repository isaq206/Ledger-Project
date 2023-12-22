#include "record.h"
#include <fstream>
#include <iostream>

/*************************************************************************
* This method is used to read in the text file. The ! in the actual text
* file is used as a sort of key for the program to know where the end of one
* data entry is.
*************************************************************************/
void readInFile(std::string fileName, std::vector<std::string> &recordContent) throw (const char*)
{
   std::ifstream fin;
   fin.open(fileName);

   if (fin.fail())
      throw ("Error: Cannot read file.");

   if (!recordContent.empty())
      recordContent.clear();

   std::string fileContent;  //This variable is for the data that is being read in exclusively
   std::string contentToPush = "";  //This variable is going to be the on eused as a medium for pushing back onto the vector
   int indexForContent = 0;
   int indexForRecord = 0;


   std::getline(fin, fileContent);

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
void saveData(std::string fileName, std::vector<std::string> recordContent) throw (const char*)
{
   std::ofstream fout;
   fout.open(fileName);

   if (fout.fail()) {
      throw ("Error: Cannot save file.");
   }

   int counter = 0;
   for (std::vector<std::string>::iterator it = recordContent.begin(); it != recordContent.end(); it++, counter++)
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
void updateData(std::vector<std::string> &recordContent)
{
   string data;
   int index = 0;
   string choice = "\0";

   std::cin.ignore();
   std::cout << "Where do you want to start updating? (1, 2, 3,...) Based on \"Review Data\" option in main menu. \nYou can type \"end\""
        << "if you want to update at end of file. Type \"Back\" if you want to go back to main menu.\n\n" << ">";
   std::cin >> choice;
   std::cout << endl;


	if(choice == "Back" || choice == "back")
	{
		return;
	}

	else if(choice == "end" || choice == "End")
	{

//This line was used for debugging and figuring out which if the logic will make it go to.
//cout << "This means it is in the \"Update at the end\"\n";

		std::cout << "*When finished, please enter \'done\' when finished updating.\n";
		std::cout << endl;
	    std::cin.ignore();
		do
		{
			std::cout << "Enter data. Press enter when finished with each input: ";
			std::getline(std::cin, data);
			if(data != "done")
			{
				recordContent.push_back(data);
				std::cout << recordContent[index] << endl;
				index++;
			}
			std::cin.ignore();
		}
		while(data != "done");

		std::cout << endl;
		return;
	}

	else
	{
//This line was used for debugging and figuring out which if the logic will make it go to.
//cout << "This means it is in the \"Update somewhere besides end\"\n";

		std::cout << "When finished, please enter \'done\' when finished updating.\n";
		std::cin.ignore();
		do
		{
			std::cout << "Enter data. Press enter when finished with each input: ";
			std::getline(std::cin, data);
			if(data != "done")
			{
				int count = recordContent.size();
				int designation;
				destination = (int)choice;

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

		std::cout << endl;
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
      cout << "Enter data. Type \'done\' to finish: ";
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
//         cin.ignore("\n");
      }
//      else
//      {
//         cin.ignore("\n");
//      }
   }
   while(newData != "done");

   grabInFile(fileName);
   cout << endl;
   saveData(fileName, recordContent);
}

