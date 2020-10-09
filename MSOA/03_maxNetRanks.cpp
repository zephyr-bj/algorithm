int maxNetRanks(vector<int>&A, vector<int>&B, int N){
    int M = A.size();
    vector<int>cities(N+1,0);
    for(int i=0; i<M; i++){
        cities[A[i]]++;
        cities[B[i]]++;
    }
    int ans = 0;
    for(int i=0; i<M; i++){
        ans = max(ans, cities[A[i]]+cities[B[i]]-1);
    }
    return ans;
}
