#include "source_processor/include/extractor/Extractor.h"

Extractor::Extractor() {
    constantExtractor = new ConstantExtractor();
    procedureExtractor = new ProcedureExtractor();
    statementExtractor = new StatementExtractor();
}

set<string> Extractor::getVariables() {
    return statementExtractor->getVariables();
}

set<string> Extractor::getConstants() {
    return constantExtractor->getConstants();
}

set<string> Extractor::getProcedures() {
    return procedureExtractor->getProcedures();
}

unordered_map<string, set<int>> Extractor::getStatements() {
    return statementExtractor->getStatements();
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

void Extractor::extractEntities(const vector<Line> &program) {
    for(auto line: program) {
        string type = line.getType();
        if(isProcedure(line)) {
            procedureExtractor->extractProcedures(line);
        } if (isStatement(line)) {
            statementExtractor->extractStatements(line);
        }
        constantExtractor->extractConstants(line);
    }
}

void Extractor::printEntities() {
    cout << "Procedures: " << endl;
    for(const auto& procedure: procedureExtractor->getProcedures()) {
        cout << procedure << " ";
    }
    cout << endl << endl;

    cout << "Variables: " << endl;
    for(const auto& variable: statementExtractor->getVariables()) {
        cout << variable << " ";
    }
    cout << endl << endl;

    cout << "Constants: " << endl;
    for(const auto& c: constantExtractor->getConstants()) {
        cout << c << " ";
    }
    cout << endl << endl;

    cout << "Statements: " << endl;
    for(auto[key, value] : statementExtractor->getStatements()) {
        cout << "Statement type " << key << ": ";
        for(auto i : value) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << endl;
}

unordered_map<int, int> Extractor::getFollowsRS() {
    return this->followsRS;
}

unordered_map<int, set<int>> Extractor::getFollowsStarRS() {
    return this->followsStarRS;
}

unordered_map<int, int> Extractor::getParentRS() {
    return this->parentsRS;
}

unordered_map<int, set<int>> Extractor::getParentStarRS() {
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
    this->modifiesRS = extractModifiesRS(program);
    auto [parents, parentsStar] = extractParentsRelationship(program);
    auto [follows, followsStar] = extractFollowsRelationship(program);
    //TODO: ensure variables are defined before calling extractAssignmentRS and extractUsesRS
    this->assignsRS = extractAssignmentRS(program, statementExtractor->getVariables());
    this->usesRS = extractUsesRS(program, statementExtractor->getVariables());
    // Set results here
    this->parentsRS = parents;
    this->parentsStarRS = parentsStar;

    this->followsRS = follows;
    this->followsStarRS = followsStar;
}
