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
   std::string temp_record_name;

   //Record Object. Currently, we are only going to handle one record at a time.
   //Eventually, I want to make it so X number of records can handled at a time.
   Record record;

   //BEGINNING OF IMPLEMENTATION

   do {
       std::cout << "What would you like to do?\nN - Create new document." 
                 << "--PLEASE!!! Make sure to save your work before create a new record!--\n"
                 << "L - Load a Record.\nE - Edit Record.\nR - Review Record.\nS - Save Record\nQ - Exit." 
                 << std::endl << "\n>";
       std::cin >> choice;
       std::cout << std::endl;

      switch(choice) {
         case 'N':
         case 'n':
            std::cout << "Please enter the name of new record to create: ";
            std::cin >> temp_record_name;
            record.setRecordName(temp_record_name);
            record.createRecord();
            break;
         case 'L':
         case 'l':
            try 
            {
                std::cout << "Please enter the name of the record to import: ";
                std::cin >> temp_record_name;
                record.setRecordName(temp_record_name);
                record.readInRecord();
            }
            catch (const char* e)
            {
                std::cout << e << std::endl;
            }
            break;
         case 'E':
         case 'e':
            record.editRecord();
            break;
         case 'R':
         case 'r':
            record.reviewRecord();
            break;
         case 'S':
         case 's':
            std::cout << "Save record under current name? Y/N: ";
            std::cin >> choice;
            if (choice == 'Y' || choice == 'y')
                record.saveRecord();
            else if (choice == 'N' || choice == 'n')
            {
                std::cout << "Please type in the new name of the file to save to: ";
                std::cin >> temp_record_name;
                record.setRecordName(temp_record_name);
            }
            else
                std::cout << "Invalid character entered when saving record. Please try again." << std::endl;
            break;
         case 'Q':
         case 'q':
            return 0;
      } 
   }
   while(choice);
}
