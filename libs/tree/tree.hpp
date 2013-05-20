#pragma once
#include <iostream>
#include <vector>
#include "testlib/generator.hpp"
#include "testlib/generators/int.hpp"
#include "testlib/random.hpp"

namespace tree
{
using std::vector;

class Tree{
public:
	Tree(const vector<int>& parents) {
		graph.resize(parents.size());
		parent = parents;
		for (size_t i = 0; i < parents.size(); ++i)
			if (parents[i] == -1)
				root = i;
			else
				graph[parents[i]].push_back(i);
	}
	
	Tree(const vector<vector<size_t> >& graph, size_t root = 0): graph(graph.size()), parent(graph.size()), root(root) {
		parent[root] = -1;
		vector<char> used(graph.size(), false);
		dfsToOrderVertices(graph, used, root);
	}

	Tree(const vector<std::pair<size_t, size_t> >& edges, size_t _root = 0): Tree(edgesListToGraph(edges), _root) {}
	
	const vector<size_t>& children(size_t vertex) const {
		return graph[vertex];
	}
	
	size_t getRoot() const {
		return root;
	}
	
	bool isRoot(size_t vertex) const {
		return vertex == root;
	}
	
	Tree rehang(size_t newRoot) const;
	
	
	size_t size() const {
		return parent.size();
	}
	
	int getParent(size_t vertex) const {
		return parent[vertex];
	}
	
private:
	vector<vector<size_t> > graph;
	vector<int> parent;
	size_t root;
	void dfsToOrderVertices(const vector<vector<size_t> >& g, vector<char>& used, size_t vertex) {
		used[vertex] = true;
		for (auto to : g[vertex]) {
			if (!used[to]) {
				parent[to] = vertex;
				graph[vertex].push_back(to);
				dfsToOrderVertices(g, used, to);
			}
		}
	}
	
	static vector<vector<size_t> > edgesListToGraph(const vector<std::pair<size_t, size_t> >& edges) {
		vector<vector<size_t> > g;
		g.resize(edges.size() + 1);
		for (size_t i = 0; i < edges.size(); ++i) {
			g[edges[i].first].push_back(edges[i].second);
			g[edges[i].second].push_back(edges[i].first);
		}
		return g;
	}
};

inline vector<vector<size_t> > treeToGraph(const Tree& tree);
inline Tree shuffle(const Tree& tree, Random& rnd);
inline Tree makeParentsIdLess(const Tree& tree);

namespace utils{
inline void dfsToRenumerate(const Tree& tree, size_t vertex, vector<size_t>& resultsPermutation, size_t& usedNumbers) {
	resultsPermutation[vertex] = usedNumbers++;
	for (size_t to: tree.children(vertex))
		dfsToRenumerate(tree, to, resultsPermutation, usedNumbers);
}	
} //namespace utils ended
	

Tree Tree::rehang(size_t newRoot) const {
	vector<vector<size_t>> g = treeToGraph(*this);
	Tree resultTree(g, newRoot);
	return resultTree;
}	

inline Tree renumerateVertices(const Tree& tree, vector<size_t> permutation) {
	size_t oldRoot = tree.getRoot();
	vector<vector<size_t>> g = treeToGraph(tree);
	for (size_t v = 0; v < g.size(); ++v)
		for (auto& to : g[v])
			to = permutation[to];
	vector<vector<size_t>> resG(g.size(), vector<size_t>());
	for (size_t v = 0; v < g.size(); ++v)
		resG[permutation[v]] = g[v];
	return Tree(resG, permutation[oldRoot]);
}

inline Tree shuffle(const Tree& tree, Random& rnd) {
	vector<size_t> permutation(tree.size());
	for (size_t i = 0; i < permutation.size(); ++i) 
		permutation[i] = i;
	rnd.shuffle(permutation.begin(), permutation.end());
	return renumerateVertices(tree, permutation);
}

inline vector<vector<size_t> > treeToGraph(const Tree& tree) {
	vector<vector<size_t> > g(tree.size());
	for (size_t v = 0; v < tree.size(); v++)
		for (auto to : tree.children(v)) {
			g[v].push_back(to);
			g[to].push_back(v);
		}
	return g;
}

inline Tree makeParentsIdLess(const Tree& tree) {
	vector<size_t> permutation(tree.size());
	size_t qUsedVertices = 0;
	utils::dfsToRenumerate(tree, tree.getRoot(), permutation, qUsedVertices);
	return renumerateVertices(tree, permutation);
}


}// end of namespace tree

template<>
class DefaultGenerator<tree::Tree> : public Generator<tree::Tree> {
public:
	
	tree::Tree generate(Random& rnd, size_t numberVertices, double coefHeight = 1.0) const {
		if (coefHeight < 0.0 || coefHeight > 1.0)
			throw VerdictException(Verdict::FAIL, "DefaultGenerator<Tree> coefficient of height should be from 0.0 to 1.0");
		std::vector<std::pair<size_t, size_t> > edges(numberVertices - 1);
		for (size_t i = 1; i < numberVertices; i++) {
			size_t to = rnd.next<size_t>(0, i - 1) * coefHeight; 
			edges[i - 1] = std::make_pair(i, to);
		}
		tree::Tree tree = tree::Tree(edges);
		tree = tree::shuffle(tree, rnd);
		return tree;
	}
};

class BambooGenerator : public Generator<tree::Tree> {
public:
	tree::Tree generate(Random& rnd, size_t numberVertices) const {
		std::vector<std::pair<size_t, size_t> > edges(numberVertices - 1);
		for (size_t i = 1; i < numberVertices; i++)
			edges[i - 1] = std::make_pair(i, i - 1);
		tree::Tree tree = tree::Tree(edges);
		tree = tree::shuffle(tree, rnd);
		return tree;
	}
};

class BinaryTreeGenerator : public Generator<tree::Tree> {
public:
	tree::Tree generate(Random& rnd, size_t numberVertices) const {
		if (numberVertices % 2 == 0)
			throw VerdictException(Verdict::FAIL, "BinaryTreeGenerator: numberVertices is even");
		
		std::vector<std::pair<size_t, size_t> > edges; 
		edges.reserve(numberVertices - 1);
		std::vector<size_t> curLevel, nextLevel;
		curLevel.push_back(0); 
		size_t qProcessed = 1;
		while (qProcessed != numberVertices) {
			bool isList = true;
			for (size_t i = 0; i < curLevel.size(); i++)
				if (rnd.nextBit()) {
					size_t v = curLevel[i];
					for (size_t j = 0; j < 2 && qProcessed < numberVertices; j++) {
						edges.push_back(std::make_pair(v, qProcessed));
						nextLevel.push_back(qProcessed);
						qProcessed++;
						isList = false;
					}
				}
			if (isList) {
				size_t v = curLevel[0];
				for (size_t j = 0; j < 2 && qProcessed < numberVertices; j++) {
					edges.push_back(std::make_pair(v, qProcessed));
					nextLevel.push_back(qProcessed);
					qProcessed++;
				}
			}
			curLevel = nextLevel;
			nextLevel.clear();
		}
		tree::Tree tree = tree::Tree(edges);
		tree = tree::shuffle(tree, rnd);
		return tree;
	}
};

class BalancedKTreeGenerator : public Generator<tree::Tree> {
public:
	tree::Tree generate(Random& rnd, size_t numberVertices, size_t vertexDegree) const {
		if (vertexDegree == 0)
			throw VerdictException(Verdict::FAIL, "BalancedKTreeGenerator: vertexDegree = 0");
		std::vector<std::pair<size_t, size_t> > edges(numberVertices - 1);
		for (size_t i = 1; i < numberVertices; i++)
			edges[i - 1] = std::make_pair(i , (i - 1) / vertexDegree);
		tree::Tree tree = tree::Tree(edges);
		tree = tree::shuffle(tree, rnd);
		return tree;
	}
};

class FluffyBambooGenerator : public Generator<tree::Tree> {
public:
	tree::Tree generate(Random& rnd, size_t numberVertices) const {
		std::vector<std::pair<size_t, size_t> > edges(numberVertices - 1);
		size_t bambooSize = rnd.next<size_t>(1, numberVertices);
		for (size_t i = 1; i < bambooSize; i++)
			edges[i - 1] = std::make_pair(i, i - 1);
		for (size_t i = bambooSize; i < numberVertices; i++)
			edges[i - 1] = std::make_pair(i, rnd.next<size_t>(0, bambooSize - 1));
		tree::Tree tree = tree::Tree(edges);
		tree = tree::shuffle(tree, rnd);
		return tree;
	}
};
