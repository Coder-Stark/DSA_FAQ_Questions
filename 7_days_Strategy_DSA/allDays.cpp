/*ARRAY *****************************************************/


//01,02. KADANE ALGORITHM OR MAXIMUM SUBARRAY            //T.C = O(N), S.C = O(1)
//OR LARGEST SUM OF CONTINUOUS ARRAY
Given an integer array nums, find the subarray with the largest 
sum, and return its sum.

//LEETCODE
class Solution {
public:
  int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    int j = 0;
    int maxSum = INT_MIN, sum = 0;
    while(j < n){
      sum += nums[j];
      maxSum = max(maxSum, sum);         //update maxSum

      if(sum < 0) sum = 0;               //handle negative (reset sum to 0)
      
      j++;
    }
    return maxSum;
  }
};

//GFG
class Solution {
  public:
    int maxSubarraySum(vector<int> &arr) {
        int sum = 0;
        int maxSum = INT_MIN;
        
        for(auto it : arr){
            sum += it;
            maxSum = max(maxSum, sum);
            
            if(sum < 0) sum = 0;
        }
        return maxSum;
    }
};

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
Example 2:

Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.
Example 3:

Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.


//03. Best Time to Buy and Sell Stock                        //T.C = O(N), S.C = O(1)
You are given an array prices where prices[i] is the price of 
a given stock on the ith day. You want to maximize your profit
by choosing a single day to buy one stock and choosing a different
day in the future to sell that stock. Return the maximum profit
you can achieve from this transaction. If you cannot achieve any profit, return 0.

class Solution {
public:
  int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int maxProfit = 0;
    int mini = prices[0];
    for(int i = 1; i < n; i++){
      int profit = prices[i]-mini;
      maxProfit = max(maxProfit, profit);
      mini = min(mini, prices[i]);
    }
    return maxProfit;
  }
};

Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.


//04. Best Time to Buy and Sell Stock (IV) [with limit]                            //{T.C = O(N*K), S.C = O(N*K)}
You are given an integer array prices where prices[i] is the 
price of a given stock on the ith day, and an integer k. Find 
the maximum profit you can achieve. You may complete at most k
transactions: i.e. you may buy at most k times and sell at most 
k times.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

class Solution {
public:
  vector<vector<vector<int>>>dp;
  int solveMem(vector<int>&prices, int i, int buy, int limit){
    int n = prices.size();
    int maxProfit = 0;
    //base case
    if(i >= n || limit == 0) return 0;

    if(dp[i][buy][limit] != -1) return dp[i][buy][limit];

    if(buy){
      int buyKaro = -prices[i] + solveMem(prices, i+1, 0, limit);  //0-> next sell
      int skipKaro = 0 + solveMem(prices, i+1, 1, limit);    //1 -> next buy
      maxProfit = max(buyKaro, skipKaro);
    }else{ //sell
      int sellKaro = +prices[i] + solveMem(prices, i+1, 1, limit-1);  //only sell limit reduced
      int skipKaro = 0 + solveMem(prices, i+1, 0, limit);
      maxProfit = max(sellKaro, skipKaro);
    }
    return dp[i][buy][limit] = maxProfit;
  }
  int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    dp.resize(n+1, vector<vector<int>>(2, vector<int>(k+1, -1)));   //index, 2(buy/sell), limit
    return solveMem(prices, 0, 1, k);     //prices, initial index, buy allowed, limit
  }
};

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.


//05. Trapping Rain Water           {T.C = (N), S.C = O(N)}
Given n non-negative integers representing an elevation map 
where the width of each bar is 1, compute how much water it 
can trap after raining.

class Solution {
public:
  int trap(vector<int>& height) {
    int n = height.size();
    vector<int>leftMaxVec(n), rightMaxVec(n);

    for(int i = 1; i < n ; i++){
      leftMaxVec[i] = max(leftMaxVec[i-1], height[i-1]);
    }

    for(int j = n-2; j >= 0; j--){
      rightMaxVec[j] = max(rightMaxVec[j+1], height[j+1]);
    }

    //trapped water
    int ans = 0;
    for(int i = 0; i < n; i++){
      int waterLevel = min(leftMaxVec[i], rightMaxVec[i]);

      if(waterLevel > height[i]){
        ans += waterLevel-height[i];
      }
    }
    return ans;
  }
};

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9


//06. Chocolate Distribution Problem              //{T.C = O(N*LOGN), S.C = O(1)}
Given an array arr[] of positive integers, where each value 
represents the number of chocolates in a packet. Each packet 
can have a variable number of chocolates. There are m students, 
the task is to distribute chocolate packets among m students 
such that -
  i. Each student gets exactly one packet.
  ii. The difference between maximum number of chocolates given
      to a student and minimum number is minimum and return 
      that minimum possible difference.

class Solution {
  public:
    int findMinDiff(vector<int>& a, int m) {
      int n = a.size();
      
      if(m == 0 || n == 0) return 0;
      if(m > n) return -1;              //not possible
      
      sort(a.begin(), a.end());
      
      int minDiff = INT_MAX;               //need to find minDiff
      for(int i = 0; i+m-1 < n; i++){
        int diff = a[i+m-1] - a[i];
        minDiff = min(minDiff, diff);
      }
      return minDiff;
    }
};

Input: arr = [3, 4, 1, 9, 56, 7, 9, 12], m = 5
Output: 6
Explanation: The minimum difference between maximum chocolates and minimum chocolates is 9 - 3 = 6 by choosing m packets as [3, 4, 9, 7, 9].
Input: arr = [7, 3, 2, 4, 9, 12, 56], m = 3
Output: 2
Explanation: The minimum difference between maximum chocolates and minimum chocolates is 4 - 2 = 2 by choosing m packets as [3, 2, 4].
Input: arr = [3, 4, 1, 9, 56], m = 5
Output: 55
Explanation: With 5 packets for 5 students, each student will receive one packet, so the difference is 56 - 1 = 55.


/*MATRIX ************************************************** */


//07. ROTATE IMAGE                //{T.C = O(N^2), S.C = O(1)}

You are given an n x n 2D matrix representing an image, 
rotate the image by 90 degrees (clockwise).You have to rotate 
the image in-place, which means you have to modify the input 
2D matrix directly. DO NOT allocate another 2D matrix and do 
the rotation.

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
      int n = matrix.size();                  //n == m
      //transpose of matrix
      for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){       //j = i+1 (upper triangle) X j = 0 (orignal)
          swap(matrix[i][j], matrix[j][i]);
        }
      }
      //reverse each row
      for(int i = 0; i < n; i++){
        reverse(matrix[i].begin(), matrix[i].end());
      }
    }
};

Example 1:
Input: matrix = [[1,2,3],
                 [4,5,6],
                [7,8,9]]
Output: [[7,4,1],
         [8,5,2],
         [9,6,3]]

Example 2:
Input: matrix = [[5,1,9,11],
                 [2,4,8,10],
                 [13,3,6,7],
                 [15,14,12,16]]
Output: [[15,13,2,5],
         [14,3,4,1],
         [12,6,8,9],
         [16,7,10,11]]


//08. SPIRAL MATRIX                {T.C = O(N*M), S.C = O(N)}

Given an m x n matrix, return all elements of the matrix in 
spiral order

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int>ans;
        int n = matrix.size(), m = matrix[0].size();
        int rowStart = 0, rowEnd = n-1;
        int colStart = 0, colEnd = m-1;

        while(rowStart <= rowEnd && colStart <= colEnd){
            //print first row
            if(rowStart <= rowEnd){                        //we can skip [if](already handle in while loop)
                for(int j = colStart; j <= colEnd; j++){
                    ans.push_back(matrix[rowStart][j]);
                }
            }
            rowStart++;
            //print last column
            if(colStart <= colEnd){                      //we can skip [if](already handle in while loop)
                for(int i = rowStart; i <= rowEnd; i++){
                    ans.push_back(matrix[i][colEnd]);
                }
            }
            colEnd--;
            //print last row
            if(rowStart <= rowEnd){
                for(int j = colEnd; j >= colStart; j--){
                    ans.push_back(matrix[rowEnd][j]);
                }
            }
            rowEnd--;
            //print first col
            if(colStart <= colEnd){
                for(int i = rowEnd; i >= rowStart; i--){
                    ans.push_back(matrix[i][colStart]);
                }
            }
            colStart++;
        }

        return ans;
    }
};

Example 1:
Input: matrix = [[1,2,3],
				 [4,5,6],
				 [7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
Input: matrix = [[1,2,3,4],
				 [5,6,7,8],
				 [9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]


/*INTERVAL GREEDY FAMILY ************************************/


//10. MERGE INTERVALS            //{T.C = O(N*LOGN), S.C = O(N)}
Given an array of intervals where intervals[i] = [starti, endi],
merge all overlapping intervals, and return an array of the 
non-overlapping intervals that cover all the intervals in the
input.

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
      sort(intervals.begin(), intervals.end());
      vector<vector<int>>ans;
      for(auto &it : intervals){
        int start = it[0];           //1 {1, 3}
        int end   = it[1];           //3
        
        //no overlap
        if(ans.empty() || ans.back()[1] < start){    //empty or interval's last < next interval
          ans.push_back(it);
        }else{
          //overlap
          ans.back()[1] = max(ans.back()[1], end);
        }
      }
      return ans;
    }
};

//INTERVALS + GREEDY
//NON OVERALAP TYPE SOLUTION
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end());        //sort on start

        int prevStart = intervals[0][0];
        int prevEnd   = intervals[0][1];

        vector<vector<int>>ans;

        for(int i = 1; i < n; i++){
            int start = intervals[i][0];
            int end   = intervals[i][1];

            //overlap
            if(prevEnd >= start){
                prevEnd = max(prevEnd, end);
            }else{
            //push previous interval
                ans.push_back({prevStart, prevEnd});

                prevStart = start;
                prevEnd   = end;
            }
        }       

        //push last interval
        ans.push_back({prevStart, prevEnd});
        return ans;
    }
};

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

Example 3:
Input: intervals = [[4,7],[1,4]]
Output: [[1,7]]
Explanation: Intervals [1,4] and [4,7] are considered overlapping.


//11. INSERT INERVAL         //{T.C = O(N*LOGN), S.C = O(N)}
//simple create new vector of vector insert previous + new then sort

You are given an array of non-overlapping intervals intervals 
where intervals[i] = [starti, endi] represent the start and 
the end of the ith interval and intervals is sorted in ascending 
order by starti. You are also given an interval newInterval = 
[start, end] that represents the start and end of another interval.

Insert newInterval into intervals such that intervals is still 
sorted in ascending order by starti and intervals still does 
not have any overlapping intervals (merge overlapping intervals 
if necessary).

Return intervals after the insertion.

Note that you don't need to modify intervals in-place. You 
can make a new array and return it.

class Solution {
public:
    vector<vector<int>>mergeInterval(vector<vector<int>>&newIntervals){
        int n = newIntervals.size();
        sort(newIntervals.begin(), newIntervals.end());

        int prevStart = newIntervals[0][0];
        int prevEnd   = newIntervals[0][1];

        vector<vector<int>>ans;
        
        for(int i = 1; i < n; i++){
            int start = newIntervals[i][0];
            int end   = newIntervals[i][1];

            //overlap
            if(prevEnd >= start){                //>= -> overalapping here
                prevEnd = max(prevEnd, end);
            }else{
                ans.push_back({prevStart, prevEnd});

                prevStart = start;
                prevEnd   = end;
            }
        }

        ans.push_back({prevStart, prevEnd});      //push last (left) interval

        return ans;
    }
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>>temp;
        for(auto it : intervals) temp.push_back(it);

        temp.push_back(newInterval);

        return mergeInterval(temp);
    }
};

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].


//12. NON-OVERLAPPING INTERVALS    //{T.C = O(N*LOGN), S.C = (1)}

Given an array of intervals intervals where intervals[i] = [starti, endi], 
return the minimum number of intervals you need to remove to 
make the rest of the intervals non-overlapping.

Note that intervals which only touch at a point are non-overlapping. 
For example, [1, 2] and [2, 3] are non-overlapping.

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

        // int prevStart = intervals[0][i];
        int prevEnd   = intervals[0][1];

        // vector<vector<int>>ans;
        int count = 0;
        
        for(int i = 1; i < intervals.size(); i++){
            int start = intervals[i][0];
            int end   = intervals[i][1];

            //overlap
            if(prevEnd > start){        //not >=
                count++; 
                prevEnd = min(prevEnd, end);
            }else{
                prevEnd = end;
            }
        }
        return count;
    }
};

Example 1:
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

//13. MINIMUM NUBMER OF ARROWS TO BURST BALLONS   //{T.C = O(N*LOGN), S.C = O(1)}
There are some spherical balloons taped onto a flat wall that
represents the XY-plane. The balloons are represented as a 
2D integer array points where points[i] = [xstart, xend] 
denotes a balloon whose horizontal diameter stretches between
xstart and xend. You do not know the exact y-coordinates of the balloons.

Arrows can be shot up directly vertically (in the positive y-direction) 
from different points along the x-axis. A balloon with xstart
and xend is burst by an arrow shot at x if xstart <= x <= xend. 
There is no limit to the number of arrows that can be shot. 
A shot arrow keeps traveling up infinitely, bursting any balloons in its path.

Given the array points, return the minimum number of arrows 
that must be shot to burst all balloons.

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size();
        sort(points.begin(), points.end());

        int prevEnd = points[0][1];

        int count = n;                            //initial (1:1 [arrow : interval])
        
        for(int i = 1; i < n; i++){
            int start = points[i][0];
            int end   = points[i][1];

            //overlap
            if(prevEnd >= start){            //can be >=
                count--;
                prevEnd = min(prevEnd, end);
            }else{
                prevEnd = end;
            }
        }

        return count;
    }
};

Example 1:
Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

Example 2:
Input: points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4
Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.

Example 3:
Input: points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
- Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].


//14. ACTIVITY SELECTION              //{T.C = O(N*LOGN), S.C = O(N)}

Given a set of activities, each with a start time and a finish
time, represented by the arrays start[] and finish[], respectively. 
A single person can perform only one activity at a time, meaning 
no two activities can overlap. Your task is to determine the 
maximum number of activities that a person can complete in a day.

Note: Start time and finish time cannot overlap, i.e., if a 
person finishes an activity at time x, then they cannot start 
another activity at time x.

class Solution {
  public:
    //minimum overlap -> max activities done
    int activitySelection(vector<int> &start, vector<int> &finish) {
        int n = start.size();              //n = m
        vector<vector<int>>intervals;
        for(int i = 0; i < n; i++){
            intervals.push_back({start[i], finish[i]});
        }
        
        //sort by end not START
        auto lambda = [&](vector<int>&a, vector<int>&b){
            return a[1] < b[1];  
        };
        sort(intervals.begin(), intervals.end(), lambda);
        
        int prevEnd = intervals[0][1];
        int count = n;                 //assume every activity is selectable
        
        for(int i = 1 ; i < n; i++){
            int start = intervals[i][0];
            int end   = intervals[i][1];
            
            //overlap
            if(prevEnd >= start){            //on boundary consider overlap
                count--;
                prevEnd = min(prevEnd, end);      //min overalap highest activity
            }else{
                prevEnd = end;
            }
        }
        
        return count;                 
    }
};

Input: start[] = [1, 3, 0, 5, 8, 5], finish[] = [2, 4, 6, 7, 9, 9]
Output: 4
Explanation: A person can perform at most four activities. The maximum set of activities that can be executed is {0, 1, 3, 4}

Input: start[] = [10, 12, 20], finish[] = [20, 25, 30]
Output: 1
Explanation: A person can perform at most one activity.

Input: start[] = [1, 3, 2, 5], finish[] = [2, 4, 3, 6]
Output: 3
Explanation: A person can perform activities 0, 1 and 3.


/*STACK AND QUEUE *******************************************/


//18. VALID/BALANCED PARENTHESES    {T.C = O(N), S.C = O(N)}
Given a string s containing just the characters '(', ')', 
'{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

class Solution {
public:
    bool isValid(string s) {
        int n = s.size();
        stack<char>stk;
        for(int i = 0 ; i < n; i++){
            if(!stk.empty() && (
               (s[i] == ')' && stk.top() == '(') || 
               (s[i] == '}' && stk.top() == '{') || 
               (s[i] == ']' && stk.top() == '[')
            ))  {
                stk.pop();
            }else{
                stk.push(s[i]);
            }  
        }

        return stk.empty();
    }
};

Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "()[]{}"
Output: true

Example 3:
Input: s = "(]"
Output: false

Example 4:
Input: s = "([])"
Output: true

Example 5:
Input: s = "([)]"
Output: false


//19. IMPLEMENT STACK USING ARRAY    {T.C = O(N), S.C = O(N)}

Implement a Stack using an Array, where the size of the array, n is given.
The Stack must support the following operations:

(i) push(x): Insert an element x at the top of the stack.
(ii) pop(): Remove the element from the top of the stack.
(iii) peek(): Return the top element if not empty, else -1.
(iv) isEmpty(): Return true if the stack is empty else return false.
(v) isFull(): Return true if the stack is full else return false.

There will be a sequence of queries queries[][]. The queries are represented in numeric form:

1 x : Call push(x)
2 : Call pop()
3 : Call peek()
4  : Call isEmpty()
5 : Call isFull()
You just have to implement the functions push, pop, peek, isEmpty, and isFull. The driver code will handle the output.

Note: All the queries are valid.

class myStack {
  public:
    int top;
    int* arr;
    int size;
    
    myStack(int n) {
        // Define Data Structures
        top = -1;
        arr = new int[n];
        size = n;
        
    }

    bool isEmpty() {
        // check if the stack is empty
        return top == -1;
    }

    bool isFull() {
        // check if the stack is full
        return top == size-1;
    }

    void push(int x) {
        // inserts x at the top of the stack
        if(top == size-1) return;
        top++;
        arr[top] = x;
    }

    void pop() {
        // removes an element from the top of the stack
        if(top ==  -1) return;
        top--;
    }

    int peek() {
        // Returns the top element of the stack
        if(top == -1) return -1;
        return arr[top];
    }
};

Input: n = 3, q = 6, queries[][] = [[1, 5], [1, 3], [3], [2], [4], [5]]
Output: [3, false, false]
Explanation: Queries on stack are as follows:
push(5) : Insert 5 at the top of the stack.
push(3) : Insert 3 at the top of the stack.
peek() : Return the top element i.e. 3.
pop() : Remove the top element i.e. 3.
isEmpty() : return false as the stack is not empty.
isFull() : return false as the stack is not full. Capacity = 3.

Input: n = 1, q = 5, queries[][] =  [[2], [3], [4], [1, 9], [5]]
Output: [-1, -1, true, true]
Explanation: Queries on stack are as follows:
pop(): Since stack is empty, nothing is popped.
peek(): Return the top element. Since the stack is empty, return -1.
isEmpty(): Return true as the stack is empty.
push(9): Insert 9 at the top of the stack. The stack will be [9].
isFull(): Return true as the stack is full. Capacity = 1.


//21. IMPLEMENT STACK USING QUEUE    //{T.C = O(N), S.C = O(N)}
//using 1 stack

Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal stack (push, top, pop, and empty).

Implement the MyStack class:

void push(int x) Pushes element x to the top of the stack.
int pop() Removes the element on the top of the stack and returns it.
int top() Returns the element on the top of the stack.
boolean empty() Returns true if the stack is empty, false otherwise.

class MyStack {
public:
    queue<int>q;
    MyStack() {}
    
    void push(int x) {            //just handle push , pop already handled
        int n = q.size();
        q.push(x);
        while(n--){
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int ele = q.front();
        q.pop();
        return ele;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

Input
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 2, 2, false]
Explanation
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // return 2
myStack.pop(); // return 2
myStack.empty(); // return False


//22. IMPLEMENT QUEUE USING STACKS
//using 2 queues

Implement a first in first out (FIFO) queue using only two 
stacks. The implemented queue should support all the functions 
of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.

class MyQueue {
public:
    stack<int>stk1;
    stack<int>stk2;

    MyQueue() {}
    
    void push(int x) {
        //move stk1 -> stk2
        while(!stk1.empty()){
            stk2.push(stk1.top());
            stk1.pop();
        }

        stk1.push(x);               //push new element

        //move back stk2 -> stk1
        while(!stk2.empty()){
            stk1.push(stk2.top());
            stk2.pop();
        }
    }
    
    int pop() {
        int ele = stk1.top();
        stk1.pop();
        return ele;
    }
    
    int peek() {
        return stk1.top();
    }
    
    bool empty() {
        return stk1.empty();
    }
};

Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]

Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false


//23. NEXT GREAER ELEMENT I           {T.C = O(N), S.C = O(N)}

The next greater element of some element x in an array is the
first greater element that is to the right of x in the same 
array.

You are given two distinct 0-indexed integer arrays nums1 and 
nums2, where nums1 is a subset of nums2.

For each 0 <= i < nums1.length, find the index j such that 
nums1[i] == nums2[j] and determine the next greater element 
of nums2[j] in nums2. If there is no next greater element, 
then the answer for this query is -1.

Return an array ans of length nums1.length such that ans[i] 
is the next greater element as described above.

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int>stk;                         //store next greater ele
        unordered_map<int,int>mp;              //elem -> next greater ele

        for(auto it : nums2){
            while(!stk.empty() && it > stk.top()){
                mp[stk.top()] = it;            //prev(ele)->current(next greater ele)
                stk.pop();
            }
            stk.push(it);
        }

        vector<int>ans;

        for(auto it : nums1){
            if(mp.count(it)) ans.push_back(mp[it]);
            else ans.push_back(-1);
        }

        return ans;
    }
};

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
- 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
- 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.

Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
- 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.


//24. NEXT GREATER ELEMENT 2     //{T.C = O(N), S.C = O(N)}

Given a circular integer array nums (i.e., the next element 
of nums[nums.length - 1] is nums[0]), return the next greater 
number for every element in nums.

The next greater number of a number x is the first greater 
number to its traversing-order next in the array, which means 
you could search circularly to find its next greater number. 
If it doesn't exist, return -1 for this number.

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int>stk;
        vector<int>ans(n, -1);

        for(int i = 0; i < 2*n; i++){
            while(!stk.empty() && nums[i % n] > nums[stk.top()]){
                ans[stk.top()] = nums[i % n];
                stk.pop();
            }

            if(i < n) stk.push(i);
        }
        
        return ans;
    }
};

Example 1:

Input: nums = [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; 
The number 2 can't find next greater number. 
The second 1's next greater number needs to search circularly, which is also 2.
Example 2:

Input: nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]


/*LINKED LIST ***********************************************/


//29. DETECT AND REMOVE LOOP IN LL   {T.C = O(N), S.C = O(1)}

Given the head of a singly linked list, the task is to remove a cycle if present. A cycle exists when a node's next pointer points back to a previous node, forming a loop.

Internally, a variable pos is used to denotes the position of 
the node where the cycle starts, but it is not passed as a parameter.
The linked list remains as it is if there is cycle in the list.
The output will be "true" if your code works according to expectations, otherwise "false". 

class Solution {
  public:
    void removeLoop(Node* head) {
        Node* slow  = head;
        Node* fast = head;
        Node* meetingPoint = NULL;
        
        //find loop logic
        while(fast && fast-> next){
            slow = slow-> next;
            fast = fast->next->next;
            
            if(slow == fast){              //slow contains looped index
                meetingPoint = slow;
                break;
            }
        }
        
        if(meetingPoint == NULL) return;            //no loop found
        
        //remove node logic  
        //core logic below
        //distance from head to loop start = distance from meeting point to loop start
        
        Node* loopStartNode = head;              //find exact loopstart
        while(loopStartNode != meetingPoint){
            loopStartNode = loopStartNode->next;
            meetingPoint = meetingPoint->next;
        }
        
        Node* lastNode = loopStartNode;
        
        while(lastNode->next != loopStartNode){     //keep moving until node points back to loop start
            lastNode = lastNode->next;
        }
        
        lastNode->next = NULL;                    //break the loop
    }
};

Input: head = 1 -> 3 -> 4, pos = 2
Output: true
Explanation: The linked list looks like
A loop is present in the list, and it is removed.

Input: head = 1 -> 8 -> 3 -> 4, pos = 0
Output: true
Explanation: 
The Linked list does not contains any loop. 

Input: head = 1 -> 2 -> 3 -> 4, pos = 1
Output: true
Explanation: The linked list looks like 
A loop is present in the list, and it is removed.


//30a. MERGE 2 SORTED LIST     {T.C  O(N+M), S.C = O[aux](N+M)}

You are given the heads of two sorted linked lists list1 and list2.
Merge the two lists into one sorted list. The list should be made 
by splicing together the nodes of the first two lists.
Return the head of the merged linked list.

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        //base case
        if(!list1 && !list2) return NULL;
        if(!list1) return list2;
        if(!list2) return list1;

        if(list1-> val <= list2->val){
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }else{
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};

Example 1:
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Example 2:
Input: list1 = [], list2 = []
Output: []

Example 3:
Input: list1 = [], list2 = [0]
Output: [0]


//30b. MERGE K SORTED LL          {T.C = O(N*LOGK), S.C = O[aux](N)}

You are given an array of k linked-lists lists, each linked-list
is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.
class Solution {
public:
    ListNode* mergeTwoSortedLists(ListNode* list1, ListNode* list2){
        //bsae case
        if(!list1 && !list2) return NULL;
        if(!list1) return list2;
        if(!list2) return list1;

        if(list1->val <= list2->val){
            list1->next = mergeTwoSortedLists(list1->next, list2);
            return list1;
        }else{
            list2->next = mergeTwoSortedLists(list1, list2->next);
            return list2;
        }
    }

    ListNode* partitionAndMerge(int start , int end , vector<ListNode*>& lists){
        //base case
        if(start > end) return NULL;
        if(start == end) return lists[start];       //only 1 LL

        int mid = start + (end-start)/2;

        ListNode* L1 = partitionAndMerge(start, mid, lists);
        ListNode* L2 = partitionAndMerge(mid+1, end, lists);

        return mergeTwoSortedLists(L1, L2);
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int k = lists.size();

        if(k == 0) return NULL;

        return partitionAndMerge(0, k-1, lists);
    }
};

Example 1:
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted linked list:
1->1->2->3->4->4->5->6

Example 2:
Input: lists = []
Output: []

Example 3:
Input: lists = [[]]
Output: []


/*BINARY TREE TRAVERSAL / VIEW **************************** */


//32. LEFT VIEW OF BINARY TREE      {T.C = O(N), S.C = O(H)}

Given the root of a binary tree. Your task is to return the 
left view of the binary tree. The left view of a binary tree 
is the set of nodes visible when the tree is viewed from the 
left side.
Note: If the tree is empty, return an empty list.

class Solution {
  public:
    //NLR  (preorder)
    void leftDFS(Node* root, vector<int>&ans, int lvl){
        //base case
        if(!root) return;
        
        if(lvl == ans.size()) ans.push_back(root->data);       //N
        leftDFS(root-> left, ans, lvl+1);                     //L
        leftDFS(root-> right, ans, lvl+1);                    //R
    }
    vector<int> leftView(Node *root) {
        vector<int>ans;
        leftDFS(root, ans, 0);                //0 = initial level
        return ans;
    }
};

Input: root = [1, 2, 3, 4, 5, N, N]
Output:[1, 2, 4]
Explanation: From the left side of the tree, only the nodes 1, 2, and 4 are visible.

Input: root = [1, 2, 3, N, N, 4, N, N, 5, N, N]
Output: [1, 2, 4, 5]
Explanation: From the left side of the tree, only the nodes 1, 2, 4, and 5 are visible.


//33. BINARY TREE RIGHT SIDE VIEW   {T.C = O(N), S.C = O(H)}

Given the root of a binary tree, imagine yourself standing on 
the right side of it, return the values of the nodes you can 
see ordered from top to bottom.

class Solution {
public:
    //NRL (reverse preorder(NLR -> NRL))
    void rightDFS(TreeNode* root, vector<int>&ans, int lvl){
        //base case
        if(!root) return;

        if(lvl == ans.size()) ans.push_back(root->val);        //N  (for new level first put it ans)
        rightDFS(root->right, ans, lvl+1);                     //R
        rightDFS(root->left, ans, lvl+1);                      //L
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int>ans;
        rightDFS(root, ans, 0);               //0 = initial level
        return ans;
    }
};

Example 1:
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]

Example 2:
Input: root = [1,2,3,4,null,null,null,5]
Output: [1,3,4,5]

Example 3:
Input: root = [1,null,3]
Output: [1,3]

Example 4:
Input: root = []
Output: []


//34. LEVEL ORDER TRAVERSAL      {T.C = O(N), S.C = O(N)}

Given the root of a Binary Tree, your task is to return its 
Level Order Traversal.
Note: A level order traversal is a breadth-first search (BFS) 
of the tree. It visits nodes level by level, starting from the 
root, and processes all nodes from left to right within each 
level before moving to the next.

class Solution {
  public:
    vector<int> levelOrder(Node *root) {
        vector<int>ans;
        queue<Node*>q;
        
        q.push(root);
        
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            
            ans.push_back(frontNode->data);
            if(frontNode->left) q.push(frontNode->left);
            if(frontNode->right)q.push(frontNode->right);
        }
        
        return ans;
    }
};


//35. TOP VIEW OF BINARY TREE       {T.C = O(N*LOGN), S.C = O(N)}
You are given the root of a binary tree, and your task is to 
return its top view. The top view of a binary tree is the set 
of nodes visible when the tree is viewed from the top.

Note:
Return the nodes from the leftmost node to the rightmost node.
If multiple nodes overlap at the same horizontal position, 
only the topmost (closest to the root) node is included in the view. 

class Solution {
  public:
    vector<int> topView(Node *root) {
        vector<int>ans;
        
        map<int,int>mp;               //x axis distance, node->val
        queue<pair<Node*, int>>q;           //node, distance
        
        q.push({root, 0});            //0 = initial distance
        
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            
            Node* node = frontNode.first;
            int x = frontNode.second;
            
            if(!mp.count(x)) mp[x] = node->data;      //not override
            
            if(node->left) q.push({node->left, x-1});
            if(node->right)q.push({node->right, x+1});
        }
        
        for(auto it : mp) ans.push_back(it.second);
        
        return ans;
    }
};

Input: root = [1, 2, 3]
Output: [2, 1, 3]
 
Input: root = [10, 20, 30, 40, 60, 90, 100]
Output: [40, 20, 10, 30, 100]


//36. BOTTOM VIEW OF BINARY TREE   {T.C = O(N*LOGN), S.C = O(N)}

You are given the root of a binary tree, and your task is to 
return its bottom view. The bottom view of a binary tree is 
the set of nodes visible when the tree is viewed from the bottom.

Note: If there are multiple bottom-most nodes for a horizontal
distance from the root, then the latter one in the level order 
traversal is considered.

class Solution {
  public:
    vector<int> bottomView(Node *root) {
        vector<int>ans;
        
        map<int,int>mp;             //x(distance), node-val
        
        queue<pair<Node*, int>>q;        //Node, distance
        
        q.push({root, 0});          //initialise (node[root], 0 x axis center)
        
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            
            Node* node = frontNode.first;
            int x = frontNode.second;
            
            //if(!mp.count(x)) mp[x] = node-> data;        //top view (not override)
            mp[x] = node->data;
            
            if(node->left) q.push({node->left, x-1});
            if(node->right)q.push({node->right, x+1});
        }
        
        for(auto it : mp) ans.push_back(it.second);
        
        return ans;
    }
};

Input: root = [1, 2, 3, 4, 5, N, 6]
Output: [4, 2, 5, 3, 6]
    
Input: root = [20, 8, 22, 5, 3, 4, 25, N, N, 10, 14, N, N, 28, N]
Output: [5, 10, 4, 28, 25]
    

//37. BINARY TREE ZIGZAG LEVEL ORDER TRAVERSAL  //{T.C = O(N), S.C= O(N)}

Given the root of a binary tree, return the zigzag level order 
traversal of its nodes values. (i.e., from left to right, 
then right to left for the next level and alternate between).

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        //base case
        if(!root) return ans;

        queue<TreeNode*>q;
        q.push(root);

        int level = 0;

        while(!q.empty()){
            int sz = q.size();
            vector<int>temp;

            for(int i = 0; i < sz; i++){
                TreeNode* frontNode = q.front();
                q.pop();

                temp.push_back(frontNode->val);
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right)q.push(frontNode->right);
            }

            if(level % 2  == 1){
                reverse(temp.begin(), temp.end());
            }

            ans.push_back(temp);
            level++;
        }

        return ans;
    }
};

Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []


//38. TREE BOUNDARY TRAVERSAL    {T.C = O(N), S.C = O(H)}

Given a root of a Binary Tree, return its boundary traversal 
in the following order:
Left Boundary: Nodes from the root to the leftmost non-leaf 
node, preferring the left child over the right and excluding leaves.

Leaf Nodes: All leaf nodes from left to right, covering every
leaf in the tree.

Reverse Right Boundary: Nodes from the root to the rightmost 
non-leaf node, preferring the right child over the left, 
excluding leaves, and added in reverse order.

Note: The root is included once, leaves are added separately 
to avoid repetition, and the right boundary follows traversal 
preference not the path from the rightmost leaf.

class Solution {
  public:
    void leftBoundary(Node* root, vector<int>&ans){
        //base case
        if(!root || (!root->left && !root->right)) return;    //empty or leaf skip
        
        ans.push_back(root->data);
        if(root->left) leftBoundary(root->left, ans);        //if not left then only go further
        else leftBoundary(root->right, ans);  
    }
    
    void leafBoundary(Node* root, vector<int>&ans){
        //base case
        if(!root) return; 
        
        if(!root->left && !root->right) ans.push_back(root->data);   //only leaf node push
        
        leafBoundary(root->left, ans);
        leafBoundary(root->right, ans);
    }
    
    void rightBoundaryReverse(Node* root, vector<int>&ans){
        //base case
        if(!root || (!root->left && !root->right)) return;     //empty for leaf skip
        
        if(root->right) rightBoundaryReverse(root->right, ans);     //if not right then only go further
        else rightBoundaryReverse(root->left, ans); 
        
        //push reverse
        ans.push_back(root->data);
    }
    vector<int> boundaryTraversal(Node *root) {
        //base case
        if(!root) return {};
        
        vector<int>ans;
        ans.push_back(root->data);                               //1.
        
        leftBoundary(root->left, ans);                     //2.
        
        leafBoundary(root->left, ans);                     //3a.
        leafBoundary(root->right, ans);                    //3b.
        
        rightBoundaryReverse(root->right, ans);
        
        return ans;
    }
};

Input: root = [1, 2, 3, 4, 5, 6, 7, N, N, 8, 9, N, N, N, N]
Output: [1, 2, 4, 8, 9, 6, 7, 3]

Input: root = [1, N, 2, N, 3, N, 4, N, N] 
Output: [1, 4, 3, 2]

Left boundary: [1] (as there is no left subtree)
Leaf nodes: [4]
Right boundary: [3, 2] (in reverse order)
Final traversal: [1, 4, 3, 2]


/*BINARY TREE CONSTRUCTION / BST ****************************/


//39. MAXIMUM DEPTH OF BINARY TREE   {T.C = O(N), S.C= O(H)}
//   OR HEIGHT OF BINARY TREE
Given the root of a binary tree, return its maximum depth.
A binary tree's maximum depth is the number of nodes along 
the longest path from the root node down to the farthest 
leaf node.

class Solution {
public:
    int maxDepth(TreeNode* root) {
        //base case
        if(!root) return 0;

        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        return max(left, right) + 1;                //1 for current node

    }
};

Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: 3

Example 2:
Input: root = [1,null,2]
Output: 2


//40. DIAMETER OF BINARY TREE    {T.C = O(N), S.C = O(H)}

Given the root of a binary tree, return the length of the 
diameter of the tree.
The diameter of a binary tree is the length of the longest 
path between any two nodes in a tree. This path may or may 
not pass through the root.
The length of a path between two nodes is represented by the 
number of edges between them.

class Solution {
public:
    int heightOfBT(TreeNode* root){
        //base case
        if(!root) return 0;

        int left = heightOfBT(root->left);
        int right = heightOfBT(root->right);

        return max(left, right) + 1;               //1 for current node
    }
    int diameterOfBinaryTree(TreeNode* root) {
        //base case
        if(!root) return 0;

        int leftSubtreeDia = diameterOfBinaryTree(root->left);      //longest chain in left subtree only
        int rightSubtreeDia = diameterOfBinaryTree(root->right);    //longest chain in right subtree only
        int passRootDia = heightOfBT(root->left) + heightOfBT(root->right); //longest chain pass through root

        return max({leftSubtreeDia, rightSubtreeDia, passRootDia});
    }
};

Example 1:
Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

Example 2:
Input: root = [1,2]
Output: 1


//42. CONSTRUCT TREE USING PREORDER AND INORDER  //{T.C = O(N^2), S.C = O(H)}

Given two integer arrays preorder and inorder where preorder 
is the preorder traversal of a binary tree and inorder is the
inorder traversal of the same tree, construct and return the 
binary tree.

class Solution {
public:
    TreeNode* buildPrAndIn(vector<int>&preorder, vector<int>&inorder, int start, int end, int &idx){
        //base case
        if(start > end) return NULL;        //invalid/leaf

        int rootVal = preorder[idx];
        int i = start;                        //for search preorder's value in inorder(traversal)
        for(; i <= end; i++){
            if(inorder[i] == rootVal) break;
        }

        idx++;
        //now i contains root position (in inorder)
        
        //build root->left->right
        TreeNode* root = new TreeNode(rootVal);
        root->left = buildPrAndIn(preorder, inorder, start, i-1, idx);
        root->right= buildPrAndIn(preorder, inorder, i+1, end, idx);

        return root;

    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();         //size of preorder/inorder same

        int idx = 0;                    //pointer at preorder

        return buildPrAndIn(preorder, inorder, 0, n-1, idx);  //0 = pointer inorder -> start and end

    }
};

Example 1:
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: preorder = [-1], inorder = [-1]
Output: [-1]


//43. CONSTRUCT TREE USING INORDER AND POSTORDER  //{T.C = O(N^2), S.C = O(H)}

Given two integer arrays inorder and postorder where inorder 
is the inorder traversal of a binary tree and postorder is 
the postorder traversal of the same tree, construct and 
return the binary tree.

class Solution {
public:
    TreeNode* buildInAndPo(vector<int>&inorder, vector<int>&postorder, int start, int end, int &idx){
        //base case
        if(start > end) return NULL;

        int rootVal = postorder[idx];

        int i = start;
        //traversal in inorder
        for(; i <= end; i++){
            if(inorder[i] == rootVal) break;
        }
        idx--;                                     //last to first

        //build root->right->left
        TreeNode* root = new TreeNode(rootVal);
        root->right = buildInAndPo(inorder, postorder, i+1, end, idx);
        root->left  = buildInAndPo(inorder, postorder, start, i-1, idx);

        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = postorder.size();

        int idx = n-1;                    //postorder (root at last), search => root->righ->left in inorder

        return buildInAndPo(inorder, postorder, 0, n-1, idx);
    }
};

Example 1:
Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: inorder = [-1], postorder = [-1]
Output: [-1]


//45. LARGEST BST IN A BINARY TREE    //{T.C = O(N), S.C = O(H)}

Youre given a binary tree. Your task is to find the size of 
the largest subtree within this binary tree that also satisfies 
the properties of a Binary Search Tree (BST). The size of a 
subtree is defined as the number of nodes it contains.

Note: A subtree of the binary tree is considered a BST if 
for every node in that subtree, the left child is less than 
the node, and the right child is greater than the node, 
without any duplicate values in the subtree.

class NodeVal{
  public:
    int minNode, maxNode, maxSize;
    
    NodeVal(int minNode, int maxNode, int maxSize){
        this->minNode = minNode;
        this->maxNode = maxNode;
        this->maxSize = maxSize;
    }
};
class Solution {
  public:
    /*You are required to complete this method */
    // Return the size of the largest sub-tree which is also a BST
    NodeVal solve(Node* root){
        //base case
        if(!root) return NodeVal(INT_MAX, INT_MIN, 0);
        
        auto leftTree = solve(root->left);
        auto rightTree = solve(root->right);
        
        //check valid bst (left max < node < right min)
        if(leftTree.maxNode < root->data && root->data < rightTree.minNode){
            return NodeVal(
                        min(root->data, leftTree.minNode),      //min can be root or min(subtree's node)
                        max(root->data, rightTree.maxNode),     //max can be root or max(subtree's node)
                        leftTree.maxSize + rightTree.maxSize+1 //total max size
                    );
        }
        
        //invalid tree  (invalid, invalid, max size should correct)
        return NodeVal(INT_MIN, INT_MAX, max(leftTree.maxSize, rightTree.maxSize)); 
    }
    int largestBst(Node *root) {
        return solve(root).maxSize;
    }
};

Input: root = [5, 2, 4, 1, 3]
Root-to-leaf-path-sum-equal-to-a-given-number-copy
Output: 3
Explanation:The following sub-tree is a BST of size 3
Balance-a-Binary-Search-Tree-3-copy

Input: root = [6, 7, 3, N, 2, 2, 4]
Output: 3
Explanation: The following sub-tree is a BST of size 3:


//46. MERGE 2 BST        //{T.C = O(N+M), S.C = O(N+M)}

You are given the root of two BSTs, you have to merge this 
two BST and return the in-order traversal of the new BST.

class Solution {
  public:
    //for bst inorder traversal -> sorted list
    
    void inOrTraversal(Node* root, vector<int>&arr){
        //base case
        if(!root) return;
        
        inOrTraversal(root->left, arr);
        arr.push_back(root->data);
        inOrTraversal(root->right, arr);
    };
    
    vector<int> mergeSortedArrays(vector<int>&arr1, vector<int>&arr2){
        vector<int>merged;
        
        int i = 0, j = 0;
        while(i < arr1.size() && j < arr2.size()){
            if(arr1[i] < arr2[j]){
                merged.push_back(arr1[i]);
                i++;
            }else{
                merged.push_back(arr2[j]);
                j++;
            }
        }
        while(i < arr1.size()){
            merged.push_back(arr1[i]);
            i++;
        }
        while(j < arr2.size()){
            merged.push_back(arr2[j]);
            j++;
        }
        
        return merged;
    }
    vector<int> merge(Node *root1, Node *root2) {
        vector<int>arr1,arr2;
        
        inOrTraversal(root1, arr1);
        inOrTraversal(root2, arr2);
        
        return mergeSortedArrays(arr1, arr2);
    }
};

Input: root1 = [3, 1, 5], root2 = [4, 2, 6]
Output: [1, 2, 3, 4, 5, 6]
Explanation: After merging and sorting the two BST we get [1, 2, 3, 4, 5, 6].

Input: root1 = [8, 2, 10, 1, N], root2 = [5, 3, N, 0, N] 
Output: [0, 1, 2, 3, 5, 8, 10]
Explanation: After merging and sorting the two BST we get [0, 1, 2, 3, 5, 8, 10].


/*HEAP / PRIORITY QUEUE ************************************ */


//47. FIND MEDIAN IN A STREAM      //{T.C = O(N*LOGN), S.C = O(N)}

Given a data stream arr[] where integers are read sequentially,
the task is to determine the median of the elements encountered 
so far after each new integer is read.

The median is defined as follows:

1. Odd number of elements: The median is the middle element 
when the current set of numbers is sorted.
2. Even number of elements: The median is the arithmetic mean 
(average) of the two middle elements when the current set of 
numbers is sorted.

class Solution {
  public:
    priority_queue<int>leftMaxHeap;
    priority_queue<int, vector<int>, greater<int>>rightMinHeap;
    
    void add(int num){                    //T.C = O(LOGN)
        //insert by value
        if(leftMaxHeap.empty() || num < leftMaxHeap.top()){
            leftMaxHeap.push(num);
        }else{
            rightMinHeap.push(num);
        }
        
        //left size always >= (greater or equal to right)
        if((leftMaxHeap.size() < rightMinHeap.size())){
            leftMaxHeap.push(rightMinHeap.top());
            rightMinHeap.pop();
        }
        else if((leftMaxHeap.size() - rightMinHeap.size()) > 1){   //left at most 1 more
            rightMinHeap.push(leftMaxHeap.top());
            leftMaxHeap.pop();
        }
    }
    
    double findMedian(){                  //T.C = O(1)
        if(leftMaxHeap.size() == rightMinHeap.size()){
            return (leftMaxHeap.top() + rightMinHeap.top())/2.0;
        }else{
            return leftMaxHeap.top();                  //extra is on left only
        }
    }
    vector<double> getMedian(vector<int> &arr) {  //OVERALL T.C = O(N*LOGN)
        
        vector<double>ans;
        
        for(auto it : arr){
            add(it);
            ans.push_back(findMedian());
        }
        
        return ans;   
    }
};

Input: arr[] = [5, 15, 1, 3, 2, 8]
Output: [5.0, 10.0, 5.0, 4.0, 3.0, 4.0] 
Explanation: 
After reading 1st element of stream – 5 -> median = 5.0
After reading 2nd element of stream – 5, 15 -> median = (5+15)/2 = 10.0 
After reading 3rd element of stream – 5, 15, 1 -> median = 5.0
After reading 4th element of stream – 5, 15, 1, 3 ->  median = (3+5)/2 = 4.0
After reading 5th element of stream – 5, 15, 1, 3, 2 -> median = 3.0
After reading 6th element of stream – 5, 15, 1, 3, 2, 8 ->  median = (3+5)/2 = 4.0

Input: arr[] = [2, 2, 2, 2]
Output: [2.0, 2.0, 2.0, 2.0]
Explanation: 
After reading 1st element of stream – 2 -> median = 2.0
After reading 2nd element of stream – 2, 2 -> median = (2+2)/2 = 2.0
After reading 3rd element of stream – 2, 2, 2 -> median = 2.0
After reading 4th element of stream – 2, 2, 2, 2 ->  median = (2+2)/2 = 2.0


//48. MERGE K SORTED ARRAYS       //{T.C = O(N*LOGK), S.C=O(N)}
//similar to merge k sorted lists (30b.)

You are given a 2D matrix mat[][] of size n x m. Each row in 
the matrix is sorted in non-decreasing order. Your task is to 
merge all the rows and return a single sorted array that 
contains all the elements of the matrix.

class Solution {
  public:
    vector<int>mergeTwoSortedArr(vector<int>&a, vector<int>&b){
        vector<int>ans;
        
        int i = 0, j = 0;
        while(i < a.size() && j < b.size()){
            if(a[i] < b[j]){
                ans.push_back(a[i]);
                i++;
            }else{
                ans.push_back(b[j]);
                j++;
            }
        }
        while(i < a.size()){
            ans.push_back(a[i]);
            i++;
        }
        while(j < b.size()){
            ans.push_back(b[j]);
            j++;
        }
        
        return ans;
    }
    
    vector<int>partitionAndMerge(vector<vector<int>>&mat, int start, int end){
        //base case
        if(start == end) return mat[start];
        
        int mid = start + (end - start)/2;
        
        vector<int>arr1 = partitionAndMerge(mat, start, mid);
        vector<int>arr2 = partitionAndMerge(mat, mid+1, end);
        
        return mergeTwoSortedArr(arr1, arr2);
    }
    
    vector<int> mergeArrays(vector<vector<int>> &mat) {
        int n = mat.size();
        //base case
        if(mat.empty()) return {};
        
        return partitionAndMerge(mat, 0, n-1);
    }
};

Input: mat[][] = [[1, 3, 5, 7],
                [2, 4, 6, 8], 
                [0, 9, 10, 11]]
Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
Explanation: Merging all elements from the 3 sorted arrays and sorting them results in: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11].

Input: mat[][] = [[1, 2, 3, 4], 
                [2, 2, 3, 4],
                [5, 5, 6, 6],
                [7, 8, 9, 9]]
Output: [1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 9] 
Explanation: Merging all elements from the 4 sorted arrays and sorting them results in:[1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 9]


/*GRAPH *************************************************** */

//49. DFS OF GRAPH               //{T.C = O(V+E), S.C = O(V)}

Given a connected undirected graph containing V vertices 
represented by a 2-d adjacency list adj[][], where each 
adj[i] represents the list of vertices connected to vertex i. Perform a Depth First Search (DFS) traversal starting from vertex 0, visiting vertices from left to right as per the given adjacency list, and return a list containing the DFS traversal of the graph.

Note: Do traverse in the same order as they are in the given 
adjacency list.

class Solution {
  public:
    void dfsOfGraph(vector<vector<int>>&adj, vector<int>&ans, vector<bool>&vis, int node){
        vis[node] = true;
        ans.push_back(node);
        for(auto it : adj[node]){
            if(!vis[it]){
                dfsOfGraph(adj, ans, vis, it);           //it becomes current node
            }   
        }
    }
    vector<int> dfs(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<int>ans;
        vector<bool>vis(n, false);
        dfsOfGraph(adj, ans, vis, 0);         //0 = intial node
        
        return ans;
    }
};

Input: adj[][] = [[2, 3, 1], [0], [0, 4], [0], [2]]
Output: [0, 2, 4, 3, 1]
Explanation: Starting from 0, the DFS traversal proceeds as follows:
Visit 0 → Output: 0 
Visit 2 (the first neighbor of 0) → Output: 0, 2 
Visit 4 (the first neighbor of 2) → Output: 0, 2, 4 
Backtrack to 2, then backtrack to 0, and visit 3 → Output: 0, 2, 4, 3 
Finally, backtrack to 0 and visit 1 → Final Output: 0, 2, 4, 3, 1

Input: adj[][] = [[1, 2], [0, 2], [0, 1, 3, 4], [2], [2]]
Output: [0, 1, 2, 3, 4]
Explanation: Starting from 0, the DFS traversal proceeds as follows: 
Visit 0 → Output: 0 
Visit 1 (the first neighbor of 0) → Output: 0, 1 
Visit 2 (the first neighbor of 1) → Output: 0, 1, 2 
Visit 3 (the first neighbor of 2) → Output: 0, 1, 2, 3 
Backtrack to 2 and visit 4 → Final Output: 0, 1, 2, 3, 4


//50. BFS OF GRAPH              //{T.C = O(V+E), S.C = O(V)}

Given a connected undirected graph containing V vertices, 
represented by a 2-d adjacency list adj[][], where each 
adj[i] represents the list of vertices connected to vertex i. Perform a Breadth First Search (BFS) traversal starting from vertex 0, visiting vertices from left to right according to the given adjacency list, and return a list containing the BFS traversal of the graph.

Note: Do traverse in the same order as they are in the given 
adjacency list.

class Solution {
  public:
    void bfsOfGraph(vector<vector<int>>&adj, vector<int>&ans, vector<bool>&vis, int node){
        vis[node] = true;
        
        queue<int>q;
        q.push(node);
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto it : adj[frontNode]){
                if(!vis[it]){
                    q.push(it);
                    vis[it] = true;
                }
            }
        }
    }
    vector<int> bfs(vector<vector<int>> &adj) {
        int n = adj.size(); 
        vector<int>ans;
        vector<bool>vis(n, false);
        bfsOfGraph(adj, ans, vis, 0);                   //0 = initial node
        
        return ans;
    }
};

Input: adj[][] = [[2, 3, 1], [0], [0, 4], [0], [2]]
Output: [0, 2, 3, 1, 4]
Explanation: Starting from 0, the BFS traversal will follow these steps: 
Visit 0 → Output: 0 
Visit 2 (first neighbor of 0) → Output: 0, 2 
Visit 3 (next neighbor of 0) → Output: 0, 2, 3 
Visit 1 (next neighbor of 0) → Output: 0, 2, 3, 1
Visit 4 (neighbor of 2) → Final Output: 0, 2, 3, 1, 4

Input: adj[][] = [[1, 2], [0, 2], [0, 1, 3, 4], [2], [2]]
Output: [0, 1, 2, 3, 4]
Explanation: Starting from 0, the BFS traversal proceeds as follows: 
Visit 0 → Output: 0 
Visit 1 (the first neighbor of 0) → Output: 0, 1 
Visit 2 (the next neighbor of 0) → Output: 0, 1, 2 
Visit 3 (the first neighbor of 2 that hasnt been visited yet) → Output: 0, 1, 2, 3 
Visit 4 (the next neighbor of 2) → Final Output: 0, 1, 2, 3, 4


//51. NUMBER OF ISLANDS         //{T.C = (N*M), S.C = O(N*M)}

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting 
adjacent lands horizontally or vertically. You may assume all 
four edges of the grid are all surrounded by water.

class Solution {
public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int i, int j, int n, int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    void dfs(vector<vector<char>>&grid, vector<vector<bool>>&vis, int i, int j){
        int n = grid.size(), m = grid[0].size();

        vis[i][j] = true;
        for(auto it : directions){
            int newRow = i + it[0];        //next row
            int newCol = j + it[1];        //next col

            if(isValid(newRow, newCol, n, m) && !vis[newRow][newCol] && grid[newRow][newCol] == '1'){
                dfs(grid, vis, newRow, newCol);
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>>vis(n, vector<bool>(m, false));
        int count = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(!vis[i][j] && grid[i][j] == '1'){
                    count++;
                    dfs(grid, vis, i, j);
                }
            }
        }
        return count;
    }
};

Example 1:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3


//54. UNDIRECT GRAPH CYCLE      //{T.C = O(V+E), S.C = O(V+E)}
//or DETECT CYCLE IN UNDIRECTED GRAPH

Given an undirected graph with V vertices and E edges, represented 
as a 2D vector edges[][], where each entry edges[i] = [u, v] 
denotes an edge between vertices u and v, determine whether 
the graph contains a cycle or not.

Note: The graph can have multiple component.

class Solution {
  public:
    bool dfsUndirGraphCycle(unordered_map<int, vector<int>>&adj, vector<bool>&vis, int node, int parent){
        vis[node] = true;
        for(auto it : adj[node]){
            if(!vis[it]){
                if(dfsUndirGraphCycle(adj, vis, it, node)){   //it-> current, node -> becomes parent
                    return true;                           //just passing the result upward (not cycle detect logic)
                }
            }else if(it != parent) return true;            //visited again but not parent (cycle present)
        }
        
        return false;
    }
    bool isCycle(int V, vector<vector<int>>& edges) {
        //create adjacency list
        unordered_map<int, vector<int>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            
            adj[u].push_back(v);
            adj[v].push_back(u);                        //undirected both required
        }
        
        vector<bool>vis(V, false);
        // return dfsUndirGraphCycle(adj, vis, 0, -1);             //0 = initial node, -1 = inital parent
        for(int i = 0; i < V ; i++){                   //for disconnected component
            if(!vis[i] && dfsUndirGraphCycle(adj, vis, i, -1)) return true; 
        }
        
        return false;
    }
};

Input: V = 4, E = 4, edges[][] = [[0, 1], [0, 2], [1, 2], [2, 3]]
Output: true
Explanation: 
1 -> 2 -> 0 -> 1 is a cycle.

Input: V = 4, E = 3, edges[][] = [[0, 1], [1, 2], [2, 3]]
Output: false
Explanation:  
No cycle in the graph.


//55. DIRECT GRAPH CYCLE    //{T.C =  O(V+E), S.C = O(V+E)}
//or DETECT CYCLE IN DIRECTED GRAPH

Given a Directed Graph with V vertices (Numbered from 0 to V-1) 
and E edges, check whether it contains any cycle or not.
The graph is represented as a 2D vector edges[][], where each 
entry edges[i] = [u, v] denotes an edge from vertex u to v.

class Solution {
  public:
    bool dfsDirGraphCycle(unordered_map<int, vector<int>>&adj, vector<bool>&vis, vector<bool>&dfsVis, int node){
        vis[node] = true;
        dfsVis[node] = true;
        for(auto it : adj[node]){
            if(!vis[it]){
                if(dfsDirGraphCycle(adj, vis, dfsVis, it)) return true;   //it -> current
            }else if(dfsVis[it]) return true;            //vis -> true, dfsVis -> true -> cycle
        }
        dfsVis[node] = false;                      //reset for next iteration
        return false;
    }
    bool isCyclic(int V, vector<vector<int>> &edges) {
        unordered_map<int, vector<int>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            
            adj[u].push_back(v);                     //directed so only u -> v
        }
        
        vector<bool>vis(V, false);
        vector<bool>dfsVis(V, false);
        
        for(int i = 0; i < V; i++){
            if(!vis[i] && dfsDirGraphCycle(adj, vis, dfsVis, i)) return true;
        }
        
        return false;
    }
};

Input: V = 4, edges[][] = [[0, 1], [1, 2], [2, 0], [2, 3]]
Output: true
Explanation: The diagram clearly shows a cycle 0 → 1 → 2 → 0

Input: V = 4, edges[][] = [[0, 1], [0, 2], [1, 2], [2, 3]]
Output: false
Explanation: no cycle in the graph


//56. TOPOLOGICAL SORT         //{T.C = O(V+E), S.C = O(V+E)}

Given a Directed Acyclic Graph (DAG) of V (0 to V-1) vertices 
and E edges represented as a 2D list of edges[][], where each 
entry edges[i] = [u, v] denotes a directed edge u - > v Return 
the topological sort for the given graph.

Topological sorting for Directed Acyclic Graph (DAG) is a linear 
ordering of vertices such that for every directed edge u - > v, 
vertex u comes before v in the ordering.
Note: As there are multiple Topological orders possible, you 
may return any of them. If your returned Topological sort is 
correct then the output will be true else false.

class Solution {
  public:
    vector<int> topoSort(int V, vector<vector<int>>& edges) {
        //create adjacency list
        unordered_map<int, vector<int>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            
            adj[u].push_back(v);
        }
        
        //1. fill indegree vector
        vector<int>inDegree(V, 0);
        for(int i = 0; i < V; i++){
            for(auto it : adj[i]) inDegree[it]++;
        }
        
        //2. fill queue (if its inDegree 0)
        queue<int>q;
        for(int i = 0; i < V; i++){
            if(inDegree[i] == 0) q.push(i);             //push node not its indegree
        }
        
        //3. simple bfs and store ans
        vector<int>ans;
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0) q.push(it);       //again push if nbr also 0
            }
        }
        
        return ans;
    }
};

Input: V = 4, E = 3, edges[][] = [[3, 0], [1, 0], [2, 0]]
Output: true
Explanation: The output true denotes that the order is valid. Few valid Topological orders for the given graph are:
[3, 2, 1, 0]
[1, 2, 3, 0]
[2, 3, 1, 0]

Input: V = 6, E = 6, edges[][] = [[1, 3], [2, 3], [4, 1], [4, 0], [5, 0], [5, 2]]
Output: true
Explanation: The output true denotes that the order is valid. Few valid Topological orders for the graph are:
[4, 5, 0, 1, 2, 3]
[5, 2, 4, 0, 1, 3]


//57. COURSE SCHEDULE 1          //{T.C = O(V+E), S.C = O(V+E)}

There are a total of numCourses courses you have to take, 
labeled from 0 to numCourses - 1. You are given an array 
prerequisites where prerequisites[i] = [ai, bi] indicates 
that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 
you have to first take course 1.
Return true if you can finish all courses. Otherwise, return 
false.

class Solution {
public:
    vector<int>topoSort(vector<vector<int>>&edges, int n){
        //create adjacency list
        unordered_map<int, vector<int>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];

            adj[v].push_back(u);                //reverse edge
        }

        //1. fill indegree vector
        vector<int>inDegree(n, 0);
        for(int i = 0 ; i < n; i++){
            for(auto it : adj[i]) inDegree[it]++;
        }

        //2. fill queue if indegree 0
        queue<int>q;
        for(int i = 0 ; i < n; i++){
            if(inDegree[i] == 0) q.push(i);       //i-> node (push node not val)
        }

        //3. simple dfs and return ans;
        vector<int>ans;
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0) q.push(it);     //again push for 0 indegree
            }
        }

        return ans;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int>topoAns = topoSort(prerequisites, numCourses);
        return topoAns.size() == numCourses;         ///all traverse valid topsort (ans exist)
    }
};


Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.


//58. COURSE SCHEDULE 2      //{T.C = O(V+E), S.C = O(V+E)}

There are a total of numCourses courses you have to take, 
labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 
you have to first take course 1.
Return the ordering of courses you should take to finish all 
courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

class Solution {
public:
        vector<int>topoSort(vector<vector<int>>&edges, int n){
        //create adjacency list
        unordered_map<int, vector<int>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];

            adj[v].push_back(u);                //reverse edge
        }

        //1. fill indegree vector
        vector<int>inDegree(n, 0);
        for(int i = 0 ; i < n; i++){
            for(auto it : adj[i]) inDegree[it]++;
        }

        //2. fill queue if indegree 0
        queue<int>q;
        for(int i = 0 ; i < n; i++){
            if(inDegree[i] == 0) q.push(i);       //i-> node (push node not val)
        }

        //3. simple dfs and return ans;
        vector<int>ans;
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0) q.push(it);     //again push for 0 indegree
            }
        }

        return ans;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int>ans = topoSort(prerequisites, numCourses);   

        if(ans.size() == numCourses) return ans;     //valid (no cycle present)
        return {};
    }
};

Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].

Example 2:
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

Example 3:
Input: numCourses = 1, prerequisites = []
Output: [0]


//61. DIJKSTRA ALGORITHM       //{T.C = O(E*LOGV), S.C = O(V+E)}

Given an undirected, weighted graph with V vertices numbered 
from 0 to V-1 and E edges, represented by 2d array edges[][], 
where edges[i]=[u, v, w] represents the edge between the nodes 
u and v having w edge weight.
You have to find the shortest distance of all the vertices from 
the source vertex src, and return an array of integers where 
the ith element denotes the shortest distance between ith node 
and source vertex src.

Note: The Graph is connected and doesn't contain any negative 
weight edge.
It is guaranteed that all the shortest distance will fit in 
a 32-bit integer.

class Solution {
  public:
    typedef pair<int,int>P;                             //distance source
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        //create adjacency
        unordered_map<int, vector<pair<int,int>>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            int w = it[2];
            
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        //real dijkstra
        vector<int>minDis(V, INT_MAX);                  //initialize with infinity
        minDis[src] = 0;                                //self node distance 0
        priority_queue<P, vector<P>, greater<P>>pq;
        pq.push({0, src});                              //distance, source
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int dis = topNode.first;
            int u   = topNode.second;
            
            for(auto it : adj[u]){
                //u -> v, w
                int v = it.first;
                int d = it.second;
                
                if(dis + d < minDis[v]){
                    minDis[v] = dis + d;
                    pq.push({dis+d, v});
                }
            }
        }
        
        return minDis;
    }
};

Input: V = 3, edges[][] = [[0, 1, 1], [1, 2, 3], [0, 2, 6]], src = 2
Output: [4, 3, 0]
Explanation:
Shortest Paths:
For 2 to 0 minimum distance will be 4. By following path 2 -> 1 -> 0
For 2 to 1 minimum distance will be 3. By following path 2 -> 1
For 2 to 2 minimum distance will be 0. By following path 2 -> 2

Input: V = 5, edges[][] = [[0, 1, 4], [0, 2, 8], [1, 4, 6], [2, 3, 2], [3, 4, 10]], src = 0
Output: [0, 4, 8, 10, 10]
Explanation: 
Shortest Paths: 
For 0 to 1 minimum distance will be 4. By following path 0 -> 1
For 0 to 2 minimum distance will be 8. By following path 0 -> 2
For 0 to 3 minimum distance will be 10. By following path 0 -> 2 -> 3 
For 0 to 4 minimum distance will be 10. By following path 0 -> 1 -> 4



















//extra for now
/*BINARY SEARCH / TWO POINTERS *****************************/

// ALLOCATE MINIMUM PAGES      {T.C = O(N*LOG(SUM), S.C = O(N))}

Given an array arr[] of integers, where each element arr[i] 
represents the number of pages in the i-th book. You also have
an integer k representing the number of students. The task is 
to allocate books to each student such that:

Each student receives atleast one book.
Each student is assigned a contiguous sequence of books.
No book is assigned to more than one student.
All books must be allocated.
The objective is to minimize the maximum number of pages assigned 
to any student. In other words, out of all possible allocations, 
find the arrangement where the student who receives the most pages
still has the smallest possible maximum.

Note: If it is not possible to allocate books to all students, return -1.

class Solution {
  public:
    bool isValid(vector<int>&arr, int k, int mid){
        int n = arr.size();
        
        int students = 1, sum = 0;            //atleast 1 student
        for(int i = 0; i < n; i++){
            sum += arr[i];
            
            if(sum > mid){
                students++;
                sum = arr[i];              //new sum for next student
            }
            
            if(students > k) return false;
        }
        return true;
    }
    int findPages(vector<int> &arr, int k) {
        
        int n = arr.size();
        //base case
        if(n < k) return -1;
        
        int sumOfPages = 0;
        for(auto it : arr) sumOfPages += it;
        
        int maxNoOfPages = *max_element(arr.begin(), arr.end());
        
        int start = maxNoOfPages , end = sumOfPages;          //range single(max page) to sum of pages a person can read
        
        int ans = -1;
        while(start <= end){
            int mid = start + (end - start)/2;
            if(isValid(arr, k, mid)){
                ans = mid;
                end = mid-1;
            }else{
                start = mid+1;
            }
        }
        return ans;
    }
};

Input: arr[] = [12, 34, 67, 90], k = 2
Output: 113
Explanation: Allocation can be done in following ways:
=> [12] and [34, 67, 90] Maximum Pages = 191
=> [12, 34] and [67, 90] Maximum Pages = 157
=> [12, 34, 67] and [90] Maximum Pages = 113.
The third combination has the minimum pages assigned to a 
student which is 113.

Input: arr[] = [15, 17, 20], k = 5
Output: -1
Explanation: Since there are more students than total books,
its impossible to allocate a book to each student.


//15. MERGE SORTED ARRAY       {T.C = O(N+M), S.C = O(1)}

You are given two integer arrays nums1 and nums2, sorted in 
non-decreasing order, and two integers m and n, representing 
the number of elements in nums1 and nums2 respectively.
Merge nums1 and nums2 into a single array sorted in non-decreasing order.
The final sorted array should not be returned by the function, but instead be stored inside the array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(i >= 0 && j >= 0){
            if(nums1[i] < nums2[j]){           //2nd array's should put at last
                nums1[k] = nums2[j];
                j--;
            }else{                             //1st array's should put at last
                nums1[k] = nums1[i];
                i--;
            }
            k--;
        }
        while(j >= 0){                        //copy remaining element of 2nd
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
};

Example 1:
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.

Example 2:
Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays we are merging are [1] and [].
The result of the merge is [1].

Example 3:
Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays we are merging are [] and [1].
The result of the merge is [1].
Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.
