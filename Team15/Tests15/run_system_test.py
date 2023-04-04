import subprocess

#tests = ["affects", "assign", "bool", "calls", "follows", "general", "ifwhile", "next", "parent", "tuple", "usesmodifies", "with"]
tests = []

for i in range(1, 27):
    tests.append(str(i))

#for test in tests:
#    source = "source-" + test + ".txt"
#    query = "query-" + test + ".txt"
#    out = "out-" + test + ".xml"
#    cmd = ["autotester.exe", source, query, out]
#    subprocess.run(cmd)

for test in tests:
    source = test + "_source" + ".txt"
    query = test + "_queries" + ".txt"
    out = test + "_out" + ".xml"
    cmd = ["autotester.exe", source, query, out]
    subprocess.run(cmd)