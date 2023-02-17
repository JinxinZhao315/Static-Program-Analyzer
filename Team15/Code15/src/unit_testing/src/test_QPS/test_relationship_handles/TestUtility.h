#include "pkb/include/PKB.h"
#include "QPS/include/PQLDriver.h"

class TestUtility {
public:
    TestUtility();
    static string testDriver(string queryStr, PKB& pkb) {
        PQLDriver driver = PQLDriver(pkb);
        set<string> retSet = driver.processPQL(queryStr);
        string retStr;

        if (retSet.empty())
        {
            retStr = "None";
        }
        else
        {
            retStr = std::accumulate(begin(retSet),
                                     end(retSet),
                                     string{},
                                     [](const string &a, const string &b)
                                     { return a.empty() ? b : a + ',' + b; });
        }
        return retStr;
    };
};
