@echo off
title system test 1 queries

.\AutoTester iter1-test1.txt iter1-test1q.txt outiter1-test1.xml
.\AutoTester iter2-test1.txt iter2-test1q.txt outiter2-test1.xml
.\AutoTester iter2-test2.txt iter2-test2q.txt outiter2-test2.xml
.\AutoTester iter2-test3.txt iter2-test3q.txt outiter2-test3.xml
.\AutoTester iter2-test5.txt iter2-test5q.txt outiter2-test5.xml
.\AutoTester iter2-test6.txt iter2-test6q.txt outiter2-test6.xml
.\AutoTester iter2-test7.txt iter2-test7q.txt outiter2-test7.xml
.\AutoTester iter2-test8.txt iter2-test8q.txt outiter2-test8.xml
.\AutoTester iter3-test1.txt iter3-test1q.txt outiter3-test1.xml
.\AutoTester iter3-test2.txt iter3-test2q.txt outter3-test2.xml
.\AutoTester iter3-test-with.txt iter3-test-withq.txt outiter3-test-with.xml

echo FINISHED
pause
exit