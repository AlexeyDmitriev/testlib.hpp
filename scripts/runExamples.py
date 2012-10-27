#!/usr/bin/python
import sys
import os
import subprocess
buildDir = "build/"
errors = 0
def binOfCpp(cpp):
	return buildDir + cpp[:-4] + ".bin"
for cpp in sys.argv[1:]:
	testDir = cpp.rsplit('.', 1)[0] + "/"
	for testFile in os.listdir(testDir):
		with open(testDir + testFile) as handler:
			tests = handler.read().split('```\n')
			for test in tests:
				testParts = test.split('`\n')
				if len(testParts) != 4:
					raise SyntaxError("test '" + str(testParts) + "' is malformed")
				names = (buildDir + "input", buildDir + "output", buildDir + "answer")
				expectedCode = int(testParts.pop())
				for name, text in zip(names, testParts):
					with open(name, 'w') as f:
						f.write(text)
				realCode = subprocess.call([binOfCpp(cpp)] + list(names) + ["/dev/null"]);
				if realCode != expectedCode:
					print cpp, "expected to return", expectedCode, "but return", realCode, "on test", testParts, "from", testFile
					errors = errors + 1
				for file in names:
					os.remove(file)

print errors, "errors"
if errors > 0:
	sys.exit(1)
