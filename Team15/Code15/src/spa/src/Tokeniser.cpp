#include "Tokeniser.h"

using namespace std;
using namespace Tokens;


//map<int, int> generateFollowsRS(map<int, int> nesting_level);
//map<int, set<int>> generateFollowsStarRS(map<int, int> nesting_level);
//map<string, vector<vector<string>>> generateAssignmentRS(map<int, vector<string>> parsed);
//vector<string> convertToPostfix(vector<string> tokens, int startIndex);

set<string> procedures;
vector<string> constants;
set<string> variables;
map<Tokens::Keyword, vector<int>> statements;

bool Tokeniser::emptyToken(std::string token) {
    if(token == "" || token == " ") {
        return true;
    } else {
        return false;
    }
}

std::vector<std::string> Tokeniser::pushToken(std::vector<std::string> tokens, std::string token) {
    if(!emptyToken(token)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool Tokeniser::isNumeric(const std::string token) {
    for (char c : token) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool Tokeniser::isStatement(std::string token) {
    return token == "read"
        || token == "print"
        || token == "call"
        || token == "while"
        || token == "if"
        || token == "assign";
}

Tokens::Keyword Tokeniser::getStatementType(std::string token) {
    return tokenMap.getTokenByString(token);
}

void Tokeniser::extract(std::vector<std::string> tokens, int lineNumber) {
    for(int i = 0; i < tokens.size(); ++i) {
        if(tokens[i] == "procedure") {
            procedures.insert(tokens[i+1]);
        } else if (isStatement(tokens[i])) {
            Tokens::Keyword statementType = getStatementType(tokens[i]);
            statements[statementType].push_back(lineNumber);
        } else if (isNumeric(tokens[i])) {
            constants.push_back(tokens[i]);
        } else if (i > 0 && tokens[i-1] == "=") {
            variables.insert(tokens[i]);
        }
    }
}

std::vector<std::string> Tokeniser::tokenise(std::string line, int lineNumber) {
    vector<std::string> tokens;
    string currentToken = "";
    for(char c : line) {
        string s(1, c);
        if(tokenMap.findToken(s)) {
            tokens = pushToken(tokens, currentToken);
            tokens = pushToken(tokens, s);
            currentToken = "";
        } else if (c == ' ') {
            tokens = pushToken(tokens, currentToken);
            currentToken = "";
        } else {
            currentToken += c;
        }
    }
    extract(tokens, lineNumber);
    return tokens;
}

map<int, vector<string>> Tokeniser::processFile(std::ifstream &file) {
    map<int, vector<string>> parsed;
    string curr_line;
    // Parse the SIMPLE program line by line
    int line_number;
    line_number = 1;
    while (getline(file, curr_line)) {
        parsed[line_number] = tokenise(curr_line, line_number);
        line_number++;
    }
    return parsed;
}

map<int, int> Tokeniser::generateNestingLevel(map<int, vector<string>> parsed) {
    map<int, int> nesting_level;
    int curr_level;
    curr_level = 0;
    for (auto it = parsed.begin(); it != parsed.end(); ++it) {
        int line_number = it->first;
        vector<string> tokens = it->second;
        int final_nesting_level = 0;
        for (int i = 0; i < tokens.size(); i++) {
            string token = tokens[i];
            if (token == "procedure") {
                final_nesting_level = 0;
                curr_level = 0;
            } else if (token == ";") {
                final_nesting_level = curr_level;
            } else if (token == "}" && i == 0) { // starts with opening brace
                curr_level--;
                final_nesting_level = curr_level;
            } else if (token == "{") {
                final_nesting_level = curr_level;
                curr_level++;
            } else if (token == "}") {
                curr_level--;
            }
        }
        if (tokens.size() == 0) {
            final_nesting_level = -1;
        }
        nesting_level[line_number] = final_nesting_level;

    }
    for (const auto &pair : nesting_level) {
        std::cout << "Line number: " << pair.first << ", Nesting level: " << pair.second << std::endl;
    }
    cout << endl;
    return nesting_level;
}

map<int, int> Tokeniser::generateFollowsRS(map<int, int> nesting_level) {
    map<int, int> follows;
    auto second_last = prev(nesting_level.end());
    for (auto it = nesting_level.begin(); it != second_last; ++it) {
        int line_number = it->first;
        int first_nesting_level = it->second;
        int second_nesting_level = next(it)->second;
        if (second_nesting_level == -1) { // new procedure
            break;
        }
        bool is_same_nesting_level = first_nesting_level == second_nesting_level;
        if (is_same_nesting_level) { // Line right after is same indentation -> follows
            follows[line_number] = line_number + 1;
        }
    }
    // print out follows relationship
    for (const auto& [key, value] : follows) {
        cout << "Follows relationship" << endl;
        cout << key << ": " << value << endl;
    }

    return follows;
}

map<int, set<int>> Tokeniser::generateFollowsStarRS(map<int, int> nesting_level) {
    map<int, set<int>> follows_star;
    for (auto outer_it = nesting_level.begin(); outer_it != nesting_level.end(); ++outer_it) {
        for (auto inner_it = next(outer_it); inner_it != nesting_level.end(); ++inner_it) {
            int first_line_number = outer_it->first;
            int second_line_number = inner_it->first;
            int first_nesting_level = outer_it->second;
            int second_nesting_level = inner_it->second;
            if (second_nesting_level == -1) { // new procedure
                break;
            }
            bool is_same_nesting_level = first_nesting_level == second_nesting_level;
            if (!is_same_nesting_level) {
                continue;
            }
            if (follows_star[first_line_number].empty()) {
                set<int> new_set;
                follows_star[first_line_number] = new_set;
            }
            follows_star[first_line_number].insert(second_line_number);
        }
    }

    // print out follows* relationship
    cout << "Follows* relationship" << endl;
    for (const auto& [key, value] : follows_star) {
        cout << key << ": { ";
        for (const auto& element : value) {
            cout << element << " ";
        }
        cout << "}" << endl;
    }
    return follows_star;
}

int Tokeniser::precedence(string c) {
    if (c == "-" || c == "+") {
        return 1;
    } else if (c == "*" || c == "/" || c == "%") {
        return 2;
    } else if (c == "^") {
        return 3;
    }
    return -1;
}

bool Tokeniser::isOperator(string c) {
    return precedence(c) > 0;
}

bool Tokeniser::isNumber(string num) {
    try {
        stod(num);
        return true;
    } catch (const invalid_argument &e) {
        return false;
    }
}


vector<string> Tokeniser::convertToPostfix(vector<string> tokens, int startIndex) {
    vector<string> result;
    stack<string> s;
    for (int i = startIndex; i < tokens.size(); i++) {
        string token = tokens[i];
        if (variables.count(token)) {
            result.push_back(token);
        } else if (isOperator(tokens[i])) {
            while (!s.empty() && precedence(s.top()) >= precedence(token)) {
                result.push_back(s.top());
                s.pop();
            }
            s.push(tokens[i]);
        } else if (isNumber(token)) {
            result.push_back(token);
        }
    }
    while (!s.empty()) {
        result.push_back(s.top());
        s.pop();
    }
    return result;
}

map<string, vector<vector<string>>> Tokeniser::generateAssignmentRS(map<int, vector<string>> parsed) {
    map<string, vector<vector<string>>> assigns;
    for (auto it = parsed.begin(); it != parsed.end(); ++it) {
        vector<string> tokens = it->second;
        string prev;
        string LHS;
        vector<string> RHS;
        int startIndexForRHS;
        bool hasRHS = false;
        for (int i = 0; i < tokens.size(); i++) {
            string token = tokens[i];
            if (token == "=") {
                LHS = prev;
                hasRHS = true;
                startIndexForRHS = i;
                break;
            }
            prev = token;
        }
        if (!hasRHS) {
            continue;
        }
        RHS = convertToPostfix(tokens, startIndexForRHS);
        if (assigns.count(LHS)) {
            assigns[LHS].push_back(RHS);
        } else {
            vector<vector<string>> new_vector;
            new_vector.push_back(RHS);
            assigns.insert(make_pair(LHS, new_vector));
        }
    }
    cout << "Assigns relationship" << endl;
    for (auto it = assigns.begin(); it != assigns.end(); ++it) {
        cout << it->first << ": [";
        for (auto match : it->second) {
            cout << "[";
            for (auto s: match) {
                cout << s << ", ";
            }
            cout << "]" << endl;
        }
        cout << "]" << endl;
    }
    return assigns;
}

void Tokeniser::driver() {
    string filename = "Team15/Tests15/Sample_source.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
    }

    map<int, vector<string>> parsed = processFile(file);
    map<int, int> nesting_level = generateNestingLevel(parsed);
    map<int, int> follows = generateFollowsRS(nesting_level);
    map<int, set<int>> follows_star = generateFollowsStarRS(nesting_level);
    map<string, vector<vector<string>>> assigns = generateAssignmentRS(parsed);

    file.close();
}

int Tokeniser::main() {
    driver();
}
