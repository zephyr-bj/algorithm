
/*first solution 252ms, second solution 24ms*/
class Solution {
public:
vector<int> maxVector(vector<int> nums, int k) {
    while (nums.size() > k) {
        int i = 0, n = nums.size();
        for (; i < n - 1; ++i) {
            if (nums[i] < nums[i + 1]) {
                nums.erase(nums.begin() + i);
                break;
            }
        }
        if (i == n - 1) nums.erase(nums.begin() + i);
    }

    return nums;
}

bool compare(vector<int> &nums1, int i, vector<int> &nums2, int j) {
    while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
        ++i;
        ++j;
    }
    if (j == nums2.size()) return true;
    if (i < nums1.size() && nums1[i] > nums2[j]) return true;
    return false;
}

vector<int> merge(vector<int> &nums1, vector<int> &nums2, int k) {
    vector<int> res(k, 0);
    for (int i = 0, j = 0, r = 0; r < k; ++r) {
        res[r] = compare(nums1, i, nums2, j) ? nums1[i++] : nums2[j++];
    }

    return res;
}

vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    int m = nums1.size(), n = nums2.size();
    vector<int> res(k, 0);

    for (int i = max(0, k - n); i <= min(k, m); ++i) {
        auto v1 = maxVector(nums1, i);
        auto v2 = maxVector(nums2, k - i);
        auto tmp = merge(v1, v2, k);
        if (compare(tmp, 0, res, 0)) res = tmp;
    }

    return res;
}
}


/*
class Solution {
public:
    vector<int> maxNumber( const vector<int> & nums1, const std::vector<int> & nums2, int k ) {
        vector<vector<int>> max_nums1( k + 1 );
        generateMaxNums( nums1, max_nums1, k );
        vector<vector<int>> max_nums2( k + 1 );
        generateMaxNums( nums2, max_nums2, k );
        
        vector< int > result;
        for( int len = 0; len <= k; len++ ) {
            const vector<int> & max_num1 = max_nums1[len];
            const vector<int> & max_num2 = max_nums2[k - len];
            if( max_num1.size() + max_num2.size() < k ) {
                continue;
            }
            vector<int> merged = mergeNums(max_num1, max_num2);
            if( result.empty() || result < merged ) {
                result = merged;
            }
        }
        return result;
    }
    
private:
    void generateMaxNums( vector<int> nums, vector<vector<int>> & max_nums, int k ) {
        int pos = 0;
        while( !nums.empty() ) {
            if( nums.size() <= k ) {
                max_nums[nums.size()] = nums;
            }
            while(pos < nums.size() - 1 && nums[pos] >= nums[pos + 1] ) {
                pos++; // skip it, we need to drop smaller prior to the next
            }
            nums.erase( nums.begin() + pos );
            if( pos > 0 ) {
                pos--;
            }
        }
    }
    
    vector<int> mergeNums( const vector<int> & nums1, const vector<int> & nums2 ) {
        int idx1 = 0;
        int idx2 = 0;
        std::vector< int > merged;
        while( idx1 < nums1.size() && idx2 < nums2.size() ) {
            if( nums1[ idx1 ] < nums2[ idx2 ] ) {
                merged.push_back( nums2[ idx2++ ] );
            } else if( nums2[ idx2 ] < nums1[ idx1 ] ){
                merged.push_back( nums1[ idx1++ ] );
            } else {
                bool take_num2 = nums1.size() - idx1 < nums2.size() - idx2;
                for( int i1 = idx1, i2 = idx2; i1 < nums1.size() && i2 < nums2.size(); i1++, i2++ ) {
                    if( nums1[ i1 ] == nums2[ i2 ] ) {
                        continue;
                    }
                    take_num2 = nums1[ i1 ] < nums2[ i2 ];
                    break;
                }
                if( take_num2 ) {
                    merged.push_back( nums2[ idx2++ ] );
                } else {
                    merged.push_back( nums1[ idx1++ ] );
                }
            }
        }
        while( idx1 < nums1.size() ) {
            merged.push_back( nums1[ idx1++ ] );  
        }
        while( idx2 < nums2.size() ) {
            merged.push_back( nums2[ idx2++ ] );  
        }
        return merged;
    }
};
*/
