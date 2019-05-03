    unordered_map<int, Node* > visited;
    Node* cloneGraph(Node* node) {
        if (!node) return NULL;
        Node * clone = new Node(node->val);
        visited[node->val] = clone;
        for (vector<Node*>::iterator it=node->neighbors.begin(); it!=node->neighbors.end(); it++){
            if(visited.find((*it)->val)!=visited.end())clone->neighbors.push_back(visited[(*it)->val]);
            else clone->neighbors.push_back(cloneGraph(*it));
        }
        return clone;
    }
