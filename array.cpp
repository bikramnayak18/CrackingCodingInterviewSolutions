#include<iostream>
#include<vector>
#include<limits>
using namespace std;


 // Definition for singly-linked list.
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
    ListNode* resultHead = NULL;
    ListNode* crawl = NULL;
public:
    ListNode* getNode(){
        if(!resultHead){
                resultHead = new ListNode();
                crawl = resultHead;
        }else{
                crawl->next = new ListNode();
                crawl = crawl->next;
        }

        return crawl;
    }

    int calculateSum(int a, int b, int carry){
        return ( a+b+carry)%10;
    }

    int calculateCarry(int a, int b, int carry){
        return (a+b+carry)/10;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry =0;
        int sum = 0;
        int a, b;
        while(l1 || l2){
            ListNode* currNode = getNode();
            a = l1!=NULL?l1->val:0;
            b = l2!=NULL?l2->val:0;
            currNode->val = calculateSum(a, b, carry);
            carry = calculateCarry(a, b, carry);
            l1 = l1!=NULL?l1->next:l1;
            l2 = l2!=NULL?l2->next:l2;
        }

        if(carry>0)
        {
            ListNode* currNode = getNode();
            currNode->val = carry;
        }
        
    }

    ListNode* addTwoNumbers2(ListNode* l1, ListNode* l2) {
        int m=0, n=0;
        ListNode* t = l1;
        ListNode* tt = l2;
        while(t!=NULL){
            m++;
            t = t->next;
        }
        while(tt){
            n++;
            tt = tt->next;
        }
        //cout<<"m: "<<m<<" n: "<<n<<endl;
        int carry = m>n?createResult(l1, l2, abs(m-n)):createResult(l2, l1, abs(m-n));
        if(carry>0){
            crawl->next = new ListNode();
            crawl = crawl->next;
            crawl->val = carry;
        }
        return resultHead;
    }
    
    int createResult(ListNode* l1, ListNode* l2, int diff){
        int carry=0;
        if(diff>0)
            carry = createResult(l1->next, l2, diff-1);
        else if(l1 && l2)
            carry = createResult(l1->next, l2->next, diff);
        else if(l1)
            carry = createResult(l1->next, l2, diff);
        else if(l2)            
            carry = createResult(l1, l2->next, diff);
        else
            return 0;
        if(!resultHead)            
        {
            resultHead = new ListNode();
            crawl = resultHead;
        }
        else{
            crawl->next = new ListNode();
            crawl = crawl->next;
        }
        //crawl->val = diff>0?l1->val: l1->val + l2->val;
        int val = diff>0?l1->val + carry:l1->val+l2->val+carry;
        crawl->val = val%10;
        carry = val/10;
        return carry;
    }
   
};

int main(){
    double minSoFar =numeric_limits<double>::max();
    vector<double> input;
    input.push_back(12);
    input.push_back(11);
    input.push_back(13);
    input.push_back(9);
    input.push_back(12);
    input.push_back(8);
    input.push_back(14);
    input.push_back(13);
    input.push_back(15);
    vector<double> firstProfit(input.size(),0);
    int n = input.size();
    double maxTotal = 0 ;
    for(int i=0;i<n;i++){
        minSoFar = min(minSoFar, input[i]);
        maxTotal = std::max(maxTotal, input[i] - minSoFar);
        firstProfit[i] = maxTotal;
    }

    double maxSoFar = numeric_limits<double>::min();
    for(int i = input.size()-1;i>0;i--){
        maxSoFar = max(maxSoFar, input[i]);
        maxTotal = max(maxTotal, maxSoFar - input[i] + firstProfit[i-1]);
    }

    cout<<maxTotal;
}