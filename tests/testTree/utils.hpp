#pragma once
#include <libs/tree/tree.hpp>
using namespace std;
using namespace tree;

bool dfsCheckNoCycle(const vector<vector<size_t> >& graph, size_t v, vector<char>& used, int parent = -1){
	used[v] = true;
	for (auto to : graph[v])
		if ((int)to != parent){
			if (used[to])
				return false;
			bool res = dfsCheckNoCycle(graph, to, used, (int)v);
			if (!res) 
				return false;
		}
	return true;
}

bool isTree(const Tree& tree){
	vector<vector<size_t> > graph = treeToGraph(tree);
	vector<char> used(tree.size(), false);
	bool hasNoCycle = dfsCheckNoCycle(graph, tree.getRoot(), used);
	if (!hasNoCycle) return false;
	for (size_t v = 0; v < tree.size(); ++v)
		if (!used[v])
			return false;
	return true;
}

void printTree(const Tree& tree)
{
	cerr << tree.getRoot() << endl;
	for (size_t v = 0; v < tree.size(); ++v){
		cerr << v << endl;
		for (auto x : tree.children(v))
			cerr << x << " ";
		cerr << endl;
	}
	cerr << endl;
}
