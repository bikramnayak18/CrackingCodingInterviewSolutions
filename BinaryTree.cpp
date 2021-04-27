#include <iostream>
#include<unordered_map>
using namespace std;

class node{
        public:
        int item;
        node* left;
        node* right;
         node(int item){
            this->item = item;
            this->right = NULL;
            this->left = NULL;
        }
};

class BinaryTree{
    public: node* head = NULL;
    
    node* insert(node* root, int item, bool &found){
        if(root == NULL)
        {
            node *temp = new node(item);
            found = true;
            return temp;
        }
        if(root->item!=-1){
            root->left = insert(root->left, item, found);
            if(!found)
                root->right = insert(root->right, item, found);
        }
        return root;
    }

    void inOrder(node* root){
        if(root == NULL) return ;
        inOrder(root->left);
        cout<<root->item<<" ";
        inOrder(root->right);
    }

    void preOrder(node* root){
        if(root == NULL) return; 
        cout<<root->item<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
    public:
    void insert(int item[],int n){
        bool found = false;
        for(int i=0;i<n;i++){
            found = false;
            head = insert(head, item[i], found);
        }
    }

    void inOrder(){
        inOrder(head);
    }

    void preOrder(){
        preOrder(head);
    }

    int partialSum(node* root, int k, unordered_map<int , int> remainder, int runningSum){
        if(root == NULL) return 0;
        int output=0;
        runningSum += root->item;
        if(runningSum == k)
            output++;
        else{
            int rem = runningSum - k;
            if(remainder.find(rem) != remainder.end()){
                output += remainder[rem];
            }
        }
        if(remainder.find(runningSum)!= remainder.end())
            remainder[runningSum]++;
        else
            remainder[runningSum]=1;
        output += partialSum(root->left, k,remainder, runningSum) ;
        output += partialSum(root->right, k, remainder, runningSum);
        remainder[runningSum]--;
        return output;        
    }
};

int main(){
    BinaryTree bt;
    // int arr[] = {10,5,3,3,-1,-1,-2,-1,-1,1,-1,2,-1,-1,-3,-1,11,-1,-1};

    // bt.insert(arr,19);
    // bt.preOrder();
    bt.head = new node(10);
    bt.head->left = new node(5);
    bt.head->right = new node(-3);
    bt.head->right->right = new node(11);
    bt.head->left->left = new node(3);
    bt.head->left->right = new node(1);
    bt.head->left->right->right = new node(2);
    bt.head->left->left->left = new node(8);
    bt.head->left->left->right = new node(-2);
    bt.preOrder();
    unordered_map<int , int> remainder;
    cout<<"partial sum : "<<bt.partialSum(bt.head, 8, remainder, 0);
}