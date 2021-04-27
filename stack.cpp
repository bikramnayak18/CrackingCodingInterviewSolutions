#include<iostream>
#include<vector>
using namespace std;
class MyStack{
   private:  class Node{
        public: int data;
        Node* next;
        public: Node(int item){
            this->data = item;
            this->next = NULL;
        }
    };

    private: Node* head=NULL;
    public: int pop(){
        if(head == NULL) return INT_MAX;
        int temp = head->data;
        head = head->next;
        return temp;
    }

    void push(int item){
        Node *node = new Node(item);
        node->next = head;
        head = node;
    }
     bool isEmpty(){
        return head == NULL;
    }

    int peek(){
        return head->data;
    }
};

class MinStack{
    private:class node{
        public: int item;
        int min;
        node* next;
    };

    node* head=NULL;

    int min = INT_MAX;

    public : void push(int item){
        node *temp = new node;
        temp->item = item;
        temp->next = NULL;
        if(min>item)
            min = item;
        temp->min = min;
        if(head==NULL){ 
            head = temp;
        }
        else{
            temp->next = head;
            head = temp;
        }
    }

    int pop(){
        int item = head->item;
        head = head->next;
        return item;
    }

    bool isEmpty(){
        return head==NULL;
    }
    int returnMin(){
        int min = head->min;
        return min;
    }
};

class StackPlates{
    private :const int threshold ;
    private:class node{
        public:int item=0;
        node* next=NULL;
        int k=1;
        node(int item){
            this->item = item;
        }
    };
    public:StackPlates(int th):threshold(th){
        
    }
    int stackPointer = -1;
    vector<node*> stacks;

    node* getInsertHead(){
        if(stackPointer==-1 || (stacks[stackPointer]!= NULL && stacks[stackPointer]->k>= this->threshold))
        {
                stackPointer++;
                return NULL;
        }
        return stacks[stackPointer];
    }

    node* getRemoveHead(){
                    
        if(stackPointer==-1){
            cout<<"No more elements can be removed";
            return NULL;
        }
        node *head =stacks[stackPointer];
        if(head->k==1 && stackPointer>-1){ 
            stacks.pop_back();
            stackPointer--;
        }
        return head;
    }
    public : void push(int item){
        node *temp = new node(item);
        node* head = getInsertHead();
        
        if(head == NULL){
            head = temp;
            stacks.push_back(head);
        }else{
            temp->k = head->k+1;
            temp->next = head;
            stacks[stackPointer] = temp;
            cout<<"pushing "<<stackPointer<<" : "<<item<<" : "<<temp->k<<endl;
        }
    }

    int pop(){
        node *head = getRemoveHead();
        if(head== NULL) return INT_MAX;
        int item = head->item;
        if(head->next != NULL)
            stacks[stackPointer] = head->next;
        cout<<"poping: "<<stackPointer<<" : "<<head->item<<" : "<<head->k<<endl;
        return item;
    }

    bool isEmpty(){
        return stackPointer==-1;
    }
};

class stack{
    private: class node{
        public : int item;
        node *next = NULL;
        node(int item){
            this->item = item;
        }
    };

    node *head = NULL;
    public:
    void push(int item){
        node *temp = new node(item);
        temp -> next = head;
        head = temp;
    }

    int pop(){
        if(head == NULL){
            cout<<"stack is empty";
            return INT_MAX;
        }
        int item = head->item;
        head = head->next;
        return item;
    }

    bool isEmpty(){
        return head == NULL;
    }
    
};

class QueueUsingStack{
    stack st1, st2;
    bool first = true;
    public:
    void push(int item){
        if(!first){
            while(!st2.isEmpty()){
                st1.push(st2.pop());
            }
            first = true;
        }
        st1.push(item);
    }

    int pop(){
        if(first){
            while(!st1.isEmpty()){
                st2.push(st1.pop());
            }
            first = false;
        }
        if(st2.isEmpty()) {
            cout<<"queue is empty";
            return INT_MAX;
        }
        return st2.pop();
    }

    bool isEmpty(){
        return st2.isEmpty() && st1.isEmpty();
    }
};

void stackOfPlates(){
        StackPlates stack(5) ;
    stack.push(7);
    stack.push(5);
    stack.push(41);
    stack.pop();
    stack.push(9);
    stack.push(0);
    stack.push(2);
    stack.push(122);
    stack.pop();
     stack.push(9);
    stack.push(0);
    stack.push(2);
    stack.pop();
     stack.push(9);
    stack.push(0);
    stack.pop();
    stack.push(2);
    cout<<"stack elements are "<<endl;
    while (!stack.isEmpty())
    {
        stack.pop();
    }
}

void queueUsingStack(){
    QueueUsingStack queue;
    queue.push(1);
    queue.push(12);
    queue.push(13);
    queue.push(14);
    queue.push(15);
    queue.push(7);
    queue.push(9);
    cout<<queue.pop()<<endl;
    cout<<queue.pop()<<endl;
    cout<<queue.pop()<<endl;
    queue.push(71);
    cout<<queue.pop()<<endl;
    queue.push(9);
    cout<<queue.pop()<<endl;
    queue.push(9);
    while(!queue.isEmpty()){
        cout<<queue.pop()<<endl;
    }
}

int main(){
    //stackOfPlates();
    queueUsingStack();   
}