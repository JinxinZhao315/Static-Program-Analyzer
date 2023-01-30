#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#include "PKB.h"

int Parse (string filename) {
    cout << "File path: " << filename << endl;

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return 0;
    }

    string line;
    // Parse the SIMPLE program line by line
    while (getline(file, line)) {
        cout << line << endl;

    }

    file.close();
    return 0;
}

// Only for testing purposes
int main(int argc, char* argv[]) {
    // For early testing this filepath is temporarily hard coded
    string filename = "Team15/Tests15/Sample_source.txt";
    Parse(filename);

    return 0;
}
