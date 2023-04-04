import subprocess

tests = ["affects", "assign", "bool", "calls", "follows", "general", "ifwhile", "next", "parent", "tuple", "usesmodifies", "with"]

#for test in tests:
#    source = "source-" + test + ".txt"
#    query = "query-" + test + ".txt"
#    out = "out-" + test + ".xml"
#    cmd = ["autotester.exe", source, query, out]
#    subprocess.run(cmd)

for test in tests:
    source = test + "_source" + ".txt"
    query = test + "_query" + ".txt"
    out = test + "_out" + ".xml"
    cmd = ["autotester.exe", source, query, out]
    subprocess.run(cmd)