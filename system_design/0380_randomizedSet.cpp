class RandomizedSet {
public:
    /** Initialize your data structure here. */
    unordered_map<int,int>setr;
    vector<int>vr;
    int n;
    RandomizedSet() {
        n=0;
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(setr.find(val)==setr.end()){
            setr[val]=n;
            vr.push_back(val);
            n++;
            return true;
        }
        return false;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(setr.find(val)!=setr.end()){
            n--;
            if(setr[val]==n){
                vr.pop_back();
                setr.erase(val);
            }else{
                vr[setr[val]]=vr[n];
                setr[vr[n]]=setr[val];
                vr.pop_back();
                setr.erase(val);
            }
            return true;
        }
        return false;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int x = rand() % n;
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
