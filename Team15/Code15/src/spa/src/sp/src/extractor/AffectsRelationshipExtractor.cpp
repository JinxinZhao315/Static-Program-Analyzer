#include "sp/include/extractor/AffectsRelationshipExtractor.h"

void dfs(unordered_map<int, set<int>> cfg, int lineNum1, int lineNum2, vector<int>* path,
         vector<vector<int>>* paths, unordered_map<int, int>* visited) {
    path->push_back(lineNum1);
    (*visited)[lineNum1]++;
    if(lineNum1 == lineNum2 && path->size() > 1) {
        paths->push_back(*path);
    } else {
        set<int> currOptions = cfg[lineNum1];
        for(auto option : currOptions) {
            if ((*visited)[option] < 2) {
                dfs(cfg, option, lineNum2, path, paths, visited);
            }
        }
    }
    (*visited)[lineNum1]--;
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

bool checkPath(const vector<int>& path, const string& variable, const unordered_map<int, set<string>>& modifiesRS,
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

bool checkAffects(bool checkModifies, bool checkPath) {
    return checkModifies && !checkPath;
}

bool checkTransitivePath(const vector<int>& path, const vector<Line>& program, int lineNum1, int lineNum2,
                         const unordered_map<int, set<int>>& cfg,
                         const set<string>& variables,
                         const unordered_map<int, set<string>>& modifiesRS,
                         const unordered_map<int, set<string>>& usesRS) {
    for(auto node : path) {
        if(extractAffectsRS(program, lineNum1, node, cfg, variables, modifiesRS, usesRS, false)
            && extractAffectsRS(program, node, lineNum2, cfg, variables, modifiesRS, usesRS, false)
        ) {
            return true;
        }
    }
    return false;
}

set<int> extractAffectsWithWildcard(const vector<Line>& program, int lineNum, bool wildCardIsFirstArg,
                                    const unordered_map<int, set<int>>& cfg,
                                    const set<string>& variables,
                                    const unordered_map<int, set<string>>& modifiesRS,
                                    const unordered_map<int, set<string>>& usesRS,
                                    bool findAffectsStar) {
    set<int> stmtLineNums;
    for(auto line : program) {
        int otherLineNum = line.getLineNumber();
        if(lineNum > 0 && otherLineNum > 0 && lineNum != otherLineNum) {
            bool affects;
            if (wildCardIsFirstArg) {
                affects = extractAffectsRS(program, otherLineNum, lineNum, cfg, variables, modifiesRS, usesRS, findAffectsStar);
            } else {
                affects = extractAffectsRS(program, lineNum, otherLineNum, cfg, variables, modifiesRS, usesRS, findAffectsStar);
            }
            if(affects) {
                stmtLineNums.insert(otherLineNum);
            }
        }
    }
    return stmtLineNums;
}

unordered_map<int, set<int>> extractAffectsWithMultipleWildcards(const vector<Line>& program,
                                                       const unordered_map<int, set<int>>& cfg,
                                                       const set<string>& variables,
                                                       const unordered_map<int, set<string>>& modifiesRS,
                                                       const unordered_map<int, set<string>>& usesRS,
                                                       bool findAffectsStar) {
    unordered_map<int, set<int>> allAffects;
    for(int i = 0; i < program.size(); i++) {
        const Line& line = program[i];
        int lineNum = line.getLineNumber();
        for(int j = 0; j < program.size(); j++) {
            const Line& otherLine = program[j];
            int otherLineNum = otherLine.getLineNumber();
            if(lineNum > 0 && otherLineNum > 0 && i != j
                && extractAffectsRS(program, lineNum, otherLineNum, cfg, variables, modifiesRS, usesRS, findAffectsStar)) {
                    allAffects[lineNum].insert(otherLineNum);
            };
        }
    }
    return allAffects;
}

bool extractAffectsRS(const vector<Line>& program, int lineNum1, int lineNum2,
                                          const unordered_map<int, set<int>>& cfg,
                                          const set<string>& variables,
                                          const unordered_map<int, set<string>>& modifiesRS,
                                          const unordered_map<int, set<string>>& usesRS,
                                          bool findAffectsStar
) {
    set<string> affectedVars;
    unordered_map<int, set<int>> result;
    Line line1 = findLine(program, lineNum1);
    Line line2 = findLine(program, lineNum2);
    if(!checkAssign(line1, line2)) return false;
    vector<int> path;
    vector<vector<int>> paths;
    unordered_map<int, int> visited;

    dfs(cfg, lineNum1, lineNum2, &path, &paths, &visited);
    set<string> varThatAreUsedInLineNum2;
    if (usesRS.count(lineNum2) > 0) {
        varThatAreUsedInLineNum2 = usesRS.at(lineNum2);
    }

    for(const auto& v : varThatAreUsedInLineNum2) {
        bool modifies = checkModifies(line1, v, modifiesRS);
        bool pathCheck = true;
        for(const auto& option : paths) {
            if(!checkPath(option, v, modifiesRS, program, lineNum1, lineNum2)) {
                pathCheck = false;
                break;
            }
        }
        if(checkAffects(modifies, pathCheck)) {
            affectedVars.insert(v);
        } else if(findAffectsStar) {
            for(const auto& option : paths) {
                if(checkTransitivePath(option, program, lineNum1, lineNum2, cfg, variables, modifiesRS, usesRS)) {
                    affectedVars.insert(v);
                }
            }
        }
    }
    bool affects = !affectedVars.empty();
    return affects;
}
