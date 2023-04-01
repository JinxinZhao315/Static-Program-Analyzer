#include <utility>

#include "source_processor/include/extractor/AffectsRelationshipExtractor.h"

void dfs(unordered_map<int, set<int>> cfg, int lineNum1, int lineNum2, vector<int>* path, vector<vector<int>>* paths) {
    path->push_back(lineNum1);
    if(lineNum1 == lineNum2) {
        paths->push_back(*path);
    } else {
        set<int> currOptions = cfg[lineNum1];
        for(auto option : currOptions) {
            if (find(path->begin(), path->end(), option) == path->end()) {
                dfs(cfg, option, lineNum2, path, paths);
            }
        }
    }
    path->pop_back();
}

Line findLine(const vector<Line>& program, int lineNum) {
    Line result;
    for(const auto& line : program) {
        if(line.getLineNumber() == lineNum) result = line;
    }
    return result;
}

bool checkAssign(const Line& line1, const Line& line2) {
    return line1.getType() == ASSIGN && line2.getType() == ASSIGN;
}

bool checkModifies(const Line& line, const string& variable, unordered_map<int, set<string>> modifiesRS) {
    int lineNum = line.getLineNumber();
    set<string> modifiedVars = modifiesRS[lineNum];
    return modifiedVars.find(variable) != modifiedVars.end();
}

bool checkUses(const Line& line, const string& variable, unordered_map<int, set<string>> usesRS) {
    int lineNum = line.getLineNumber();
    set<string> usedVars = usesRS[lineNum];
    return usedVars.find(variable) != usedVars.end();
}

bool checkPath(vector<int> path, const string& variable, const unordered_map<int, set<string>>& modifiesRS,
               const vector<Line>& program, int lineNum1, int lineNum2) {
    bool check = false;
    for(auto node : path) {
        Line line = findLine(program, node);
        KeywordsEnum type = line.getType();
        if(node == lineNum1 || node == lineNum2 || type == WHILE || type == IF) {
            continue;
        } else if(checkModifies(line, variable, modifiesRS)) {
            check = true;
        }
    }
    return check;
}

bool checkAffects(bool checkModifies, bool checkUses, bool checkPath) {
    return checkModifies && checkUses && !checkPath;
}

set<string> extractAffectsRS(const vector<Line>& program, int lineNum1, int lineNum2,
                                          unordered_map<int, set<int>> cfg,
                                          const set<string>& variables,
                                          const unordered_map<int, set<string>>& modifiesRS,
                                          const unordered_map<int, set<string>>& usesRS
) {
    set<string> affectedVars;
    unordered_map<int, set<int>> result;
    Line line1 = findLine(program, lineNum1);
    Line line2 = findLine(program, lineNum2);
    if(!checkAssign(line1, line2)) return affectedVars;
    vector<int> path;
    vector<vector<int>> paths;

    //TODO: check if nextStarRS can be used instead of DFS
    extractNextStarRS(cfg); // the value is the set of nodes that it will visit later on which can then be used for affects

    dfs(std::move(cfg), lineNum1, lineNum2, &path, &paths);
    for(const auto& v : variables) {
        bool modifies = checkModifies(line1, v, modifiesRS);
        bool uses = checkUses(line2, v, usesRS);
        bool pathCheck = true;
        for(auto option : paths) {
            if(!checkPath(option, v, modifiesRS, program, lineNum1, lineNum2)) {
                pathCheck = false;
                break;
            }
        }
        if(checkAffects(modifies, uses, pathCheck)) affectedVars.insert(v);
    }
    return affectedVars;
}
