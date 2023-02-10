#include "../../include/extractor/Extractor.h"

set<string> Extractor::getVariables() {
    return variables;
}

vector<string> Extractor::getConstants() {
    return constants;
}

set<string> Extractor::getProcedures() {
    return procedures;
}

map<string, vector<int>> Extractor::getStatements() {
    return statements;
}

bool isProcedure(Line line) {
    return line.getType() == "procedure";
}

bool isStatement(Line line) {
    return line.getType() == "read"
        || line.getType() == "print"
        || line.getType() == "call"
        || line.getType() == "while"
        || line.getType() == "if"
        || line.getType() == "=";
}

string findProcedureName(vector<string> tokens) {
    for(auto token = begin(tokens); token != end(tokens); token++) {
        if(*token == "procedure") {
            return *(next(token));
        }
    }
    return "";
}

void Extractor::extractProcedure(Line line) {
    vector<string> tokens = line.getTokens();
    string procedureName = findProcedureName(tokens);
    set<string>* procedures = &this->procedures;
    procedures->insert(procedureName);
}


// FIX
bool isNumeric(string token) {
    return strspn( token.c_str(), "-.0123456789" ) == token.size();
}

void Extractor::extractConstants(Line line) {
    vector<string> tokens = line.getTokens();
    vector<string> *constants = &this->constants;
    for (auto token = begin(tokens); token != end(tokens); token++) {
        if (isNumeric(*token)) {
            constants->push_back(*token);
        }
    }
}

void insertLineNumber(map<string, vector<int>>* statements, string* type, int* lineNumber) {
    if(statements->count(*type) == 0) {
        vector<int>* lineNumbers = new vector<int>();
        lineNumbers->push_back(*lineNumber);
        pair statement = make_pair(*type, *lineNumber);
        statements->insert(statement);
    }
}


// FIX
void Extractor::extractStatement(Line line) {
    vector<string> tokens = line.getTokens();
    string type = line.getType();
    int lineNumber = line.getLineNumber();
    map<string, vector<int>> *statements = &this->statements;
    insertLineNumber(statements, &type, &lineNumber);
    if(type == "=") {
        extractVariables(line);
    }
}

void Extractor::extractVariables(Line line) {
    set<string>* variables = &this->variables;
    vector<string> tokens = line.getTokens();
    for(auto token = begin(tokens); token != end(tokens); token++) {
        if(*token == "=" && token != begin(tokens)) {
            variables->insert(*(prev(token)));
        }
    }
}

void Extractor::extractEntities(const vector<Line> &program) {
    for(auto line: program) {
        string type = line.getType();
        if(isProcedure(line)) {
            extractProcedure(line);
        } if (isStatement(line)) {
            extractStatement(line);
        }
        extractConstants(line);
    }
}

void Extractor::printEntities() {
    cout << "Procedures: " << endl;
    for(auto procedure: this->procedures) {
        cout << procedure << " ";
    }
    cout << endl << endl;

    cout << "Variables: " << endl;
    for(auto variable: this->variables) {
        cout << variable << " ";
    }
    cout << endl << endl;

    cout << "Constants: " << endl;
    for(auto constants: this->constants) {
        cout << constants << " ";
    }
    cout << endl << endl;

    cout << "Statements: " << endl;
    for(auto statement = begin(this->statements); statement != end(this->statements); statement++) {
        cout << "Statement type " << statement->first << " ";
        for(int lineNumber : statement->second) {
            cout << lineNumber << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Extractor::extract(const vector<Line> &program) {
    extractEntities(program);
    // Call and get results of extraction
    auto [parentsRS, parentsStarRS] = extractParentsRelationship(program);
    auto [followsRS, followsStarRS] = extractFollowsRelationship(program);
    // Set results here
    this->parentsRS = parentsRS;
    this->parentsStarRS = parentsStarRS;

    this->followsRS = followsRS;
    this->followsStarRS = followsStarRS;
}
