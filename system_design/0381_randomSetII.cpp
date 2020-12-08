class RandomizedCollection {
public:
    vector<int> v;
    unordered_map<int, unordered_set<int>> m;
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    bool insert(int val) {
        v.push_back(val);
        m[val].insert(v.size() - 1);
        return m[val].size() == 1;
    }
    bool remove(int val) {
        auto it = m.find(val);
        if(it==m.end())return false;

        auto free_pos = *it->second.begin();
        it->second.erase(it->second.begin());
        v[free_pos] = v.back();
        m[v.back()].insert(free_pos);
        m[v.back()].erase(v.size() - 1);
        v.pop_back();
        if (it->second.size() == 0) m.erase(it);
        return true;
    }
    int getRandom() { return v[rand() % v.size()]; }
};
