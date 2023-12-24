#include "record.h"
#include <fstream>
#include <iostream>
#include <vector>

/*************************************************************************
* This method is used to read in the text file. The ! in the actual text
* file is used as a sort of key for the program to know where the end of one
* data entry is.
*************************************************************************/
void Record::readInRecord() throw (const char*)
{
    std::string fileContent;  //This variable is for the data that is being read in exclusively
    std::string contentToPush = "";  //This variable is going to be the on eused as a medium for pushing back onto the vector
//    int indexForContent = 0;
    int index_for_record = 0;
    record_body temp_body;

    std::ifstream fin;
    fin.open(this->record_name);

    if (fin.fail())
        throw ("Error: Cannot read file.");

    if (!record_item.empty())
      record_item.clear();

//   std::getline(fin, this->ss_file_content);
    this->ss_file_content << fin.rdbuf();
    while(fin[index_for_record] != '\0')
    {
        if(fin[index_for_record] != '\n')
            ss_file_content << fin[index_for_record];
        else
            std::cout << "A newline was encountered.\n";
    }

//   while(ss_file_content[indexForContent] != '\0')
//   {
//      if(ss_file_content[indexForContent] != '!')
//      {
//         contentToPush += ss_file_content[indexForContent];
//         indexForContent++;
//      }
//      else if(ss_file_content[indexForContent] == '!')
//      {
//         this->record_item.push_back(contentToPush);
//         contentToPush.clear();
//         indexForRecord++;
//         indexForContent++;
//      }
//   }
   std::cout << "Contents of stringstream: " << ss_file_content.str() << std::endl;
//   this->ss_file_content >> this->record_item[this->record_item.size()-1].item_type 
//                        >> this->record_item[this->record_item.size()-1].item_name
//                        >> this->record_item[this->record_item.size()-1].item_price
//                        >> this->record_item[this->record_item.size()-1].item_date;
   this->ss_file_content >> temp_body.item_type 
                        >> temp_body.item_price
                        >> temp_body.item_name
                        >> temp_body.item_date;

//   fin >> this->record_item[this->record_item.size()-1].item_type 
//       >> this->record_item[this->record_item.size()-1].item_name
//       >> this->record_item[this->record_item.size()-1].item_price
//       >> this->record_item[this->record_item.size()-1].item_date;
   this->record_item.push_back(temp_body);

   std::cout << "The contents of the read in are as follows: \n\tItem Type: " << this->record_item[this->record_item.size()-1].item_type
             << "\n\t Item Price: " << this->record_item[this->record_item.size()-1].item_price
             << "\n\t Item Name: " << this->record_item[this->record_item.size()-1].item_name
             << "\n\t Item Date: " << this->record_item[this->record_item.size()-1].item_date
             << std::endl;

   fin.close();
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
///*************************************************************************
//* This method is used for reviewing the contents of the given record object
//* that the method was invoked from.
//*************************************************************************/
//void Record::reviewRecord()
//{
//    this->review_counter = 0;
//    for (std::vector<std::string>::iterator it = this->record_item.begin(); it != record_item.end(); it++)
//    { 
//        std::cout << review_counter << ". " << *it << std::endl;
//        review_counter++;
//    } 
//    std::cout << std::endl;
//}


/*************************************************************************
* The following setters and getters are for the member variables of the
* record object you are invoking them for.
*************************************************************************/
void Record::setRecordName(std::string record_name) { this->record_name = record_name; }
std::string Record::getRecordName() { return this->record_name; }
void Record::setSSFileContent() { }
void Record::getSSFileContent() { }
void Record::setNewRecord() { }
void Record::getNewRecord() { }

