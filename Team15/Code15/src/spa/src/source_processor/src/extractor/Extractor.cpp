#include "../../include/extractor/Extractor.h"

Extractor::Extractor() {
    statements["while"] = {};
    statements["if"] = {};
    statements["read"] = {};
    statements["print"] = {};
    statements["call"] = {};
    statements["="] = {};
}

set<string> Extractor::getVariables() {
    return variables;
}

set<string> Extractor::getConstants() {
    return constants;
}

set<string> Extractor::getProcedures() {
    return procedures;
}

unordered_map<string, set<int>> Extractor::getStatements() {
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
    set<string>* p = &this->procedures;
    p->insert(procedureName);
}

bool isNumeric(const string& token) {
    try {
        stoi(token);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
    }
}

void Extractor::extractConstants(Line line) {
    vector<string> tokens = line.getTokens();
    set<string> *c = &this->constants;
    for (auto token = begin(tokens); token != end(tokens); token++) {
        if (isNumeric(*token)) {
            c->insert(*token);
        }
    }
}

void insertLineNumber(unordered_map<string, set<int>>* statements, string* type, int* lineNumber) {
    statements->at(*type).insert(*lineNumber);
}

void Extractor::extractStatement(Line line) {
    vector<string> tokens = line.getTokens();
    string type = line.getType();
    int lineNumber = line.getLineNumber();
    unordered_map<string, set<int>> *stmt = &this->statements;
    insertLineNumber(stmt, &type, &lineNumber);
    if(type == "=") {
        extractVariables(line);
    }
}

void Extractor::extractVariables(Line line) {
    set<string>* v = &this->variables;
    vector<string> tokens = line.getTokens();
    for(auto token = begin(tokens); token != end(tokens); token++) {
        if(*token == "=" && token != begin(tokens)) {
            v->insert(*(prev(token)));
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
    for(const auto& procedure: this->procedures) {
        cout << procedure << " ";
    }
    cout << endl << endl;

    cout << "Variables: " << endl;
    for(const auto& variable: this->variables) {
        cout << variable << " ";
    }
    cout << endl << endl;

    cout << "Constants: " << endl;
    for(const auto& c: this->constants) {
        cout << c << " ";
    }
    cout << endl << endl;

    cout << "Statements: " << endl;
    for(auto[key, value] : this->statements) {
        cout << "Statement type " << key << ": ";
        for(auto i : value) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << endl;
}

map<int, int> Extractor::getFollowsRS() {
    return this->followsRS;
}

map<int, set<int>> Extractor::getFollowsStarRS() {
    return this->followsStarRS;
}

map<int, int> Extractor::getParentRS() {
    return this->parentsRS;
}

map<int, set<int>> Extractor::getParentStarRS() {
    return this->parentsStarRS;
}

unordered_map<int, set<string>> Extractor::getModifiesRS() {
    return this->modifiesRS;
}

unordered_map<int, set<string>> Extractor::getUsesRS() {
    return this->usesRS;
}

unordered_map<string, set<Line>> Extractor::getAssignsRS() {
    return this->assignsRS;
}

void Extractor::extract(const vector<Line> &program) {
    extractEntities(program);
    // Call and get results of extraction
    auto [parentsRS, parentsStarRS] = extractParentsRelationship(program);
    auto [followsRS, followsStarRS] = extractFollowsRelationship(program);
    auto modifiesRS = extractModifiesRS(program);
    //TODO: ensure variables are defined before calling extractAssignmentRS and extractUsesRS
    auto assignsRS = extractAssignmentRS(program, variables);
    auto usesRS = extractUsesRS(program, variables);
    // Set results here
    this->parentsRS = parentsRS;
    this->parentsStarRS = parentsStarRS;

    this->followsRS = followsRS;
    this->followsStarRS = followsStarRS;

    this->usesRS = usesRS;
    this->modifiesRS = modifiesRS;
    this->assignsRS = assignsRS;
}
