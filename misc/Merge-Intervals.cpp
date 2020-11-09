/*
 * Merge-Intervals.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Zephyr
 */
#include <vector>
using namespace std;
/**
 * Definition for an interval.
 */
struct Interval {
   int start;
   int end;
   Interval() : start(0), end(0) {}
   Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    static bool cmp(Interval a,Interval b){return (a.start < b.start);}
    vector<Interval> merge(vector<Interval>& intervals) {
        if(intervals.size()==0)return intervals;
        sort(intervals.begin(), intervals.end(), cmp);
        vector<Interval>ans;
        int j=0;
        for(int i=j+1; i<intervals.size(); i++){
            if(intervals[i].start<=intervals[j].end){
                if(intervals[i].end>intervals[j].end){
                    intervals[j].end=intervals[i].end;
                }
            }else{
                ans.push_back(intervals[j]);
                j=i;
            }
        }
        ans.push_back(intervals[j]);
        return ans;
    }
};

