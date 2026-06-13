#include<bits/stdc++.h>
using namespace std;

//01. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS                     {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        unordered_map<int,int>mp;
        int maxLen = 0;
        int i = 0, j = 0;
        while(j < n){
            mp[s[j]]++;

            while(mp[s[j]] > 1){
                mp[s[i]]--;

                if(mp[s[i]] == 0) mp.erase(s[i]);
                i++;
            }
            maxLen = max(maxLen, j-i+1);
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/


//02. MAXIMUM SUM OF DISTINCT SUBARRAYS WITH LENGTH K                      {T.C = O(N), S.C = O(K)}
class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int>mp;
        long long maxSum = 0, sum = 0;
        int i = 0, j = 0;
        while(j < n){
            mp[nums[j]]++;
            sum += nums[j];

            if(j-i+1 == k){
                if(mp.size() == k) maxSum = max(maxSum, sum);

                sum -= nums[i];
                mp[nums[i]]--;
                if(mp[nums[i]] == 0) mp.erase(nums[i]);
                i++;
            }
            j++;
        }
        return maxSum;
    }
};
/*
Example 1:
Input: nums = [1,5,4,2,9,9,9], k = 3
Output: 15
Explanation: The subarrays of nums with length 3 are:
- [1,5,4] which meets the requirements and has a sum of 10.
- [5,4,2] which meets the requirements and has a sum of 11.
- [4,2,9] which meets the requirements and has a sum of 15.
- [2,9,9] which does not meet the requirements because the element 9 is repeated.
- [9,9,9] which does not meet the requirements because the element 9 is repeated.
We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions

Example 2:
Input: nums = [4,4,4], k = 3
Output: 0
Explanation: The subarrays of nums with length 3 are:
- [4,4,4] which does not meet the requirements because the element 4 is repeated.
We return 0 because no subarrays meet the conditions.
*/


//03. LONGEST SUBSTRING WITH K UNIQUES                                      {T.C = O(N), S.C = O(K)}
class Solution {
public:
    int longestKSubstr(string &s, int k) {
        int n = s.length();
        unordered_map<char, int>mp;              //char, freq
        int i = 0, j = 0;
        int maxLen = INT_MIN;
        while(j < n){
            mp[s[j]]++;

            while(mp[s[j]] < k){
                mp[s[i]]--;

                if(mp[s[i]] == 0) mp.erase(s[i]);
                i++;
            }
            maxLen = max(maxLen, j-i+1);
        }
        return maxLen;
    }
};
/*
Input: s = "aabacbebebe", k = 3
Output: 7
Explanation: "cbebebe" is the longest substring with 3 distinct characters.

Input: s = "aaaa", k = 2
Output: -1
Explanation: There's no substring with 2 distinct characters.

Input: s = "aabaaab", k = 2
Output: 7
Explanation: "aabaaab" is the longest substring with 2 distinct characters.
*/