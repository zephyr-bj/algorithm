class RandomizedSet {
public:
    /** Initialize your data structure here. */
    unordered_map<int,int>setr;
    vector<int>vr;
    RandomizedSet() {
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(setr.find(val)!=setr.end())return false;
        setr[val]=vr.size();
        vr.push_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(setr.find(val)==setr.end())return false;
        int idx = vr.size()-1;
        if(setr[val]!=idx){
            vr[setr[val]]=vr[idx];
            setr[vr[idx]]=setr[val];
        }
        vr.pop_back();
        setr.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int x = rand() % vr.size();
        return vr[x];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
