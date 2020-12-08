class LFUCache {
    /*
     * 1 frequency lists table; 1 dict from key to value-freq pair ; 1 dict from key to list pointer
     * get 1: remove from the old freq list 
     *     2: increase the key frequency
     *     3: push in the new freq list
     *     4: save the pointer to the new freq list
     *     5: increase the minFreq if the current minFreq list empty
     * put 1: call get
     *     2: reset the value if key found
     *     3: in case not found and overflow, remove one key from the minFreq list
     *     4: in case not found, save the new value, push to freq=1 list, save the pointer
     *     5: minFreq = 1; increase size. 
    */
    int cap;
    int size;
    int minFreq;
    unordered_map<int, pair<int, int>> m; //key to {value,freq};
    unordered_map<int, list<int>::iterator> mIter; //key to list iterator;
    unordered_map<int, list<int>>  fm;  //freq to key list;
public:
    LFUCache(int capacity) {
        cap=capacity;
        size=0;
    }
    
    int get(int key) {
        if(m.count(key)==0) return -1;
        
        fm[m[key].second].erase(mIter[key]);
        m[key].second++;
        fm[m[key].second].push_back(key);
        mIter[key]=--fm[m[key].second].end();
        
        if(fm[minFreq].size()==0 ) 
              minFreq++;
        
        return m[key].first;
    }
    
   void set(int key, int value) {
        if(cap<=0) return;
        
        int storedValue=get(key);
        if(storedValue!=-1)
        {
            m[key].first=value;
            return;
        }
        
        if(size>=cap )
        {
            m.erase( fm[minFreq].front() );
            mIter.erase( fm[minFreq].front() );
            fm[minFreq].pop_front();
            size--;
        }
        
        m[key]={value, 1};
        fm[1].push_back(key);
        mIter[key]=--fm[1].end();
        minFreq=1;
        size++;
    }
};
