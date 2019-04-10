#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

//a comment to test git

void grabInFile(string & fileName) {
   cout << "Enter record name: ";
   cin >> fileName;

}

void readInFile(string fileName, vector <string> &recordContent) throw (const char*) {
   ifstream fin;
   fin.open(fileName);

   if (fin.fail()) {
      throw ("Error: Cannot read file.");
   }

   if (!recordContent.empty()) {
      recordContent.clear();
   }

   string content;

   int index = 0;
   while(fin >> content) {
      recordContent.push_back(content);
      cout << recordContent[index] << endl;
      index++;
   }

   fin.close();
}

void updateData(vector <string> &recordContent) {
   string data;

   cout << "Enter data: ";
   cin >> data;

   recordContent.push_back(data);
}

void saveData(string fileName, vector <string> recordContent) throw (const char*) {
   ofstream fout;
   fout.open(fileName);

   if (fout.fail()) {
      throw ("Error: Cannot save file.");
   }

   int counter = 0;
   for (vector <string>::iterator it = recordContent.begin(); it != recordContent.end(); it++, counter++) { 
      fout << recordContent[counter] << " ";
   }

   fout.close();
}

int main() {

   //DATA-CONTENT VARIABLES
   string fileName = "\0";
   vector <string> recordContent;
   string newData; //for when a new file is made


   //INPUT VARIABLES
   char choice;

   //BEGINNING OF IMPLEMENTATION

   do {
      cout << "What would you like to do?\n N - Create new document.\n L - Load The Data.\n U - Update Finances.\n R - Review Data.\n S - Save The Data\n Q - Exit Program" 
      << endl << "\n>";
      cin >> choice;

      switch(choice) {
         case 'N':
         case 'n':
            cout << "Please enter new data.\n";
            cin.ignore();
            getline(cin, newData);
            cin.ignore();
            recordContent.clear();
            try
            {
               recordContent.push_back(newData);
            }
            catch(std::bad_alloc)
            {
               cout << "Cannot push_back new data" << endl;
            }
            cout << "What is the name of new file?\n";
            cin >> fileName;
            saveData(fileName, recordContent);
            break;
         case 'L':
         case 'l':
            try {
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
            for (vector <string>::iterator it = recordContent.begin(); it != recordContent.end(); it++) {
               cout << *it << endl;
            }
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
