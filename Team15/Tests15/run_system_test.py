import subprocess

#Run our test cases
tests = [ "assign", "bool", "calls", "follows", "general", "ifwhile", "next", "optimization", "parent", "tuple", "usesmodifies", "with"]
for test in tests:
   source = "source-" + test + ".txt"
   query = "query-" + test + ".txt"
   out = "../../Code15/tests/local_test/out-" + test + ".xml"
   cmd = ["../../Code15/out/build/x64-Debug/src/autotester/autotester.exe", source, query, out]
   subprocess.run(cmd)

#Run Jared's test cases
# for i in range(1, 28):
#     source = str(i) + "_source" + ".txt"
#     query = str(i) + "_queries" + ".txt"
#     out = str(i) + "_out" + ".xml"
#     cmd = ["autotester.exe", source, query, out]
#     subprocess.run(cmd)