#!/usr/bin/python
import os
import subprocess
import sys
buildDir = "build/"
def binOfCpp(cpp):
	"""
	:rtype : str
	:type cpp: str
	"""
	return buildDir + cpp[:-4] + ".bin"

def isValidator(cpp):
	"""
	:type cpp: str
	"""
	return cpp.startswith("examples/validators")

def testDir(cpp):
	"""
	:type cpp: str
	:rtype : str
	"""
	return cpp[:-4] + "/"

def getTests(cpp, testFile):
	"""
	:rtype : list
	:type cpp: str
	:type testFile: str
	"""
	suffixes = ["", ".test", ".testset"]
	prefix = testDir(cpp) + testFile
	for suffix in suffixes:
		possibleName = prefix + suffix
		if os.path.exists(possibleName):
			name = possibleName;
			break
	if not name:
		print "test not found"
		sys.exit(2);
	with open(name) as file:
		string = file.read();
	return string.split("```\n")

def runTest(cpp, test):
	"""
	:rtype : bool
	:type cpp: str
	:type test: str
	"""
	testParts = test.split('`\n')
	testSize = 2 if isValidator(cpp) else 4
	if len(testParts) != testSize:
		raise SyntaxError("test '" + str(testParts) + "' is malformed")
	expectedCode = int(testParts.pop())
	if isValidator(cpp):
		inputFile = buildDir + "input"
		with open(inputFile, "w") as f:
			f.write(testParts[0])
		with open(inputFile, "r") as f:
			realCode = subprocess.call(binOfCpp(cpp), stdin=f)
	else:
		names = (buildDir + "input", buildDir + "output", buildDir + "answer")
		for name, text in zip(names, testParts):
			with open(name, 'w') as f:
				f.write(text)
		realCode = subprocess.call([binOfCpp(cpp)] + list(names))
		for file in names:
			os.remove(file)

	return realCode == expectedCode

def runTestByNumber(cpp, testFile, number):
	"""
	:rtype : bool
	:type cpp: str
	:type testFile: str
	:type number: int
	"""
	return runTest(cpp, getTests(cpp, testFile)[number])


def runTestFile(cpp, testFile):
	"""
	:rtype : int
	:type cpp: str
	:type testFile: str
	"""
	errors = 0
	for test in getTests(cpp, testFile):
		if not runTest(cpp, test):
			errors += 1

	print errors, "errors in", testFile, "for", cpp
	return errors


def runAllTests(cpp):
	"""
	:rtype : int
	:type cpp: str
	"""
	errors = 0
	for testFile in os.listdir(testDir(cpp)):
		errors += runTestFile(cpp, testFile)
	print errors, "errors in total"
	return errors


if len(sys.argv) == 2:
	result = runAllTests(sys.argv[1])
elif len(sys.argv) == 3:
	result = runTestFile(sys.argv[1], sys.argv[2]) != 0
elif len(sys.argv) == 4:
	result = runTestByNumber(sys.argv[1], sys.argv[2], int(sys.argv[3]))
else:
	print "Wrong usage"
	sys.exit(1)

if result != 0:
	sys.exit(1)