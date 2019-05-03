    unordered_map<int, Node* > m;
    Node* cloneGraph(Node* node) {
        if (!node) return NULL;
        auto clone = new Node(node->val);
        m[node->val] = clone;
        for (auto nb : node->neighbors) 
            clone->neighbors.push_back(m.count(nb->val) ? m[nb->val] : cloneGraph(nb) );
        return clone;
    }
