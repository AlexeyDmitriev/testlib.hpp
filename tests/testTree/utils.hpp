#pragma once
#include <algorithm>
#include <vector>
#include <libs/tree/tree.hpp>

using std::vector;
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

void dfsHeight(const Tree& tree, size_t v, vector<size_t>& heights ){
	for (auto to : tree.children(v)){
		heights[to] = heights[v] + 1;
		dfsHeight(tree, to, heights);
	}
}

template<typename T>
void printVector(const vector<T>& a)
{
	for (auto to: a)
		std::cerr << to << " ";
	std::cerr << std::endl;
}

bool isBalancedKTree(const Tree& tree, size_t k){
	if (!isTree(tree))
		return false;
	vector<size_t> heights(tree.size(), 0);
	dfsHeight(tree, tree.getRoot(), heights);
	//printVector(heights);
	size_t maxHeight = *std::max_element(heights.begin(), heights.end());
	size_t qPrevLastLevel = 0;
	for (size_t v = 0; v < tree.size(); v++)
		if (heights[v] != maxHeight)
		{
			if (heights[v] != maxHeight - 1){
				if (tree.children(v).size() != k)
					return false;
			}
			else{
				if (tree.children(v).size() < k && tree.children(v).size() > 0)
					qPrevLastLevel++;
				if (tree.children(v).size() > k)
					return false;		
			}
		}
		else
		{
			if (tree.children(v).size() != 0)
				return false;
		}
	return qPrevLastLevel <= 1;
}

bool isBinaryTree(const Tree& tree){
	if (!isTree(tree))
		return false;
	for (size_t v = 0; v < tree.size(); ++v){
		if (tree.children(v).size() != 0 && tree.children(v).size() != 2)
			return false;
	}
	return true;
}

using std::cerr;
using std::endl;
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
