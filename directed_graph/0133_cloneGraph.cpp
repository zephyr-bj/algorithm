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
    unordered_map<Node*,Node*>bin;
    Node* cloneGraph(Node* node) {
        if(node==NULL)return NULL;
        if(bin.find(node)!=bin.end())return bin[node];
        int n = node->neighbors.size();
        vector<Node*>br(n,NULL);
        Node * newnode = new Node(node->val, br);
        bin[node]=newnode;

        for(int i=0; i<n; i++){
            if(node->neighbors[i]!=NULL)newnode->neighbors[i] = cloneGraph(node->neighbors[i]);
        }
        return newnode;
    }
};
