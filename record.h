#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>
#include <sstream>

class Record
{
    private:

        //This struct hold the fields of a record. Item type(corresponding enum exists),
        //item name, item description(?), price, and date.
        struct record_body
        {
            int item_type;
            int item_price;
            std::string item_name;
            //std::string item_description; //Don't know if I want this yet.
            std::string item_date;
        };

        std::vector<record_body> record_item;
        std::string record_name;
        std::stringstream ss_file_content;
        std::string new_record_content; //Used when updating a record with a new update or maybe entry.
        int review_counter;

        int io_error;

    public:
        //Object functions
        void readInRecord() throw (const char*);
        void saveRecord() throw (const char*);
        void updateRecord();
        void createRecord();
        void reviewRecord();

        //Object Setters and Getters
        void setRecordName(std::string);
        std::string getRecordName();
        void setSSFileContent();
        void getSSFileContent();
        void setNewRecord();
        void getNewRecord();
};

#endif
