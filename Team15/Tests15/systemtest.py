import subprocess

tests = ["assign", "calls", "follows", "general", "ifwhile", "next", "parent", "usesmodifies", "with"]

for test in tests:
    source = "source-" + test + ".txt"
    query = "query-" + test + ".txt"
    out = "out-" + test + ".xml"
    cmd = ["autotester.exe", source, query, out]
    subprocess.run(cmd)
