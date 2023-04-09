#include "sp/include/extractor/AffectsRelationshipExtractor.h"

void clearCache() {
    cache.clear();
}


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

Line findLine(int lineNum, unordered_map<int, Line> lineNumToLineMap) {
    return lineNumToLineMap[lineNum];
}

bool checkAssign(const Line& line1, const Line& line2) {
    return line1.getType() == ASSIGN && line2.getType() == ASSIGN;
}

bool checkModifies(const Line& line, const string& variable, unordered_map<int, set<string>> modifiesRS) {
    int lineNum = line.getLineNumber();
    set<string> modifiedVars = modifiesRS[lineNum];
    return modifiedVars.find(variable) != modifiedVars.end();
}

bool checkPath(const vector<int>& path, const string& variable, const unordered_map<int, set<string>>& modifiesRS,
               const vector<Line>& program, int lineNum1, int lineNum2, unordered_map<int, Line> lineNumToLineMap) {
    bool check = false;
    for(auto node : path) {
        Line line = findLine(node, lineNumToLineMap);
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
                         const unordered_map<int, set<string>>& modifiesRS,
                         const unordered_map<int, set<string>>& usesRS,
                         unordered_map<int, Line> lineNumToLineMap) {
    for(auto node : path) {
        if(extractAffectsRS(program, lineNum1, node, cfg, modifiesRS, usesRS, false, lineNumToLineMap)
            && extractAffectsRS(program, node, lineNum2, cfg, modifiesRS, usesRS, false, lineNumToLineMap)) {
            return true;
        }
    }
    return false;
}

set<int> extractAffectsWithWildcard(const vector<Line>& program, int lineNum, bool wildCardIsFirstArg,
                                    const unordered_map<int, set<int>>& cfg,
                                    const unordered_map<int, set<string>>& modifiesRS,
                                    const unordered_map<int, set<string>>& usesRS,
                                    bool findAffectsStar, unordered_map<int, Line> lineNumToLineMap) {
    set<int> stmtLineNums;
    for(const auto& line : program) {
        int otherLineNum = line.getLineNumber();
        if(lineNum > 0 && otherLineNum > 0 && lineNum != otherLineNum) {
            bool affects;
            if (wildCardIsFirstArg) {
                affects = extractAffectsRS(program, otherLineNum, lineNum, cfg,  modifiesRS, usesRS, findAffectsStar, lineNumToLineMap);
            } else {
                affects = extractAffectsRS(program, lineNum, otherLineNum, cfg, modifiesRS, usesRS, findAffectsStar, lineNumToLineMap);
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
                                                       const unordered_map<int, set<string>>& modifiesRS,
                                                       const unordered_map<int, set<string>>& usesRS,
                                                       bool findAffectsStar, unordered_map<int, Line> lineNumToLineMap) {
    unordered_map<int, set<int>> allAffects;
    for(int i = 0; i < program.size(); i++) {
        const Line& line = program[i];
        int lineNum = line.getLineNumber();
        for(int j = 0; j < program.size(); j++) {
            const Line& otherLine = program[j];
            int otherLineNum = otherLine.getLineNumber();
            if(lineNum > 0 && otherLineNum > 0 && i != j
                && extractAffectsRS(program, lineNum, otherLineNum, cfg, modifiesRS, usesRS, findAffectsStar, lineNumToLineMap)) {
                    allAffects[lineNum].insert(otherLineNum);
            };
        }
    }
    return allAffects;
}

bool extractAffectsRS(const vector<Line>& program, int lineNum1, int lineNum2,
                                          const unordered_map<int, set<int>>& cfg,
                                          const unordered_map<int, set<string>>& modifiesRS,
                                          const unordered_map<int, set<string>>& usesRS,
                                          bool findAffectsStar, unordered_map<int, Line> lineNumToLineMap) {
    pair<int, int> key = make_pair(lineNum1, lineNum2);
    if (cache.find(key) != cache.end()) {
        return cache[key];
    }
    set<string> affectedVars;
    unordered_map<int, set<int>> result;
    Line line1 = findLine(lineNum1, lineNumToLineMap);
    Line line2 = findLine(lineNum2, lineNumToLineMap);
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
            if(!checkPath(option, v, modifiesRS, program, lineNum1, lineNum2, lineNumToLineMap)) {
                pathCheck = false;
                break;
            }
        }
        if(checkAffects(modifies, pathCheck)) {
            affectedVars.insert(v);
        } else if(findAffectsStar) {
            for(const auto& option : paths) {
                if(checkTransitivePath(option, program, lineNum1, lineNum2, cfg, modifiesRS, usesRS, lineNumToLineMap)) {
                    affectedVars.insert(v);
                }
            }
        }
    }
    bool affects = !affectedVars.empty();
    cache[key] = affects;
    return affects;
}
