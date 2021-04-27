#include<iostream>
#include<cmath>
using namespace std;
class node{
    public:int data;
    public:node *next=NULL;
};

class linkList
{
    node *head, *tail;
    public: linkList(){
        head = NULL;
        tail = NULL;
    }

    void add(int n ){
        node *temp = new node;
        temp->data = n;
        temp->next = NULL;
        if(head == NULL){
            head = temp;
            tail = temp;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
    }

    void print(){
        node *itr = head;
        if(head == NULL) cout<<"head is null";
        while(itr!=NULL)
        {
            cout<<itr->data<<",";
            itr = itr->next;
        }
        cout<<endl;
    }

    void returnLastK(int k){
        

        if(head==NULL) return;
        returnLastKRecursive(head, k);
        return;
        int length = 0;
        for(auto itr = head;itr!=NULL;itr=itr->next){
            length++;
        }
        if(k>=length or k<0) {
            cout<<"invalid request";
            return;
        }
        cout<<length<<k;
        int diff = length - k;
        int counter = 1;
        for(auto i = head;i!=NULL;i = i->next){
            if(counter++ == diff)  {
                cout<<"kth element is "<<i->data<<endl;
                break;
            }
        }
    }

    int returnLastKRecursive(node* head, int k){
        if(head == NULL) return -1;
        int t = 1+returnLastKRecursive(head->next, k);
        
        if(k==t) cout<<head->data<<endl;
        return t;
    }
    void removeDuplicate(){

        int temp;
        cout<<"Removing duplicates...";
        try{
            for(auto *itr = head;itr!=NULL;itr=itr->next){
                int d = itr->data;
                node* prev = itr;
                
                for(auto *ptr = itr->next;ptr!=NULL;ptr = ptr->next){
                
                    if(ptr->data == d){
                        
                        prev->next = ptr->next;   
                    }    
                    else
                    {
                        prev = prev->next;//increement this pointer only if duplicate is not there
                    }                 
                }
                
            }
        }catch(const std::exception ex){
            cout<<"Exception occured"<<ex.what();
        }
    }

    void partition(int k){
        if(head == NULL) return;
        node *ptr = head;
        node *qtr = NULL;
        node *largeHead = NULL;
        while(ptr->next != NULL ){
            if(ptr->next->data >= k){
                node *temp=new node;
                temp->data = ptr->next->data;
               // temp->next =NULL;
                if(largeHead == NULL){
                    largeHead = temp;
                    qtr = temp;
                }
                else{
                    qtr->next = temp;
                    qtr = qtr->next;
                }
                    ptr->next = ptr->next->next;
            }
            else ptr = ptr->next;
            
        }
        ptr->next = largeHead;
    }

    void findSum(int n, int m){
        int sum = n+m;
        node *ptr = NULL;
        while(sum>0){
            int data = sum % 10;
            sum = sum/10;
            node *temp = new node;
            temp->data = data;
            temp->next = NULL;
            if(head == NULL){
                head = temp;
                ptr = head;
            }else
            {
                ptr->next = temp;
                ptr = ptr->next;
            }
        }
    }

    int getNumber()    {
        int output=0;
        int i=0;
        while(head!=NULL){
            output += pow(10,i++)*head->data;
            head = head->next;
        }
        cout<<"output"<<output;
        return output;
    }
};


class test{
    public:
    int t = 11;
    int* a=&t;
    string str="something";
};

int main(){
   
    int arr[7] = {1,5,2,4,8,2,3};
    int arr2[3] = {3,0,1};
    
    linkList ll;
    linkList l2;
    linkList output;
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i =0;i<n;i++)
        ll.add(arr[i]);  
    ll.partition(5)    ;
    ll.print();
    for(int i =0;i<3;i++)
        l2.add(arr2[i]);          
    ll.print();   
    l2.print();
    int p = ll.getNumber();
    int m = l2.getNumber();
    //ll.removeDuplicate()  ;
    //ll.returnLastK( 1);
    cout<<"after sum"<<endl;
    output.findSum(p,m);
    output.print();
    
    
}