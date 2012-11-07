#!/usr/bin/python
import sys
import os
import subprocess
buildDir = "build/"
errors = 0
def binOfCpp(cpp):
	"""
	:type cpp: str
	"""
	return buildDir + cpp[:-4] + ".bin"


def isValidator(cpp):
	"""
	:type cpp: str
	"""
	return cpp.startswith("examples/validators");

def processTest(cpp, test):
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
			with open("/dev/null", "w") as null:
				realCode = subprocess.call(binOfCpp(cpp), stdin=f, stdout = null)
	else:
		names = (buildDir + "input", buildDir + "output", buildDir + "answer")
		for name, text in zip(names, testParts):
			with open(name, 'w') as f:
				f.write(text)
		realCode = subprocess.call([binOfCpp(cpp)] + list(names) + ["/dev/null"])
		for file in names:
			os.remove(file)

	if realCode != expectedCode:
		print cpp, "expected to return", expectedCode, "but return", realCode, "on test", testParts, "from", testFile
		return False
	else:
		return True

for cpp in sys.argv[1:]:
	testDir = cpp.rsplit('.', 1)[0] + "/"
	for testFile in os.listdir(testDir):
		with open(testDir + testFile) as handler:
			tests = handler.read().split('```\n')
			for test in tests:
				if not processTest(cpp, test):
					errors += 1


print errors, "errors"
if errors > 0:
	sys.exit(1)
