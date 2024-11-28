#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void processFile(const string& inputFilename, const string& outputFilename) {
    
    //File opening/handling
    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file(s)." << endl;
        return;
    }

    string line;
    bool is_comment = false; //checks if comment
    int lineNumber = 1;

    //Looks for comments... STILL NEED TO COMPLETE. Line number is just a place holder
    for (int i = 0; i < line[lineNumber]; i++) {
        if (line[i] == '(' && line[i + 1] == '*') {
            is_comment = true; //is_comment = true until *)
            continue;
        }
    }
    for (int i = 0; i < line[lineNumber]; i++) {
        if (line[i] == '*' && line [i + 1] == ')') {
            is_comment = false;
            break;
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