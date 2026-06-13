//1. KADANE ALGORITHM OR MAXIMUM SUBARRAY            //T.C = O(N), S.C = O(1)
Given an integer array nums, find the subarray with the largest 
sum, and return its sum.

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


//2. Best Time to Buy and Sell Stock                        //T.C = O(N), S.C = O(1)
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


//3. Best Time to Buy and Sell Stock (IV) [with limit]                            //{T.C = O(N*K), S.C = O(N*K)}
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


//4. Trapping Rain Water           {T.C = (N), S.C = O(N)}
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


//5. Chocolate Distribution Problem              //{T.C = O(N*LOGN), S.C = O(1)}
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


//8. MERGE INTERVALS            //{T.C = O(N*LOGN), S.C = O(N)}
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
 

//9. ROTATE IMAGE                //{T.C = O(N^2), S.C = O(1)}

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


//10. SPIRAL MATRIX                {T.C = O(N*M), S.C = O(N)}

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


//12. VALID/BALANCED PARENTHESES    {T.C = O(N), S.C = O(N)}
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


//14. ALLOCATE MINIMUM PAGES      {T.C = O(N*LOG(SUM), S.C = O(N))}

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
it's impossible to allocate a book to each student.


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


//17. DETECT AND REMOVE LOOP IN LL   {T.C = O(N), S.C = O(1)}

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


//18a. MERGE 2 SORTED LIST     {T.C  O(N+M), S.C = O[aux](N+M)}

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


//18b. MERGE K SORTED LL          {T.C = O(N*LOGK), S.C = O[aux](N)}

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


//19. LEFT VIEW OF BINARY TREE      {T.C = O(N), S.C = O(H)}

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


//20. BINARY TREE RIGHT SIDE VIEW   {T.C = O(N), S.C = O(H)}

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


//21. LEVEL ORDER TRAVERSAL      {T.C = O(N), S.C = O(N)}

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


//22. TOP VIEW OF BINARY TREE       {T.C = O(N*LOGN), S.C = O(N)}
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


//23. BOTTOM VIEW OF BINARY TREE   {T.C = O(N*LOGN), S.C = O(N)}

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
    

//24. BINARY TREE ZIGZAG LEVEL ORDER TRAVERSAL  //{T.C = O(N), S.C= O(N)}

Given the root of a binary tree, return the zigzag level order 
traversal of its nodes' values. (i.e., from left to right, 
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


//25. TREE BOUNDARY TRAVERSAL    {T.C = O(N), S.C = O(H)}

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


//26. MAXIMUM DEPTH OF BINARY TREE   {T.C = O(N), S.C= O(H)}
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


//27. DIAMETER OF BINARY TREE    {T.C = O(N), S.C = O(H)}

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
