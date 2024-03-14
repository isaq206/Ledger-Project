#include "record.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

/*************************************************************************
* This method is used to read in the text file. The ! in the actual text
* file is used as a sort of key for the program to know where the end of one
* data entry is.
*************************************************************************/
void Record::readInRecord() throw (const char*)
{
	std::string path(std::getenv("HOME"));
    std::ifstream fin;
    std::stringstream temp_ss;
    record_body temp_body;

    record_item.clear();

    if (fin.is_open())
        fin.close();

    fin.open(path+"/Documents/Ledger_Records/"+this->record_name);

    if (fin.fail())
        throw ("Error: Cannot read file.");

    temp_ss << fin.rdbuf();

    while(temp_ss >> temp_body.item_date 
                  >> temp_body.item_type
                  >> temp_body.item_name
                  >> temp_body.item_price)
    {
        std::getline(temp_ss, temp_body.item_notes);
		temp_body.item_notes.erase(0, 1);
        this->record_item.push_back(temp_body);
    }

    reviewRecord();
}

/*************************************************************************
* This method is used to save the data contained in the local vector structure.
* text file. The ! in the actual text file is used as a sort of key for the
* program to know where the end of one data entry is.
*************************************************************************/
void Record::saveRecord() throw (const char*)
{
	std::string path(std::getenv("HOME"));
    std::ofstream fout;
    	
	try
	{
	    fout.open(path+"/Documents/Ledger_Records/"+this->record_name);
		if(fout.fail())
			throw ("Error: Cannot save file.");
	}
	catch(const char* e)
	{
		std::cout << "ERROR CAUGHT: " << e << std::endl;
	}

    int counter = 0;
    for (std::vector<record_body>::iterator it = this->record_item.begin(); it != this->record_item.end(); it++, counter++)
    {
        fout << this->record_item[counter].item_date << " "
             << this->record_item[counter].item_type << " " 
             << this->record_item[counter].item_name << " "
             << this->record_item[counter].item_price << " "
             << this->record_item[counter].item_notes << "\n";
    }

    fout.close();
   
    std::cout << "---Record saved---" << std::endl;
}

/*************************************************************************
* This method is used to update the contents of the text file once it has
* been loaded in or a new document has been created. The user will not need
* to type or even worry/know about the ! in the source file. The program
* takes care of that.
*************************************************************************/
void Record::editRecord()
{
    bool loop = true;
    char repeat;
//    record_body temp_body = {"\0","\0","\0",0,"\0"};
    char choice[1];
    int ichoice;
    std::string sbuffer = "\0";

    reviewRecord();

    std::cout << "Which item in record do you want to edit? (1,2,3,...). Enter \'Y\' to cancel." << std::endl;

    std::cin >> choice;
    std::cout << std::endl;
    std::cin.ignore();


	if(choice == "Y" || choice == "y")
	{
		return;
	}
	else if(isdigit(choice[0]))
    {
        ichoice = std::atoi(choice) - 1;
        std::cout << "The value of ichoice right now: " << ichoice << std::endl;
		std::cout << "Please enter the information that you want updated wit for each input. Press \'enter\' if you wish to skip that field.\n";
        
		while(!(choice[0] == 'Y' || choice[0] == 'y'))
		{
            std::cout << "Date mm/dd/yyyy (Current: " << this->record_item[ichoice].item_date << "): ";
            std::getline(std::cin, sbuffer, '\n');
            if(!sbuffer.empty())
            {
                this->record_item[ichoice].item_date = sbuffer;
            }

            std::cout << "Type (Current: " << this->record_item[ichoice].item_type << "): ";
            std::getline(std::cin, sbuffer, '\n');
            if(!sbuffer.empty())
            {
                this->record_item[ichoice].item_type = sbuffer;
            }

            std::cout << "Name (Current: " << this->record_item[ichoice].item_name << "): ";
            std::getline(std::cin, sbuffer, '\n');
            if(!sbuffer.empty())
            {
                this->record_item[ichoice].item_name = sbuffer;
            }

            std::cout << "Additional Notes (Current: " << this->record_item[ichoice].item_notes << "): ";
            std::getline(std::cin, sbuffer, '\n');
            if(!sbuffer.empty())
            {
                this->record_item[ichoice].item_notes = sbuffer;
            }

            std::cout << "Price (Current: " << this->record_item[ichoice].item_price << "): ";
            std::getline(std::cin, sbuffer, '\n');
            if(!sbuffer.empty())
            {
                this->record_item[ichoice].item_price = atof(sbuffer.c_str());
            }


            reviewRecord();
            std::cout << "Are you finished editing this record? (Y/N)";
            std::cin.get(choice[0]);
            if(choice[0] == 'N' || choice[0] == 'n')
            {
                std::cin.ignore();
                std::cout << "Please enter the item number that you wish to edit next: ";
                std::cin >> ichoice;
                ichoice -= 1;
                std::cin.ignore();
            }
            else
            {
                choice[0] = 'Y';
            }
		}
	}
    std::cout << std::endl;
}

/*************************************************************************
* This method is used to create a new text file. The ! in the actual text
* file is used as a sort of key for the program to know where the end of one
* data entry is.
*************************************************************************/
void Record::createRecord()
{
    record_body new_data; //for when a new file is made
    int index = 0;
    char finished_creating = '\0';

    this->record_item.clear(); //empty whatever is in here so we don't mix data

    std::cout << "*NOTE: Press enter after each item to then enter next.\n";
    do
    {
        std::cout << "Enter each data item. Type \'done\' to finish." << std::endl;
        std::cout << "Date(mm/dd/yyyy): ";
        std::cin >> new_data.item_date;

        std::cout << "Type(Food, Grocery, Bill, Tithing, Hobby/Entertainment): ";
        std::cin >> new_data.item_type;

        std::cout << "Name: ";
        std::cin >> new_data.item_name;

        std::cout << "Price (In USD): ";
        std::cin >> new_data.item_price;

        std::cin.ignore();

        std::cout << "Additional Notes: ";
        std::getline(std::cin, new_data.item_notes);
        try
        {
            this->record_item.push_back(new_data);
        }
        catch(std::bad_alloc)
        {
            std::cout << "Cannot push_back new data" << std::endl;
        }
        index++;

        std::cin.ignore();
        std::cout << "Are you done adding items to record? Y/N" << std::endl;
        std::cin >> finished_creating;

        std::cin.ignore();
    }
    while(toupper(finished_creating) == 'N');

    std::cout << std::endl << "You have added " << index << " new items to this new record." << std::endl;

    //I think I want to comment out the function below
    //because I don't know if I want to save this record or not.
    //Best too leave it up to the user.
//    this->saveRecord();
}

/*************************************************************************
* This method is used for reviewing the contents of the given record object
* that the method was invoked from.
*************************************************************************/
void Record::reviewRecord()
{
    this->review_counter = 0;
    std::cout << "========================================================================================================================================================\n"
              << "|" << std::setw(11) << "Date" << std::setw(7) << "|" << std::setw(13) << "Type" << std::setw(9) << "|" 
              << std::setw(11) << "Name" << std::setw(7) << "|" << std::setw(12) << "Price" << std::setw(7) << "|" 
              << std::setw(32) << "Additional Notes" << std::setw(17) << "\n";

    for (std::vector<record_body>::iterator it = this->record_item.begin(); it != this->record_item.end(); it++)
    { 
        std::cout << "|" << std::setw(17) << (*it).item_date
            << "|" << std::setw(21) << (*it).item_type
            << "|" << std::setw(17) << (*it).item_name
            << "|" << std::setw(18) << std::fixed << std::setprecision(2) << (*it).item_price
            << "|" << (*it).item_notes
            //<< "| " << std::setw(69)/*Nice*/ << std::left << (*it).item_notes
            << std::endl;
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
void Record::setNewRecord() { }
void Record::getNewRecord() { }
