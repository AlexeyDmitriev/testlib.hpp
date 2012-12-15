#!/usr/bin/python
import os
import subprocess
import sys
logLevels = ["no", "errors", "cpp", "testset", "test", "all"]

def needLog(messageLevel, logLevel):
	"""
	:rtype : bool
	:type messageLevel: str
	"""
	return logLevels.index(messageLevel) <= logLevels.index(logLevel)

def log(messageLevel, logLevel, *text):
	"""
	:type text: str
	:type messageLevel: str
	"""
	if needLog(messageLevel, logLevel):
		print ' '.join(map(str, text))

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
	name = None
	for suffix in suffixes:
		possibleName = prefix + suffix
		if os.path.exists(possibleName):
			name = possibleName
			break
	if not name:
		print "test not found"
		sys.exit(2)
	with open(name) as file:
		string = file.read()
	return string.split("```\n")

def runTest(cpp, test, logLevel):
	"""
	:type logLevel: str
	:rtype : bool
	:type cpp: str
	:type test: str
	"""
	testParts = test.split('`\n')
	testSize = 2 if isValidator(cpp) else 4
	if len(testParts) != testSize:
		raise SyntaxError("test '" + str(testParts) + "' is malformed")
	expectedCode = int(testParts.pop())
	resultFile = buildDir + "result"
	if isValidator(cpp):
		inputFile = buildDir + "input"
		with open(inputFile, "w") as f:
			f.write(testParts[0])
		with open(inputFile, "r") as f:
			with open(resultFile, "w") as result:
				realCode = subprocess.call(binOfCpp(cpp), stdin=f, stdout=result)
	else:
		names = (buildDir + "input", buildDir + "output", buildDir + "answer");
		for name, text in zip(names, testParts):
			with open(name, 'w') as f:
				f.write(text)
		realCode = subprocess.call([binOfCpp(cpp)] + list(names) + [resultFile])
		for file in names:
			os.remove(file)
	if realCode != expectedCode:
		log("errors", logLevel, cpp, "expected to return", expectedCode, "but return", realCode, "on", testParts)
	currentLevel = "all" if realCode == expectedCode else "test"
	if needLog(currentLevel, logLevel):
		with open(resultFile) as f:
			print f.read().strip()
	return realCode == expectedCode

def runTestByNumber(cpp, testFile, number, logLevel):
	"""
	:type logLevel: str
	:rtype : bool
	:type cpp: str
	:type testFile: str
	:type number: int
	"""
	return runTest(cpp, getTests(cpp, testFile)[number], logLevel)


def runTestFile(cpp, testFile, logLevel):
	"""
	:type logLevel: str
	:rtype : int
	:type cpp: str
	:type testFile: str
	"""
	log("testset", logLevel, "Start", testFile, "for", cpp)
	errors = 0
	for test in getTests(cpp, testFile):
		if not runTest(cpp, test, logLevel):
			errors += 1
	log("testset", logLevel, errors, "errors in", testFile, "for", cpp)
	return errors


def runAllTests(cpp, logLevel):
	"""
	:type logLevel: str
	:rtype : int
	:type cpp: str
	"""
	log("cpp", logLevel, "Start test", cpp)
	errors = 0
	for testFile in os.listdir(testDir(cpp)):
		errors += runTestFile(cpp, testFile, logLevel)
	log("cpp", logLevel, errors, "errors in", cpp)
	return errors

args = []
logLevel = None

for arg in sys.argv[1:]:
	if arg.startswith("--log="):
		logLevel = arg[6:]
	else:
		args.append(arg)

if len(args) < 1:
	print "Wrong usage"
	sys.exit(1)

if args[0] == '--files':
	errors = 0
	logLevel = logLevel or "errors"
	for cpp in args[1:]:
		errors += runAllTests(cpp, logLevel)
	result = errors == 0
	log("errors", logLevel, errors, "errors in all files")
elif len(args) == 1:
	result = runAllTests(args[0], logLevel or "cpp") != 0
elif len(args) == 2:
	result = runTestFile(args[0], args[1], logLevel or "testset") != 0
elif len(args) == 3:
	logLevel = logLevel or "all"
	result = runTestByNumber(args[0], args[1], int(args[2]), logLevel)
	if result:
		log("errors", logLevel, "Test passed")
else:
	print "Wrong usage"
	sys.exit(1)


if not result:
	sys.exit(1)
