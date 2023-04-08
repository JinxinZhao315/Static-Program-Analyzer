@echo off
title system test 1 queries

.\AutoTester SystemTest_source.txt ModifiesP.txt outModifiesP.xml
.\AutoTester SystemTest_source.txt ModifiesS.txt outModifiesS.xml
.\AutoTester SystemTest_source.txt UsesP.txt outUsesP.xml
.\AutoTester SystemTest_source.txt UsesS.txt outUsesS.xml
.\AutoTester SystemTest_source.txt Calls.txt outCalls.xml
.\AutoTester SystemTest_source.txt CallsT.txt outCallsT.xml
.\AutoTester SystemTest_source.txt Follows.txt outFollows.xml
.\AutoTester SystemTest_source.txt Parent.txt outParent.xml
.\AutoTester SystemTest_source.txt FollowsParent.txt outFollowsParent.xml
.\AutoTester SystemTest_source.txt With.txt outWith.xml
.\AutoTester SystemTest_source.txt Pattern.txt outPattern.xml
.\AutoTester SystemTest_source.txt Next.txt outNext.xml
.\AutoTester SystemTest_source.txt PatternExtra.txt outPatternExtra.xml
.\AutoTester SystemTest_source.txt Boolean.txt outBoolean.xml
.\AutoTester SystemTest_source.txt Affects.txt outAffects.xml
.\AutoTester SystemTest_source.txt OtherClauses.txt outOtherClauses.xml
.\AutoTester SystemTest_source.txt Multiple.txt outMultiple.xml
.\AutoTester SystemTest_source.txt SystemTest_queries.txt outSystemTest_queries.xml
.\AutoTester SystemTest_source.txt Tuple.txt outTuple.xml


echo FINISHED
pause
exit