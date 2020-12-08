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
