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
