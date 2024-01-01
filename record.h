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
            std::string item_date;
            std::string item_type;
            std::string item_name;
            float item_price;
            std::string item_notes; //Don't know if I want this yet.
        };

        std::vector<record_body> record_item;
        std::string record_name;
        std::string new_record_content; //Used when updating a record with a new update or maybe entry.
        int review_counter;

        int io_error;

    public:
        //Object functions
        void readInRecord() throw (const char*);
        void saveRecord() throw (const char*);
        void editRecord();
        void createRecord();
        void reviewRecord();

        //Object Setters and Getters
        void setRecordName(std::string);
        std::string getRecordName();
        void setNewRecord();
        void getNewRecord();
};

#endif
