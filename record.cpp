#include "record.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

/*************************************************************************
* This method is used to read in the text file. The ! in the actual text
* file is used as a sort of key for the program to know where the end of one
* data entry is.
*************************************************************************/
void Record::readInRecord() throw (const char*)
{
    record_body temp_body;

    std::ifstream fin;
    fin.open(this->record_name);

    if (fin.fail())
        throw ("Error: Cannot read file.");

//    if (!record_item.empty())
//      record_item.clear();

    this->ss_file_content << fin.rdbuf();
    
    fin.close();

    while(this->ss_file_content >> temp_body.item_date 
                                >> temp_body.item_type
                                >> temp_body.item_name
                                >> temp_body.item_price)
    {
        this->record_item.push_back(temp_body);
    }
    reviewRecord();
}

///*************************************************************************
//* This method is used to save the data contained in the local vector structure.
//* text file. The ! in the actual text file is used as a sort of key for the
//* program to know where the end of one data entry is.
//*************************************************************************/
//void Record::saveRecord() throw (const char*)
//{
//   std::ofstream fout;
//   fout.open(this->record_name);
//
//   if (fout.fail()) {
//      throw ("Error: Cannot save file.");
//   }
//
//   int counter = 0;
//   for (std::vector<std::string>::iterator it = this->record_item.begin(); it != this->record_item.end(); it++, counter++)
//   {
//       fout << this->record_item[counter] << " !";
//   }
//
//   fout.close();
//}
//
///*************************************************************************
//* This method is used to update the contents of the text file once it has
//* been loaded in or a new document has been created. The user will not need
//* to type or even worry/know about the ! in the source file. The program
//* takes care of that.
//*************************************************************************/
//void Record::updateRecord()
//{
//   std::string data;
//   int index = 0;
//   char choice[2] = "\0";
//
//   std::cin.ignore();
//   std::cout << "Where do you want to start updating? (1, 2, 3,...) Based on \"Review Data\" option in main menu. \nYou can type \"E or e\""
//        << "if you want to append at end of file. Type \"B or b\" if you want to go back to main menu.\n\n" << ">";
//   std::cin >> choice;
//   std::cout << std::endl;
//
//
//	if(choice == "B" || choice == "b")
//	{
//		return;
//	}
//
//	else if(choice == "E" || choice == "e")
//	{
//
////This line was used for debugging and figuring out which if the logic will make it go to.
////cout << "This means it is in the \"Update at the end\"\n";
//
//		std::cout << "*When finished, please enter \'done\' when finished updating.\n";
//		std::cout << std::endl;
//	    std::cin.ignore();
//		do
//		{
//			std::cout << "Enter data. Press enter when finished with each input: ";
//			std::getline(std::cin, data);
//			if(data != "done")
//			{
//				this->record_item.push_back(data);
//				std::cout << this->record_item[index] << std::endl;
//				index++;
//			}
//			std::cin.ignore();
//		}
//		while(data != "done");
//
//		std::cout << std::endl;
//		return;
//	}
//
//	else
//	{
//		std::cout << "When finished, please enter \'done\' when finished updating.\n";
//		std::cin.ignore();
//		do
//		{
//			std::cout << "Enter data. Press enter when finished with each input. Type \'done\' when finished.: ";
//			std::getline(std::cin, data);
//			if(data != "done")
//			{
//				int count = this->record_item.size();
//				int designation;
//				designation = atoi(choice);
//
//				this->record_item.push_back(this->record_item[count-1]);
//
//
//				for(std::vector<std::string>::reverse_iterator it = this->record_item.rbegin(); count > designation; ++it)
//				{
//					this->record_item[count] = this->record_item[count-1];
//					count--;
//				}
//				this->record_item[count] = data;
//			}
////         cin.ignore();
//		}
//		while(data != "done");
//
//		std::cout << std::endl;
//		return;
//	}
//}
//
///*************************************************************************
//* This method is used to create a new text file. The ! in the actual text
//* file is used as a sort of key for the program to know where the end of one
//* data entry is.
//*************************************************************************/
//void Record::createRecord()
//{
//   std::string newData; //for when a new file is made
//   int index = 0;
//
//   this->record_item.clear(); //empty whatever is in here so we don't mix data
//
//   std::cout << "*NOTE: Press enter after each entry to then enter next entry. Type \'done\' when finished with document.\n";
//   std::cin.ignore();
//   do
//   {
//       std::cout << "Enter data. Type \'done\' to finish: ";
//       std::getline(std::cin, newData);
//      if(newData != "done")
//      {
//         try
//         {
//            this->record_item.push_back(newData);
//         }
//         catch(std::bad_alloc)
//         {
//             std::cout << "Cannot push_back new data" << std::endl;
//         }
//         std::cout << this->record_item[index] << std::endl;
//         index++;
////         cin.ignore("\n");
//      }
////      else
////      {
////         cin.ignore("\n");
////      }
//   }
//   while(newData != "done");
//
////   this->readInRecord();
//   std::cout << std::endl;
//   this->saveRecord();
//}
//
/*************************************************************************
* This method is used for reviewing the contents of the given record object
* that the method was invoked from.
*************************************************************************/
void Record::reviewRecord()
{
    this->review_counter = 0;
    std::cout << "========================================================================================================================================================\n"
              << "|" << std::setw(11) << "Date" << std::setw(7) << "|" << std::setw(11) << "Type" << std::setw(7) << "|" 
              << std::setw(11) << "Name" << std::setw(7) << "|" << std::setw(12) << "Price" << std::setw(7) << "|\n";

    for (std::vector<record_body>::iterator it = this->record_item.begin(); it != this->record_item.end(); it++)
    { 
        std::cout << "|" << std::setw(17) << (*it).item_date
            << "|" << std::setw(17) << (*it).item_type
            << "|" << std::setw(17) << (*it).item_name
            << "|" << std::setw(17) << std::fixed << std::setprecision(2) << (*it).item_price
            << "|" << std::endl;
        review_counter++;
    } 
    std::cout << "========================================================================================================================================================\n";
    std::cout << std::endl;
}


/*************************************************************************
* The following setters and getters are for the member variables of the
* record object you are invoking them for.
*************************************************************************/
void Record::setRecordName(std::string record_name) { this->record_name = record_name; }
std::string Record::getRecordName() { return this->record_name; }
void Record::setSSFileContent() { }
std::stringstream Record::getSSFileContent() { }
void Record::setNewRecord() { }
void Record::getNewRecord() { }

