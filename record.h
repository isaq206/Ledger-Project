#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>

namespace Record
{
	class Record
	{
        private:
            std::vector<std::string>
            std::string record_name;
            std::stringstream ss_file_content;
            std::string new_record_content;

            int io_error;

        public:
            void readInFile(std::string fileName, std::vector<std::string> &recordContent) throw (const char*);
            void saveData(std::string fileName, std::vector<std::string> recordContent) throw (const char*);
            void updateData(std::vector<std::string> &recordContent);
            void createData(std::vector<std::string> & recordContent, std::string & fileName);
	}
}
