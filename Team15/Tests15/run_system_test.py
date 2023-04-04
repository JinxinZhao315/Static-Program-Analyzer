import subprocess

#Run our test cases
tests = ["affects", "assign", "bool", "calls", "follows", "general", "ifwhile", "next", "parent", "tuple", "usesmodifies", "with"]
for test in tests:
   source = "source-" + test + ".txt"
   query = "query-" + test + ".txt"
   out = "out-" + test + ".xml"
   cmd = ["autotester.exe", source, query, out]
   subprocess.run(cmd)

#Run Jared's test cases
# for i in range(1, 28):
#     source = str(i) + "_source" + ".txt"
#     query = str(i) + "_queries" + ".txt"
#     out = str(i) + "_out" + ".xml"
#     cmd = ["autotester.exe", source, query, out]
#     subprocess.run(cmd)