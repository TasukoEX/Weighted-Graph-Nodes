/*
* Dante Ebanks
* DS_Project_3_Ebanks.cpp
* COP4415.02
* 12/8/2022
*/

#include <iostream>
#include <utility>
#include <list>
#include <queue>
using namespace std;


#define INF 1000

class Graph{
	// Number of vertices
	int V;
	// Adjacency list representation
	// Pair of a neighbor vertex  and a weight for every edge
	list< pair<int, int> >* adj;
public:
	Graph(int V);
	// Function to add an edge to graph
	void addEdge(int u, int v, int w);
	// Print MST using Prim's algorithm
	void primMST();
};
// Allocates memory for adjacency list
Graph::Graph(int V){
	this->V = V;
	adj = new list< pair<int, int>>[V];
}

void Graph::addEdge(int u, int v, int w) {

	//Push the edges  onto the adj list (both ways)
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

void  Graph::primMST() {

	// Instantiate the priority queue for vectors and pairs of vertices
	priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;

	// Initial condition
	int src = 0;

	// Stores parent nodes
	vector<int> parent(V, -1);

	// Keep track of vertices that are already included in MST
	vector<bool> inMST(V, false);

	// Instantiate the vertices to have the value of INF
	vector<int> value(V, INF);

	// Initialize the index and insert it as source
	pq.push(make_pair(0, src));
	value[src] = 0;

	// Loop until priority queue is empty
	while (!pq.empty())
	{
		// Extract the minimum value vertex from priority queue.
		// Vertex label is stored in the second pair
		int u = pq.top().second;
		pq.pop();

		// Different values for same vertex exist in the priority queue.
		// The one with the least value is always first (continue if true already)
		if (inMST[u] == true) {
			continue;
		}

		inMST[u] = true;

		list< pair<int, int> >::iterator i;

		// Iterate through the adj array 
		for (i = adj[u].begin(); i != adj[u].end(); ++i){
			// Get vertex and weight of adjacent
			int v = (*i).first;
			int weight = (*i).second;

			//  If v is not in MST and weight of (u,v) is smaller than current value...
			if (inMST[v] == false && value[v] > weight)
			{
				// Instantiate the variables
				value[v] = weight;
				pq.push(make_pair(value[v], v));
				parent[v] = u;
			}
		}
	}

	// Output using parent array
	for (int i = 1; i < V; ++i)
		cout << parent[i] << " - " << i << endl;
}

int main() {

	int V = 8;
	Graph g(V);

	g.addEdge(0, 1, 5);
	g.addEdge(0, 4, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 7, 2);
	g.addEdge(3, 6, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 3);
	g.primMST();

	return 0;
}