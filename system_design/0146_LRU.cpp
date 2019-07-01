class LRUCache {
public:
    int depth;
list<vector<int>>que;
unordered_map<int, list<vector<int>>::iterator>proj;

    LRUCache(int capacity) {
        depth=capacity;
    }
    
    int get(int key) {
        if(proj.find(key)==proj.end()){
            return -1;
        }else{
            vector<int>pair=*proj[key];
            que.erase(proj[key]);
            que.push_front(pair);
            proj[key]=que.begin();
            return pair[1];
        }    
    }
    
    void put(int key, int value) {
        if(proj.find(key)==proj.end()){
            if(que.size()==depth){
                proj.erase(proj.find(que.back()[0]));
                que.pop_back();
            }
        }else{
            que.erase(proj[key]);
        }
        vector<int>pair(2,key);
        pair[1]=value;
        que.push_front(pair);
        proj[key]=que.begin();
    }
};
