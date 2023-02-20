#include "source_processor/include/extractor/Extractor.h"

Extractor::Extractor() {}

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

void Extractor::printEntities() {
    cout << "Procedures: " << endl;
    for(const auto& procedure: procedures) {
        cout << procedure << " ";
    }
    cout << endl << endl;

    cout << "Variables: " << endl;
    for(const auto& variable: variables) {
        cout << variable << " ";
    }
    cout << endl << endl;

    cout << "Constants: " << endl;
    for(const auto& c: constants) {
        cout << c << " ";
    }
    cout << endl << endl;

    cout << "Statements: " << endl;
    for(auto[key, value] : statements) {
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

unordered_map<int, set<int>> Extractor::getParentRS() {
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
    this->constants = extractConstants(program);
    this->statements = extractStatements(program);
    this->variables = extractVariables(program);
    this->procedures = extractProcedures(program);
    // Call and get results of extraction
    this->modifiesRS = extractModifiesRS(program);
    auto [parents, parentsStar] = extractParentsRelationship(program);
    auto [follows, followsStar] = extractFollowsRelationship(program);
    //TODO: ensure variables are defined before calling extractAssignmentRS and extractUsesRS
    this->assignsRS = extractAssignmentRS(program, variables);
    this->usesRS = extractUsesRS(program, variables);
    // Set results here
    this->parentsRS = parents;
    this->parentsStarRS = parentsStar;

    this->followsRS = follows;
    this->followsStarRS = followsStar;
}
