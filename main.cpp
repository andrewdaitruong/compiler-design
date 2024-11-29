#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

void processFile(const string& inputFilename, const string& outputFilename) {
    
    //File opening/handling
    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename, ios::trunc);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file(s)." << endl;
        return;
    }

    string line;
    bool is_comment = false; //checks if comment
    int lineNumber = 1;

    //Looks for comments... STILL NEED TO COMPLETE. Line number is just a place holder
    while (getline(inputFile, line)) {
        stringstream processed_line;
        size_t i = 0;
        
        while (i < line.size()) {
            if (!is_comment) {
                if (line[i] == '(' && line[i + 1] == '*' && i + 1 < line.size()) {
                    is_comment = true; //is_comment = true until *)
                    i += 2;
                }
                else {
                    if (!isspace(line[i]) || (processed_line.tellp() > 0 && !isspace(processed_line.str().back()))) {
                        processed_line << line[i];
                    }
                    i++;
                }
            }
            else { 
                if (line[i] == '*' && line [i + 1] == ')' && i + 1 < line.size()) {
                    is_comment = false;
                    i += 2;
                }
                else {
                    i++;
                }
            }
        }

        string result = processed_line.str();
        result.erase(0, result.find_first_not_of(' '));
        result.erase(result.find_last_not_of(' ') + 1);

        if (!result.empty() && !is_comment) {
            outputFile << setw(4) << lineNumber << ". " << result << endl;  // Line number formatting
            lineNumber++;
        }   
    }

    //Closing files
    inputFile.close();
    outputFile.close();
}

int main() {
    processFile("final.txt", "final24.txt");
    cout << "Processing complete. Check final24.txt for results." << endl;
    return 0;
}