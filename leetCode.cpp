#include<iostream>
#include<unordered_set>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<map>
using namespace std;

int getMax(vector<vector<int>> &courses, int start, int maxVal, unordered_set<int> cid){
    int duration, endDay;
    int currMax = 0;
    for(int i=0;i<courses.size();i++){
        if(cid.find(i) == cid.end()){
            duration = courses[i][0];
            endDay = courses[i][1];
            if(start+duration < endDay){
                cid.insert(i);
                currMax = std::max(getMax(courses, start + duration, maxVal+1, cid), currMax);
                cid.erase(i);
            }
        }
    }
    return currMax;
}

bool compareEnd(const vector<int>& a,const vector<int>& b){
    return a[1]<b[1];
}

int scheduleCourse(vector<vector<int>>& courses) {
        unordered_set<int> cid;
        sort(courses.begin(),courses.end(), compareEnd);
        return getMax(courses, 0, 0, cid);
    }

int lengthOfLongestSubstring(string s) {
        int start = 0;
        int max = 0;
        unordered_map<char, int> map;
        for(int i=0;i<s.length();i++){
            char c = s[i];
            if(map.find(c) != map.end())//duplicate is found
            {
                start = std::max(start, map[c] + 1);
            }
            max = std::max(max, i - start+1);
            map[c] = i;
        }
        return max;
    }

string checkPallindrome(string s, int size);

string longestPalindrome(string s) {
        int n = s.length();
        string isPallindrome = "";
        for(int size = n ;size>0;size--){
            isPallindrome = checkPallindrome(s, size);
            if(isPallindrome!="")
                return isPallindrome;
        }
        return isPallindrome;
    }
    
    string checkPallindrome(string s, int size){
        int count = s.length() - size;
        bool found = false;
        for(int i =0;i<=count;i++){
            int start=i;
            int end = size - 1 +i;
            found = true;
            while(start<=end){
                if(s[start++] != s[end--]){
                    found = false;
                    break;
                }
            }
            if(found){
                cout<<"Start"<<i<<" size "<<size<<endl;
                return s.substr(i, size);            
            }
        }
        return "";
    }

 string convert(string s, int numRows) {
        bool down = true;
        int crawl = 0;
        vector<char> zigzag[numRows];
        for(int i=0;i<s.length();i++){
            zigzag[crawl].push_back(s[i]);
            crawl = down?crawl+1:crawl-1;
            if(crawl==-1)
                crawl += 2, down = true;
            else if(crawl == numRows)
                crawl -= 2, down = false;
        }
        int index =0;
        for(int i=0;i<numRows;i++){
            for(auto itr=zigzag[i].begin();itr!=zigzag[i].end();itr++){
                s[index++] = *itr;
            }
        }
        return s;
    }
  string reverseInt(int x){
        return x==0?"": (char) (x%10+'0')+ reverseInt(x/10);
    }
int reverse(int x) {
        bool isNegative = x<0;
        x = x<0?x*-1:x;
        string reversed = reverseInt(x);
        if(reversed.length()<10)
            return isNegative?-1*stoi(reversed):stoi(reversed);
        else if(reversed.length()>10)
            return 0;
        else{
            if(reversed[0] =='1')
                return isNegative?-1*stoi(reversed):stoi(reversed);
            else if(((int)reversed[0] - '0')>2)
                return 0;
            else{
                int temp = stoi(reversed.substr(1,9));
                if(temp>147483647)                                
                    return 0;
                else 
                    return isNegative?-1*stoi(reversed):stoi(reversed);
            }
        }
    }
     //start and end are inclusive
    int findMaxIndex(vector<int>& height, int start, int end){
        int maxIndex = start;
        for(int i=start+1;i<=end;i++){
            if(height[maxIndex]< height[i]){
                maxIndex = i;
            }
        }
        return maxIndex;
    }
  int maxArea(vector<int>& height) {
        if(height.size()==0)
            return 0;
        int maxWater = 0;
        int minVal = 0;
        int subMax=0;
        int size = height.size();
        int currLeftMax = 0;
        for(int i=0;i<size-1;i++){
            if(height[i]>currLeftMax){
                currLeftMax = height[i];
                if(subMax<=i)
                    subMax = findMaxIndex(height, i+1, size-1);
                
                for(int j=size-1;j>i && j>=subMax;j--){
                    minVal = std::min(height[i],height[j]);
                    maxWater = std::max(minVal * (j-i), maxWater);
                }
            }
        }
        return maxWater;
    }
    bool isValid(char a, char b);
    int romanToInt(string s) {
   unordered_map<char,int> map {{'I', 1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}};

        int size = s.length();
        int output = map[s[size-1]];
        for(int i=size-2;i>=0;i--){
            if(isValid(s[i],s[i+1]))
                output -= map[s[i]];
            else
                output += map[s[i]];
                
        }
        return output;        
    }
    
    bool isValid(char a, char b){
        if(a=='I' &&(b=='V' || b=='X'))
            return true;
        else if(a=='X' &&(b=='L' || b=='C'))
            return true;
        else if(a=='C' &&(b=='D' || b=='M'))
            return true;
        else 
            return false;
    }


    string intToRoman(int input){
        unordered_map<int, string> m={{1,"I"},{4,"IV"},{5,"V"},{9,"IX"},{10,"X"},{40,"XL"},{ 50,"L"},{90,"XC"},{100,"C"},{400,"CD"}
        ,{500,"D"},{900,"CM"} ,{1000,"M"}
         };
        vector<int> numerics = {1,4,5,9,10,40,50,90,100,400,500,900,1000};
        int n = numerics.size();
        string output;
        int i = n-1;
        while(input>0){
            while(i>=0){
                if(numerics[i]<=input)
                {
                    input -= numerics[i];
                    output += m[numerics[i]];
                }else{
                    i--;
                }
            }
            if(i<0 && input>0)
                return "invalid";
        }
        cout<<output;
        return output;
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> output;
        int n = nums.size();
        for(int i=0;i<n-2;i++){
            if(!(i>0 && nums[i]==nums[i-1])){//new element
                int first = nums[i];
                int secondPair = 0 - first;
                unordered_set<int> remainders ;
                unordered_set<int> visited;
                for(int j=i+1;j<n;j++){
                    
                    int second = nums[j];                    
                    int third = secondPair - second;
                    if(visited.find(second) != visited.end())continue;
                    if(remainders.find(third)!=remainders.end()){
                        vector<int> triplet = {first, second, third};
                        output.push_back(triplet);
                        visited.insert(second);
                        visited.insert(third);
                    }
                    remainders.insert(second);
                    
                }
            }
        }
        return output;    
    }

    bool threeSum(vector<int>& nums, int target) {
        int n = nums.size();
        for(int i=0;i<n-2;i++){
            if(!(i>0 && nums[i]==nums[i-1])){//new element
                int first = nums[i];
                int secondPair = target - first;
                unordered_set<int> remainders ;
                for(int j=i+1;j<n;j++){
                    int second = nums[j];                    
                    int third = secondPair - second;
                    if(remainders.find(third)!=remainders.end()){
                        return true;
                    }
                    remainders.insert(second);
                }
            }
        }
        return false;    
    }

    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int n = nums.size();
        int min = nums[0]+nums[1]+nums[2];
        int max = nums[n-3] + nums[n-2] + nums[n-1];
        if(target>= max)
            return max;
        else if(target<=min)
            return min;
        int minTarget = target;
        int maxTarget = target ;
        bool found = false;
        while(minTarget>=min && maxTarget<=max){
            target = minTarget--;
            found = threeSum(nums,target);
            if(!found){
                target = maxTarget++;
                found = threeSum(nums, target);
            }
            if(found)
                return target;
        }
        
        while(minTarget>min){
            found = threeSum(nums, minTarget--);
            if(found)
                return minTarget++;
        }
        while(maxTarget<max){
            found = threeSum(nums, maxTarget++);
            if(found)
                return maxTarget--;
        }
        return -1;
    }
    bool swap(vector<int>& nums, int i, int j){
        cout<<i <<":"<<j<<endl;
        if(i==j || nums[i] == nums[j])
            return false;
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        return true;
    }
    int removeDuplicates(vector<int>& nums) {
        int size = nums.size();
        if(size<=1)
            return size;
        int swapIndex = -1;
        int count =1;
        for(int i=1;i<size;i++){
            if(nums[i-1]==nums[i]){
                if(swapIndex==-1)
                    swapIndex = i;
                while(nums[i-1] == nums[i]){
                    if(i==size-1)return count;
                    i++;
                }
                
            }
            if(swapIndex!=-1)
                swap(nums, swapIndex++, i);
            count++;
        }
        return count;
    }
    
    
    int move(vector<int>& nums, int size, int index, int count, unordered_map<int,int>& memo, int& minCount){
        if(index == size - 1){
            cout<<"count"<<count<<":"<<minCount<<endl;
            minCount = std::min(minCount, count);
            return minCount;
        }
        if(memo.find(index) != memo.end()){
            return memo[index]==INT_MAX?INT_MAX:memo[index] + count;
        }
        int min = INT_MAX;
        for(int i=nums[index];i>0;i--){
            if((index+i)<size && (count)<minCount)
                min = std::min(min, move(nums, size, index+i, count+1, memo,minCount));
        }
        memo[index] = min==INT_MAX?INT_MAX: min - count;
        return min;
    }

    int jump(vector<int>& nums) {
        if(nums.size() == 1)
            return 0;
        unordered_map<int, int> memo;
        int minCount = INT_MAX;
        return move(nums, nums.size(), 0, 0, memo, minCount);
    }
        void swapArr(vector<int>& nums, int a, int b){
        int temp = nums[a];
        nums[a] = nums[b];
        nums[b] = temp;
    }
    
    bool valid(int a, int size, vector<int>& nums){
        if(a+1 == nums[a])return false;
        if(a>=0 && a<size)
            return true;
        return false;
    }
string multiply(string num1, string num2) {
        //char output[num1.length() + num2.length()];
        int arr[num1.length()+num2.length()]={0};
        int startIndex = 0, carry=0;
        for(int i=num2.length()-1;i>=0;i--){
            startIndex = num2.length()-i-1;
            carry = 0;
            for(int j=num1.length()-1;j>=0;j--){
                int a = num2[i] -'0';
                int b = num1[j] - '0';
                int temp = a*b + carry + arr[startIndex];
                arr[startIndex++] = temp%10;
                carry = temp/10;
            }            
            arr[startIndex++] = carry;
        }
        string output="";
        int n = num1.length() + num2.length();
        for(int i=n-1;i>=0;i--){
            if(output=="" && arr[i]!=0)
               output += to_string(arr[i]);
            else if(output!="")
                output += to_string(arr[i]);
        }
        return output;
        return "";
    }
 int firstMissingPositive(vector<int>& nums) {
        int i =0;
        int size = nums.size();
        for(int i=0;i<size;i++){
            while(true){
                int index = nums[i]-1;
                int index2 = i;
                if(valid(index, size, nums)){
                    swapArr(nums, index, index2);
                }else{
                    break;
                }
            }
        }
        for(int i=0;i<size;i++)
            cout<<nums[i]<<" ";
        return 1;
    }
    
int removeDuplicates2(vector<int>& nums){
        int count = 0;
        int swap = -1;
        for(int i=1;i<nums.size();i++){
            
            if(swap==-1 && nums[i-1] == nums[i])
                swap = i;
            if(swap>=0 && nums[i-1] != nums[i])
                nums[swap++] = i;
        }
        
        for(int i=0;i<swap;i++)
            cout<<nums[i]<<" ";
        return swap;
    }   
    

int main(){
    vector<int> input = {-2,-1,0,0,1,2};
    removeDuplicates2(input);
    // vector<int> input = {3,4,-1,1};
    // firstMissingPositive(input);
    //multiply("9","99");
    // vector<int> input = {9,8,2,2,0,2,2,0,4,1,5,7,9,6,6,0,6,5,0,5};
    // int jumps = jump(input);
    // cout<<"min jumps : "<<jumps;
    // vector<int> nums = {0,0,1,1,1,2,2,3,3,4};
    // removeDuplicates(nums);
    //int arr[] = 
    // vector<int> input = {-1,2,1,-4};
    // cout<<"output"<<threeSumClosest(input,1);
    //intToRoman(1994);
    // int arr[]={1,3,2,5,25,24,5};
    // vector<int> input(arr, arr + sizeof(arr)/sizeof(arr[0]));
    // maxArea(input);
    //longestPalindrome("babad");
    // lengthOfLongestSubstring("abba");
    // vector<vector<int>> courses;
    // vector<int> course1;
    // course1.push_back(100);
    // course1.push_back(200);

    // vector<int> course2;
    // course2.push_back(200);
    // course2.push_back(1300);

    // vector<int> course3;
    // course3.push_back(1000);
    // course3.push_back(1250);

    // vector<int> course4;
    // course4.push_back(2000);
    // course4.push_back(3200);

    // courses.push_back(course1);
    // courses.push_back(course2);
    // courses.push_back(course3);
    // courses.push_back(course4);

    // scheduleCourse(courses);
}