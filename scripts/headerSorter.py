#!/usr/bin/python
import sys
import os

used = set();

def go(oldFile, path):
	relative = os.path.dirname(oldFile) + '/' + path
	if os.path.exists(relative):
		return relative
	else:
		return path

def dfs(file):
	if file in used:
		return
	used.add(file)
	if os.path.isdir(file):
		for inner in os.listdir(file):
			dfs(file + '/' + inner)
	else:
		with open(file, "r") as f:
			for line in f:
				if line.startswith("#include \""):
					dfs(go(file, line[8:].strip("\n\r \"")))
				else:
					print line,

for file in sys.argv[1:]:
	dfs(file)
