import sys
import os
import time
import subprocess

# Please add new test cases in alphabetical order. Thanks :)
l = [
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"11",
	"12",
	"13",
	"14",
	"15",
	"16",
]


for test in l:
   source = test + "_source.txt"
   query = test + "_query.txt"
   out = "../../Code15/tests/g/out-" + test + ".xml"
   cmd = ["../../Code15/out/build/x64-Debug/src/autotester/autotester.exe", source, query, out]
   subprocess.run(cmd)

# for elem in l:
# 	try:
# 		os.remove("../Code15/Tests/" + elem + "_out.xml")
# 	except OSError:
# 		pass

# for elem in l:
# 	try:
# 		os.system("..\Code15\Debug\Autotester.exe " + elem + "_source.txt " + elem + "_queries.txt ..\Code15\Tests\\"+ elem + "_out.xml")
# 	except KeyboardInterrupt:
# 		pass

# for elem in l:
# 	hasErrors = False
# 	hasCorrect = False
# 	hasTimeout = False
# 	with open("../Code15/Tests/" + elem + "_out.xml") as f:
# 		if '<failed>' in f.read():
# 			hasErrors = True
# 	with open("../Code15/Tests/" + elem + "_out.xml") as f:
# 		if '<passed/>' in f.read():
# 			hasCorrect = True
# 	with open("../Code15/Tests/" + elem + "_out.xml") as f:
# 		if '<timeout/>' in f.read():
# 			hasTimeout = True
	
# 	if hasErrors and hasCorrect:
# 		if hasTimeout:
# 			print(elemt + " has timeout")
# 		else:
# 			print(elem + " PARTIAL!")
# 	elif hasErrors and not hasCorrect:
# 		if hasTimeout:
# 			print(elemt + " has timeout")
# 		else:
# 			print(elem + " all WRONG!")
# 	elif not hasErrors and hasCorrect:
# 		if hasTimeout:
# 			print(elemt + " has timeout")
# 		else:
# 			print(elem + " all correct")
# 	else:
# 		if hasTimeout:
# 			print(elemt + " has timeout")
# 		else:
# 			print(elem + " UNKNOWN STATUS")

# input("press return key to exit")