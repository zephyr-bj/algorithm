/* cache [2] : (0146) LRU cache (0460) LFU cache
 * radomized set [2] : (0380) randomized set (0381) randomized collection
 * tweeter [1] : (0355) tweeter
 */
// (0146) LRU cache
/* 1 list of key and value pairs; 1 dict from key to list pointer
 * get: 1. push the fetched pair to list head
 *      2. remove the existing fetched pair
 *      3. update the list pointer
 * put: 1. remove the existing fetched pair
 *      2. push the a new pair to list head
 *      3. update the list pointer
 *      4. if size overflow, pop the list end
 */
class LRUCache {
public:
    list<pair<int,int>>cache;
    unordered_map<int,list<pair<int,int>>::iterator>dict;
    int cap;
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if(dict.count(key)){
            int x = dict[key]->second;
            cache.push_front(*dict[key]);
            cache.erase(dict[key]);
            dict[key]=cache.begin();
            return x;
        }else{
            return -1;
        }
    }
    
    void put(int key, int value) {
        if(dict.count(key))cache.erase(dict[key]);
        cache.push_front(pair<int,int>({key,value}));
        dict[key]=cache.begin();
        if(cache.size()>cap){
            dict.erase(cache.back().first);
            cache.pop_back();
        }
    }
};

// (0460) LFU
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

// (0380) randomized set
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
// (0381) randomized collection
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

// (0355) tweeter
class Twitter {
private:    
   unordered_map<int, unordered_set<int>> fo;
   unordered_map<int, vector<pair<int, int>>> t;
   long long time; 

public:
/** Initialize your data structure here. */
Twitter() {
    time = 0;
}

/** Compose a new tweet. */
void postTweet(int userId, int tweetId) {
    t[userId].push_back({time++, tweetId});
}

/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
vector<int> getNewsFeed(int userId) {
    priority_queue<pair<int, int>> maxHeap; 
    for (auto it=t[userId].begin();it!=t[userId].end();++it)
        maxHeap.push(*it);
    for (auto it1=fo[userId].begin();it1!=fo[userId].end();++it1){
        int usr = *it1; // get target user
        for (auto it2=t[usr].begin();it2!=t[usr].end();++it2)
            maxHeap.push(*it2);
    }   
    vector<int> res;
    while(maxHeap.size()>0) {
        res.push_back(maxHeap.top().second);
        if (res.size()==10) break;
        maxHeap.pop();
    }
    return res;
}

/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
void follow(int followerId, int followeeId) {
    if (followerId != followeeId)
        fo[followerId].insert(followeeId);
}

/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
void unfollow(int followerId, int followeeId) {
    fo[followerId].erase(followeeId);
}
