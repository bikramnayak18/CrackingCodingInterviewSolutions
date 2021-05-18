#include<iostream>
using namespace std;
class Solution {
public:
    int longestValidParentheses(string s) {
        int count =0;
        int max = 0;
        int l=0;
        for(int i=0;i<s.length();i++){
            if(s[i]=='(')
                count++;
            else if(s[i] ==')')
                count--;
            l++;
            if(count==0)
                max = std::max(l,max);
            if(count<0){
                l = 0;
                count = 0;
            }
        }
        count =0;
        l=0;
        for(int i=s.length()-1;i>=0;i--){
            if(s[i]==')')
                count++;
            else if(s[i]=='(')
                count--;
            l++;
            if(count==0)
                max = std::max(l,max);
            if(count<0){
                l = 0;
                count =0;
            }
        }
        return max;
    }
};