import sys
import os
import time
import subprocess

# Please add new test cases in alphabetical order. Thanks :)
l = [
    "Affects",
    "Boolean",
    "Calls",
    "CallsT",
    "Follows",
    "FollowsParent",
    "ModifiesP",
    "ModifiesS",
    "Multiple",
    "Next",
    "OtherClauses",
    "Parent",
    "Pattern",
    "PatternExtra",
    "SystemTest_queries",
    "Tuple",
    "UsesP",
    "UsesS",
    "With",
]


for test in l:
	source = "SystemTest_source.txt"
	query = test + ".txt"
	if sys.platform == "win32": #win
		out = "../../Code15/tests/ALLTESTCASESTOTEST/out-" + test + ".xml"
		cmd = ["../../Code15/out/build/x64-Debug/src/autotester/autotester.exe", source, query, out]
		subprocess.run(cmd)
	elif sys.platform == "darwin": #mac
		out = "../../Code15/tests/ALLTESTCASESTOTEST/out-" + test + ".xml"
		cmd = ["../../Code15/cmake-build-debug/src/autotester/autotester", source, query, out]
		subprocess.run(cmd)