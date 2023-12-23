#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>
#include <sstream>

class Record
{
    private:
        std::vector<std::string> record_item;
        std::string record_name;
        std::stringstream ss_file_content;
        std::string new_record_content;
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
