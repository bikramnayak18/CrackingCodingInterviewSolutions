#include<iostream>
#include<list>
#include<vector>
using namespace std;

class node{
    public: 
    node* left = NULL;
    node* right = NULL;
    int item = 0;
};

class BST{
    node* root = NULL;
    public:
    node* insert(node* root, int item){
        if(root == NULL){
            node* temp = new node;
            temp->item = item;
            return temp;
        }

        if(item<=root->item)
            root->left = insert(root->left, item);
        else   
            root->right = insert(root->right, item);
        return root;            
    }

    void traversal(node* root){
        if(root == NULL)  return;
        traversal(root->left);
        cout<<root->item;
        traversal(root->right);
    }
    
    string preorder(node *root, string prefix){
        if(root == NULL)
        {
            return prefix+"X";
        }
        prefix += to_string(root->item);
        prefix = preorder(root->left, prefix);
        prefix = preorder(root->right, prefix);
        return prefix;
    }

    void weeveArr(list<int> first, list<int> second, vector<list<int>> &results, list<int> prefix){
        if(first.size()==0 || second.size()==0){
            list<int> result;
            result.insert(result.end(), prefix.begin(), prefix.end());
            result.insert(result.end(), first.begin(), first.end());
            result.insert(result.end(), second.begin(), second.end());
            results.push_back(result);
            return ;
        }
        int position=0;
        int firstElement = first.front();
        first.pop_front();
        prefix.push_back(firstElement);
        weeveArr(first, second, results, prefix);
        first.push_front(firstElement);
        prefix.pop_back();

        int secondElement = second.front();
        second.pop_front();
        prefix.push_back(secondElement);
        weeveArr(first,second,results,prefix);
        second.push_front(secondElement);
        prefix.pop_back();
    }

    vector<list<int>> findArrays(node* root){
        vector<list<int>> results;
        if(root == NULL)
        {
            list<int> empty;
            results.push_back(empty);
            return results;
        }
        list<int> prefix;
        prefix.push_back(root->item);
        vector<list<int>> left = findArrays(root->left);
        vector<list<int>> right = findArrays(root->right);
        for(auto itr=left.begin();itr!=left.end();itr++){
            for(auto ptr=right.begin();ptr!=right.end();ptr++){
                weeveArr(*itr,*ptr,results,prefix);
            }
        }
        return results;
    }

};

bool matchTree(node* first, node* second){
    if(first == NULL || second == NULL){
        if(second != first) return false;
        else return true;
    }
    if(first->item != second->item) return false;
    bool result = matchTree(first->left, second->left);
    if(result)
        result = matchTree(first->right, second->right);
    return result;
}

bool isSubtree(node* t1, node* t2){
    if(t1 == NULL)  return false;
    bool result = false;
    if(t1->item == t2->item)
        result = matchTree(t1, t2);
    if(!result)
        result = isSubtree(t1->left,t2);
    if(!result)
        result = isSubtree(t1->right, t2);
    
    return result;
}

int main(){
        int arr[7] = {5,3,2,4,7,6,8};
        BST tree;
        node* root = NULL;
        for(int i=0;i<7;i++){
            root = tree.insert(root, arr[i]);
        }

        int arr2[3] = {6,7,8};
        BST tree2;
        node* root2 = NULL;
        for(int i=0;i<3;i++)
            root2 = tree2.insert(root2, arr2[i]);
        // string output = tree.preorder(root,"");
        // string output2 = tree2.preorder(root2, "");
        // cout<<output<<endl;
        // cout<<output2<<endl;
        bool isTree = isSubtree(root,root2);
        cout<<"sub tree "<< isTree<<endl;
        // tree.traversal(root);
        // vector<list<int>> results = tree.findArrays(root);
        // for(auto result:results){
        //     for(auto element:result){
        //         cout<<element<<" ";
        //     }
        //     cout<<endl;
        // }
}


