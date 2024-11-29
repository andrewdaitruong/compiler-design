// If text files are not suppose to have numbers, remove anything line number related.

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

    while (getline(inputFile, line)) {
        // This strips the number off of the input file
        size_t pos = line.find_first_not_of(" \t");
        if (pos != string::npos && isdigit(line[pos])) {
            pos = line.find_first_of(" \t", pos);  // Skip the number and any spaces after it
            line = (pos != string::npos) ? line.substr(pos) : "";
        }

        stringstream processed_line;
        size_t i = 0;
        
        while (i < line.size()) {
            if (!is_comment) {
                // Looks for the characters that make up a comment
                if (line[i] == '(' && line[i + 1] == '*' && i + 1 < line.size()) {
                    is_comment = true; //true until it finds *)
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

        // Can remove use "if ( !results.empty() || is_comment ) and whatever is in the else if no line numbers are needed."
        if (result.empty() || is_comment) {
            continue;
        }
        else {
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