/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
class Solution {
public:
    unordered_map<Node*,Node*>visited;
    Node* cloneGraph(Node* node) {
        if(node==NULL)return NULL;
        if(visited.find(node)!=visited.end())return visited[node];
        Node* x = new Node(node->val);
        visited[node]=x;
        for(auto nn:node->neighbors){
            x->neighbors.push_back(cloneGraph(nn));
        }
        return x;
    }
};
