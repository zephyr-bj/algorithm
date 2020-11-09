/*
 * Insert-Interval.cpp
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
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        int n=intervals.size();
        vector<Interval>ans;
        if(n==0){
            ans.push_back(newInterval);return ans;
        }
        bool inserted=0;
        for(int i=0; i<n; i++){
            if(intervals[i].end<newInterval.start){
                ans.push_back(intervals[i]);
            }else if(intervals[i].start>newInterval.end){
                if(inserted==0){
                    ans.push_back(newInterval);
                    inserted=1;
                }
                ans.push_back(intervals[i]);
            }else{
                if(intervals[i].start<newInterval.start){
                    newInterval.start=intervals[i].start;
                    if(intervals[i].end>newInterval.end){
                        newInterval.end=intervals[i].end;
                    }
                }else{
                    if(newInterval.end<intervals[i].end){
                        newInterval.end=intervals[i].end;
                    }
                }
            }
        }
        if(!inserted)ans.push_back(newInterval);
        return ans;
    }
};
