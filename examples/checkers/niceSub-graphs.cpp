#include "testlib.hpp"
#include <vector>
#include <iostream>
#include <set>
using namespace std;
const int MAXN = 100000;
const int MAXM = 200000;

vector< vector<int> > graph;
vector<char> color;

bool dfs(int v){
	for (size_t i = 0; i < graph[v].size(); i++){
		int to = graph[v][i];
		if (color[to] == color[v])
			return false;
		if (color[to] == 0){
			color[to] = 3 - color[v];
			if (!dfs(to))
				return false;
		}
	}
	return true;
}

struct Edge{
	int u, v;
	Edge() {}
	Edge(int u, int v): u(u), v(v) {}
	bool operator < (const Edge& edge) const{
		return make_pair(u, v) < make_pair(edge.u, edge.v);
	}
	
};

class ReaderEdge : Reader<Edge>{
public:
	ReaderEdge(int n): n(n) {}
	
	Edge read(IStream& stream){
		int u = stream.read<int>(1, n);
		int v = stream.read<int>(1, n);
		u--, v--;
		if (u > v) swap(u, v);
		return Edge(u, v);
	}
private:
	int n;
};

TESTLIB_CHECK(){
	int n = inf.read<int>(1, MAXN);
	int m = inf.read<int>(0, MAXM);
	set<Edge> inputEdges, foundEdges;
	ReaderEdge ourReader(n);
	for (int i = 0; i < m; i++){
		Edge edge = inf.read<Edge>(ourReader);
		ensure(edge.u != edge.v);
		ensure(inputEdges.find(edge) == inputEdges.end());
		inputEdges.insert(edge);
	}
	string res = ouf.readToken();
	if (res != "YES" && res != "NO")
		PE(expectation("YES or NO", res));
	int q = ouf.read<int>((m + 1) / 2, m);
	graph.assign(n, vector<int>());
	
	for (int i = 0; i < q; i++){
		Edge edge = ouf.read<Edge>(ourReader);
		if (inputEdges.find(edge) == inputEdges.end())
			WA("Edge " << edge.u <<  " " << edge.v << " isn't exist in input graph");
		if (foundEdges.find(edge) != foundEdges.end())
			WA("Edge " << edge.u <<  " " << edge.v << " musn't be a multiple edge");
		foundEdges.insert(edge);
		graph[edge.u].push_back(edge.v);
		graph[edge.v].push_back(edge.u);
	}
	color.assign(n, 0);
	for (int i = 0; i < n; i++)
		if (color[i] == 0){
			color[i] = 1;
			if (!dfs(i)){
				WA("Graph isn't bipartite");
			}
		}
}
