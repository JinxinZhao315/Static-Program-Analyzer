#include "Driver.h"

string mainDriver(int argc, char* argv[]) {
    // Enter source of SIMPLE code
    string filename = "Team15/Tests15/Sample_source.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return 0;
    }

    // Tokeniser process
    map<int, vector<string>> parsed = processFile(file);
    map<int, int> nesting_level = generateNestingLevel(parsed);
    map<int, int> follows = generateFollowsRS(nesting_level);
    map<int, set<int>> follows_star = generateFollowsStarRS(nesting_level);
    map<string, vector<vector<string>>> assigns = generateAssignmentRS(parsed);

    file.close();

    // TODO: add PKB calls

    // TODO: add PQL calls
    string queryStr = "stmt s; Select s such that Follows(_,_)";
    PQLDriver pqlDriver = PQLDriver();
    return "";
}