#pragma once
#include <vector>
#include <cassert>
#include "random.hpp"
#include <iostream>
#include "testlib/generator.hpp"
#include "testlib/generators/int.hpp"
namespace tree
{
using std::vector;

class Tree{
public:
	Tree(const vector<int>& parents){
		graph.resize(parents.size());
		parent = parents;
		for (size_t i = 0; i < parents.size(); ++i)
			if (parents[i] == (int)i || parents[i] == -1)
				root = i;
			else
				graph[parents[i]].push_back(i);
	}
	
	Tree(const vector<vector<size_t> >& _graph, size_t _root = 0){
		graph.resize(_graph.size());
		parent.resize(_graph.size());
		root = _root;
		parent[_root] = -1;
		vector<char> used(_graph.size(), false);
		dfsToOrderVertices(_graph, used, root);
	}
	
	Tree(const vector<std::pair<size_t, size_t> > edges, size_t _root = 0){
		vector<vector<size_t>> g;
		g.resize(edges.size() + 1);
		for (size_t i = 0; i < edges.size(); ++i) {
			g[edges[i].first].push_back(edges[i].second);
			g[edges[i].second].push_back(edges[i].first);
		}
		*this = Tree(g, _root);
	}
	
	Tree() {}
	
	const vector<size_t>& children(size_t vertex) const{
		return graph[vertex];
	}
	
	size_t getRoot() const{
		return root;
	}
	
	bool isRoot(size_t vertex) const{
		return vertex == root;
	}
	
	Tree rehang(size_t newRoot) const ;
	
	
	size_t size() const{
		return parent.size();
	}
	
	int getParent(size_t vertex) const{
		return parent[vertex];
	}
	
private:
	vector<vector<size_t> > graph;
	vector<int> parent;
	size_t root;
	void dfsToOrderVertices(const vector<vector<size_t> >& g, vector<char>& used, size_t vertex){
		used[vertex] = true;
		for (auto to : g[vertex]){
			if (!used[to]){
				parent[to] = vertex;
				graph[vertex].push_back(to);
				dfsToOrderVertices(g, used, to);
			}
		}
	}
};

inline vector<vector<size_t> > treeToGraph(const Tree& tree);
inline Tree shuffle(const Tree& tree, Random& rnd);
inline Tree makeParentsIdLess(const Tree& tree);
	
inline void dfsToRenumerate(const Tree& tree, size_t vertex, vector<size_t>& resultsPermutation, size_t usedNumbers){ //hide in namespace
	resultsPermutation[vertex] = usedNumbers++;
	for (size_t to: tree.children(vertex))
		dfsToRenumerate(tree, to, resultsPermutation, usedNumbers);
}	
	

Tree Tree::rehang(size_t newRoot) const { // we want const method, but it is hard to realize
	vector<vector<size_t>> g = treeToGraph(*this);	
	Tree resultTree(g, newRoot);
	return resultTree;
}	

inline Tree renumerateVertices(const Tree& tree, vector<size_t> permutation){
	vector<vector<size_t>> g = treeToGraph(tree);
	for (size_t v = 0; v < g.size(); ++v)
		for (size_t& to : g[v])
			to = permutation[to];
	vector<vector<size_t>> resG(g.size(), vector<size_t>());
	for (size_t v = 0; v < g.size(); ++v)
		resG[permutation[v]] = g[v];
	return Tree(resG);
}

inline Tree shuffle(const Tree& tree, Random& rnd) { // don't change root
	vector<size_t> permutation(tree.size());
	for (size_t i = 0; i < permutation.size(); ++i) 
		permutation[i] = i;
	rnd.shuffle(permutation.begin(), permutation.end());
	for (size_t i = 0; i < permutation.size(); ++i)
		if (permutation[i] == tree.getRoot()){
			std::swap(permutation[i], permutation[tree.getRoot()]);
			break;
		}
	return renumerateVertices(tree, permutation);
}

inline vector<vector<size_t> > treeToGraph(const Tree& tree){
	vector<vector<size_t> > g(tree.size());
	for (size_t v = 0; v < tree.size(); v++)
		for (auto to : tree.children(v)){
			g[v].push_back(to);
			g[to].push_back(v);
		}
	return g;
}

inline Tree makeParentsIdLess(const Tree& tree){
	vector<size_t> permutation(tree.size());
	dfsToRenumerate(tree, tree.getRoot(), permutation, 0);
	return renumerateVertices(tree, permutation);
}


}

template<>
class DefaultGenerator<tree::Tree> : public Generator<tree::Tree>{
public:
	
	tree::Tree generate(Random& rnd, size_t numberVertices) const {
		std::vector<std::pair<size_t, size_t> > edges(numberVertices - 1);
		for (size_t i = 1; i < numberVertices; i++)
			edges[i - 1] = std::make_pair(i, rnd.next<int>(0, i - 1));
		tree::Tree tree = tree::Tree(edges);
		tree = tree.rehang(rnd.next<int>(0, numberVertices - 1));
		tree = tree::shuffle(tree, rnd);
		return tree;
	}
};

class BambooTreeGenerator : public Generator<tree::Tree>{
public:
	tree::Tree generate(Random& rnd, size_t numberVertices) const {
		std::vector<std::pair<size_t, size_t> > edges(numberVertices - 1);
		for (size_t i = 1; i < numberVertices; i++)
			edges[i - 1] = std::make_pair(i, i - 1);
		tree::Tree tree = tree::Tree(edges);
		tree = tree.rehang(rnd.next<int>(0, numberVertices - 1));
		tree = tree::shuffle(tree, rnd);
		return tree;
	}
};
