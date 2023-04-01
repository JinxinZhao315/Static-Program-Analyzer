#include "source_processor/include/extractor/Extractor.h"

Extractor::Extractor() {
    variableExtractor = new VariableExtractor();
    procedureExtractor = new ProcedureExtractor();
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

unordered_map<KeywordsEnum, set<int>> Extractor::getStatements() {
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

unordered_map<string, set<Line>> Extractor::getIfRS() {
    return this->ifRS;
}

unordered_map<string, set<Line>> Extractor::getWhileRS() {
    return this->whileRS;
}

unordered_map<string, set<string>> Extractor::getProcedureModifiesRS() {
    return this->procedureModifiesRS;
}

unordered_map<string, set<string>> Extractor::getProcedureUsesRS() {
    return this->procedureUsesRS;
}

unordered_map<string, set<string>> Extractor::getCallsRS() {
    return this->callsRS;
}

unordered_map<string, set<string>> Extractor::getCallsStarRS() {
    return this->callsStarRS;
}

unordered_map<int, string> Extractor::getReadLineNumToVarName() {
    return this->readLineNumToVarName;
}

unordered_map<int, string> Extractor::getPrintLineNumToVarName() {
    return this->printLineNumToVarName;
}

unordered_map<int, string> Extractor::getCallLineNumToProcName() {
    return this->callLineNumToProcName;
}

unordered_map<int, set<int>> Extractor::getNextRS() {
    return this->nextRS;
}

void Extractor::extract(const vector<Line> &program) {
    this->constants = extractConstants(program);
    this->statements = extractStatements(program);
    variableExtractor->extractVariables(program);
    variableExtractor->extractReadAndPrintLineNumToVarName(program);
    this->variables = variableExtractor->getVariables();
    this->readLineNumToVarName = variableExtractor->getReadLineNumToVarName();
    this->printLineNumToVarName = variableExtractor->getPrintLineNumToVarName();
    procedureExtractor->extractProcedures(program);
    procedureExtractor->extractCallLineNumToProcName(program);
    this->procedures = procedureExtractor->getProcedures();
    this->callLineNumToProcName = procedureExtractor->getCallLineNumToProcName();
    // Call and get results of extraction
    this->assignsRS = extractAssignmentRS(program, variables);
    this->ifRS = extractConditionalRS(IF, program, variables);
    this->whileRS = extractConditionalRS(WHILE, program, variables);

    auto [parents, parentsStar] = extractParentsRelationship(program);
    this->parentsRS = parents;
    this->parentsStarRS = parentsStar;

    auto [follows, followsStar] = extractFollowsRelationship(program);
    this->followsRS = follows;
    this->followsStarRS = followsStar;

    auto [modifies, procModifies, uses, procUses, calls, callsStar] = extractModifiesUsesAndCallRS(program, variables);
    this->modifiesRS = modifies;
    this->procedureModifiesRS = procModifies;
    this->usesRS = uses;
    this->procedureUsesRS = procUses;
    this->callsRS = calls;
    this->callsStarRS = callsStar;

    this->nextRS = extractNextRS(program, follows);
}
