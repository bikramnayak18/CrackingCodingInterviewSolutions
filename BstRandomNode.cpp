#include<iostream>

using namespace std;

class node{
    public:
    int item;
    node* left;
    node* right;
    int size;
    node(int item){
        this->item = item;
        this->size = 1;
        this->left = NULL;
        this->right = NULL;
    }
};

class tree{
    node* root = NULL;
    public:
    node* insert(node* root, int item){
        node* temp = new node(item) ;
        if(root == NULL)
            return temp;
        root->size++;
        if(item<=root->item)
            root->left = insert(root->left, item);
        else
            root->right = insert(root->right, item);

        return root;            
    }

    node* getIthNode(int i, node* root){
        int leftSize = root->left==NULL?0: root->left->size;
        if(i<leftSize)
            return getIthNode(i, root->left);
        else if(i == leftSize)
            return root;
        else
            return getIthNode(i - leftSize+1, root->right);
    }

    node* getRandom(node* root){
        if(root == NULL) return NULL;
        int i = rand()%root->size;
        return getIthNode(i, root);
    }


};

int main(){

}