#include<iostream>
#include<unordered_map>
using namespace std;

class node{
    public:
    string item = "";
    int key=0;
    node* prev = NULL;
    node* next = NULL;
    
    node(string item, int key){
        this->item = item;
        this->key = key;
    }
};

class cache{
    node* head= NULL;
    node* tail = NULL;
    unordered_map<int, node*> dict;
    int maxSize = 5;

    void removeKey(int key){
        node* temp = dict[key];
        removeFromLinkedList(temp);
        dict.erase(key);
    }

    void removeFromLinkedList(node* current){
        if(current == NULL) return ;
        if(current->prev != NULL) current->prev->next = current->next;
        if(current->next != NULL) current->next->prev = current->prev;
        if(current == tail) tail = current->prev;
        if(current == head) head = current->next;
    }
    public:
    void insertAtFront(node* root){
        if(head == NULL) {
            head = root;
            tail = root;
        }
        root->next = head;
        head->prev = root;
        head = root;
    }

    void insert(int key, string value){
        removeKey(key);
        if(dict.size()>=maxSize && tail!= NULL){
            removeKey(tail->key);
        }
        node* newNode = new node(value, key);
        insertAtFront(newNode);
        dict[key] = newNode;
    }

    string getValue(int key){
        node* current = dict[key];
        if(current == NULL) return "";
        if(current != head)
        {
            removeFromLinkedList(current);
            insertAtFront(current);
        }
        return current->item;
    }

    void printAll(){
        node* temp = head;
        while(true){
            cout<<temp->key<<":"<<temp->item<<endl;
            if(temp == tail)
                return;
            temp = temp->next;
        }
    }
};

int main(){
    cache firstCache; 
    firstCache.insert(4,"fourth");
    firstCache.insert(3,"third");
    firstCache.insert(2,"second");
    firstCache.insert(1,"first");
    cout<<"Printing values ... ";firstCache.printAll();
    cout<<"key 3 value"<<firstCache.getValue(3)<<endl;
    cout<<"printing values ";firstCache.printAll();
    cout<<"key 4 value"<<firstCache.getValue(4)<<endl;
    firstCache.insert(5,"fifth");
    firstCache.insert(6,"sixth");
    cout<<"printing vlaues";firstCache.printAll();
    firstCache.insert(1,"one");
    cout<<"printing ...";
    firstCache.printAll();
}