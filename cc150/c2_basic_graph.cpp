#include<iostream>
#include <list>
#include <vector>
#include <map>

//DFS of a m-arry in non-recursive manner without using extra memory.????
 
using namespace std;
 
// Graph class represents a directed graph using adjacency list representation
class Graph
{
    int N;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    void DFSUtil(int v, bool visited[]);  // A function used by DFS
	bool isCyclicUtil(int v, bool visited[], bool *rs);  // used by isCyclic()
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void DFS(int v);    // DFS traversal of the vertices reachable from v
	void BFS(int s);
	void DFS_Full(); // prints DFS traversal of the complete graph
	bool isCyclic();    // returns true if there is a cycle in this graph
};
 
Graph::Graph(int V)
{
    this->N = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            DFSUtil(*i, visited);
}
 
// DFS traversal of the vertices reachable from v. It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[N];
    for(int i = 0; i < N; i++)
        visited[i] = false;
 
    // Call the recursive helper function to print DFS traversal
    DFSUtil(v, visited);
}

// The function to do DFS traversal. It uses recursive DFSUtil()
void Graph::DFS_Full()
{
    // Mark all the vertices as not visited
    bool *visited = new bool[N];
    for(int i = 0; i < N; i++)
        visited[i] = false;
 
    // Call the recursive helper function to print DFS traversal
    // starting from all vertices one by one
    for(int i = 0; i < N; i++)
        if(visited[i] == false)
            DFSUtil(i, visited);
}

void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[N];
    for(int i = 0; i < N; i++)
        visited[i] = false;
    // Create a queue for BFS
    list<int> queue;
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
    // 'i' will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;
    while(!queue.empty()){
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(i = adj[s].begin(); i != adj[s].end(); ++i){
            if(!visited[*i]){
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

// This function is a variation of DFSUytil() 
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if(visited[v] == false){
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i){
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                return true;
            else if (recStack[*i])
                return true;
        } 
    }
    recStack[v] = false;  // remove the vertex from recursion stack
    return false;
}
 
// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() 
bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    bool *visited = new bool[N];
    bool *recStack = new bool[N];
    for(int i = 0; i < N; i++){
        visited[i] = false;
        recStack[i] = false;
    }
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for(int i = 0; i < N; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;
 
    return false;
}
 
int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Depth First Traversal (starting from vertex 2) \n";
    g.DFS(2);
 
    return 0;
}


/**
 * Definition for undirected graph.*/
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};
 
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL) return NULL;
        UndirectedGraphNode * root = new UndirectedGraphNode(node->label);
        list<UndirectedGraphNode *> iQueue;
        list<UndirectedGraphNode *> oQueue;
        map<int,UndirectedGraphNode *> created;
        created.insert(pair<int,UndirectedGraphNode *>(node->label,root));
        iQueue.push_back(node);
        oQueue.push_back(root);
        while(!iQueue.empty()){
            UndirectedGraphNode * a = iQueue.front();
            UndirectedGraphNode * b = oQueue.front();
            b->neighbors.resize(a->neighbors.size());
            for(int i = 0; i<a->neighbors.size();i++){
                if(created.find(a->neighbors[i]->label) == created.end() ){
                    iQueue.push_back(a->neighbors[i]);
                    UndirectedGraphNode * tmp = new UndirectedGraphNode(a->neighbors[i]->label);
                    created.insert(pair<int,UndirectedGraphNode *>(a->neighbors[i]->label,tmp));
                    oQueue.push_back(tmp);
                }
                b->neighbors[i] = created[a->neighbors[i]->label];
            }
            iQueue.pop_front();
            oQueue.pop_front();
        }
        return root;
    }
};
