#include<iostream>
#include<vector>
#include<list>
using namespace std;
class Graph{
    private: int V;
    vector<int> *adj;
    public: Graph(int v){
        this->V = v;
        adj = new vector<int>[v];
    }

    void addEdge(int u, int v){
        cout<<"ading edge"<<endl;
        adj[u].push_back(v);
    }
    void print(){
        for(int i=0;i<V;i++){
            cout<<"source "<<i<<" ";
            for(auto itr = adj[i].begin(); itr!= adj[i].end() ; itr++){
                cout<<"childs "<<*itr;
            }
        }
        cout<<endl;
    }



    
    void DFSUtil(int source, bool visited[]){
        cout<<"calling dfs uti";
        visited[source] = true;
        cout<<source<<endl;
        for(auto i = adj[source].begin();i!=adj[source].end();i++){
            if(!visited[*i]){
                visited[*i] = true;
                DFSUtil(*i, visited);
            }
        }
    }

    void DFS(int source){
        // cout<<source;
        bool visited[V] = {false};
       
        DFSUtil(source, visited);
    }
    void BFS(int source)
    {
        
        bool visited[this->V]= {false};
        visited[source] = true;
        list<int> queue;
        queue.push_back(source);
        while (!queue.empty())
        {
            int u = queue.front();
            cout<<u<<";";
            
            queue.pop_front();
            for(vector<int>::iterator i = adj[u].begin();i!=adj[u].end();i++){
                if(!visited[*i]){
                    visited[*i] = true;
                    queue.push_back(*i);
                }
            }
            
        }
        
    }

    void findPath(int u, int v){
        //BFS(u,v);
    }
};

class node{
    public : int key=0;
    int weight = 0;
    vector<node> child;
};

class Graph2{
    public : int vertices=0;
    node* nodes;
    Graph2(int vertices){
        this->vertices = vertices;
        this->nodes = new node[vertices];
        for(int i=0;i<vertices;i++){
            this->nodes[i].key = i;
            this->nodes[i].weight = INT_MAX;
        }
    }
    void printNodes(){
        cout<<"printing graph nodes";
        for(int i=0;i<vertices;i++){
            cout<<this->nodes[i].key<<" : "<<nodes[i].weight;
            for(auto itr = nodes[i].child.begin(); itr!=nodes[i].child.end();itr++){
                cout<<"childs "<<itr->key;
            }
            cout<<endl;
        }
        
    }
  

    void print(){
        for(int i=0;i<vertices;i++){
            cout<<nodes[i].key<<" weight : "<<nodes[i].weight<<endl;
        }
    }
    int findMin(bool visited[]){
        int min = INT_MAX;
        int minIndex=-1;
        for(int i=0;i<vertices;i++){
            if(!visited[i] && min>nodes[i].weight)
            {
                minIndex = i;
                min = nodes[i].weight;
            }
        }
        nodes[minIndex].weight = min;
        return minIndex;
    }

    void dijkstra(int start){
        bool visited[this->vertices] = {false};
        nodes[start].weight = 0;
        for(int j=0;j<vertices-1;j++){
            int index = findMin(visited);
            visited[index] = true;  
            node temp = nodes[index];
            vector<node> childs = temp.child;
            for(vector<node>::iterator i = childs.begin() ; i!=childs.end(); i++){
                if(!visited[i->key] && temp.weight + i->weight < nodes[i->key].weight)
                    nodes[i->key].weight = temp.weight + i->weight;
            }
        }
    }

    void addEdge(int u, int v, int distance){
        node temp ;
        temp.key = v;
        temp.weight = distance;
        this->nodes[u].child.push_back(temp);
        temp.key = u;
        this->nodes[v].child.push_back(temp);
    }

    void BFS(int source){
        bool visited[vertices] = {false};
        visited[source] = true;
        list<node> queue;
        queue.push_back(nodes[source]);
        while(!queue.empty()){
            node pop = queue.front();
            queue.pop_front();
            cout<<pop.key<<" ";
            vector<node> childs = pop.child;
            for(vector<node>:: iterator i = childs.begin(); i != childs.end() ; i++){
               // cout<<" child: "<<i->key<<" ";
                if(!visited[i->key])
                {
                    visited[i->key] = true;
                    queue.push_back(nodes[i->key]);
                }
            }
        }
    }

    void DFS(node* root, bool visited[]){
       cout<<root->key<<endl;
       visited[root->key] = true;
        for(vector<node>::iterator i = root->child.begin();i!= root->child.end();i++)
        {   
            //node * temp2 = i;//error
            //node * temp2 = *i;//error
            node *temp3 = &*i;
            node* temp;
            temp->key = i->key;
            if(!visited[i->key]){
                visited[i->key] = true;
                DFS(&nodes[i->key], visited);
                DFS(temp, visited);
                DFS(&*i, visited);
                //DFS(i, visited);//error
                //DFS(i, visited);//erroro
                //DFS(*i, visited);//erroro
                DFS(temp3, visited);
            }
        }
    }

    void runDfs(int source){
        node root;
        root.key = source;
        bool visited[this->vertices] = {false};
        DFS(&root, visited);
        node* root2 = new node;
        root2->key = source;
        DFS(root2, visited);
    }
};

class BST{
    public: class node{
        public:int key=0;
        node *left = NULL;
        node *right = NULL;
        public: node(int key){
            this->key = key;
        }
    };
    private: node* root = NULL;
    public: node* temp;

    void pinters(){
        node * ptr = new node(1);
        //node* qtr = *ptr;//gives error
        node* qtr = ptr;
        node* str ;
        str = ptr;
        //str = *ptr;//gives error
        //str = *ptr;
        //node t = qtr;//gives error
        node t = *qtr;
        t = *ptr;
        node s(1);
        //s = ptr;//gives error
    }
    void inorder(node *ptr){
        if(ptr==NULL) return;
        inorder(ptr->left);
        cout<<ptr->key<<endl;
        inorder(ptr->right);
    }

    void preOrder(node *ptr){
        if(ptr==NULL) return;
        cout<<ptr->key<<endl;
        preOrder(ptr->left);
        preOrder(ptr->right);
    }

    public:
    void inOrderTraversal(node* temp){
        node *root = temp ==NULL?this->root:temp;
        preOrder(root);
    }
    void maxDepth(){
        cout<<"max depth of tree is :"<<maxDepthWithHeader(root)<<endl;
    }

    int maxDepthWithHeader(node *ptr){
        if(ptr == NULL) return -1;
        int left = maxDepthWithHeader(ptr->left);
        int right = maxDepthWithHeader(ptr->right);
        if(left>right)
            return 1 +  left;
        return 1 + right;   
    }

   
     node* commonA(node* root, int n1, int n2, bool &v1, bool &v2){
        if(!root)
            return NULL;
        if(root->key == n1 ){
            v1 = true;
            return root;
        }
        if(root->key == n2){
            v2 = true;
            return root;
        }
        node* left = commonA(root->left, n1, n2, v1, v2);
        node* right = commonA(root->right, n1, n2, v1, v2);

        if(left && right) return root;

        return left==NULL?right:left;
    }

    //common ansestor for binary tree problem
    void commonAncestor(int n1, int n2){
        bool v1 = false;
        bool v2 = false;
        node * root = commonA(root,n1, n2, v1, v2);
        if(root!= NULL && v1 && v2) cout<<root->key;
        else cout<<"common ancestor doesn't exist";
    }

    void insertRoots(int arr[], int start, int end, int visited[]){
        if(end-start<=2) return;
        int n = start + (end- start)/2;

        if(!visited[n]){
            visited[n] = true;
            insert(arr[n]);
            insertRoots(arr,start, n,visited);
            insertRoots(arr,n,end,visited);
        }
    }

    node* insertRoots2(int arr[], int start, int end){
        if(end<start) return NULL;
        int mid = (start+end)/2;
        node* temp  = new node(arr[mid]);
        temp->left = insertRoots2(arr, start, mid-1);
        temp->right = insertRoots2(arr, mid+1, end);
        return temp;
    }

    node* insertIntoTree2(int arr[], int n){
        node* temp = insertRoots2(arr, 0,n-1);
        cout<<"max depth : "<<maxDepthWithHeader(temp)<<endl;
        inOrderTraversal(temp);
        return temp;
    }

    void insertIntoTree(int arr[], int n){
        int visited[n] = {false};
        insertRoots(arr, 0,n, visited);
        for(int i =0;i<n;i++)
        {
            if(!visited[i]){
                insert(arr[i]);
            }
        }
    }

    list<list<node>> createLevelList(node * root){
        list<list<node>> output;
        list<node> current;
        if(root != NULL)
            current.push_back(*root);
        while(current.size()>0){
            output.push_back(current);
            list<node> temp = current;
            current.clear();
            for(auto i=temp.begin();i!=temp.end();i++){
                if(i->left!=NULL)
                    current.push_back(*i->left);
                if(i->right!=NULL)
                    current.push_back(*i->right);
            }
        }
        return output;
    }

    int checkTreeHeight(node *head){
        if(head ==NULL) return 0;
        int leftH = checkTreeHeight(head->left);
        if(leftH==-1) return -1;
        int rightH = checkTreeHeight(head->right);
        if(rightH ==-1) return -1;
        if(abs(leftH-rightH)>1) return -1;
        int height = leftH>rightH? leftH+1:rightH+1;
        return height;
    }

    bool isTreeBalanced(){
        return checkTreeHeight(root)!=-1;
    }

    void levelNodes(){
        list<list<node>> output = createLevelList(root);
        for(auto i=output.begin();i!=output.end();i++){
            for(auto j= i->begin();j!=i->end();j++){
                cout<<j->key<<" ";
            }
            cout<<endl;
        }
    }

    void insert(int key){
        node* temp = new node(key);
        if(root == NULL){
            root = temp;
            return;
        }
        node *ptr = root;
        while(ptr != NULL){ 
            if( key <ptr->key)
            {
                if(ptr->left != NULL ) 
                    ptr = ptr->left;
                else {
                    ptr->left = temp;
                    break;
                }
            }
            else if ( key>ptr->key)
            {
                if(ptr->right != NULL)
                    ptr = ptr->right;
                else{
                    ptr->right = temp;
                    break;
                }
            }
        }
    }
};

class dnode{
    public:
        int key;
        int dcount ;
        vector<dnode> childs;
        dnode(int key){
            this->key = key;
        }
        dnode(){
            key = 0;
            dcount = 0;
        }
};


class Topology{
    private: int vertices=0;
    dnode* nodes;
    public: Topology(int vertices){
        this->vertices = vertices;
        this->nodes = new dnode[this->vertices];
        for(int i =0;i<vertices;i++){
            this->nodes[i].key = i;
        }
    }

    void addEdge(int u, int v){
        dnode temp(v);
        this->nodes[u].childs.push_back(temp);
        this->nodes[v].dcount++;
    }

    void topologySort(){
        //find independent node first.. if there is none then graph has cycle and build order is not possible
        cout<<"calling topo"<<endl;
        list<dnode> indNode;
        bool visited[vertices] = {false};
        for(int i =0;i<vertices;i++){
            cout<<nodes[i].dcount<<endl;
            if(nodes[i].dcount==0)
                indNode.push_back(nodes[i]);
        }
        while(!indNode.empty()){
            dnode temp = indNode.front();
            dnode* i = &temp;
            indNode.pop_front();
            if(visited[i->key]) continue;
            cout<<"build order : "<<i->key<<" "<<endl;
            visited[i->key] = true;
            vector<dnode> childs = i->childs;
            //cout<<"number of childs "<<childs.size();
            for(auto j = childs.begin();j!=childs.end();j++){
                //cout<<"childs"<<j->key<<" ";
                this->nodes[j->key].dcount--;
                if(this->nodes[j->key].dcount==0)
                    indNode.push_back(nodes[j->key]);
            }
        }

        for(int i=0;i<vertices;i++){
            if(!visited[i]) {
                cout<<"cycle detected";
                break;
            }
        }
    }
};

int main(){

    Topology g(6);
    g.addEdge(1, 2); 
    g.addEdge(1, 0); 
    g.addEdge(4, 0); 
    g.addEdge(4, 1); 
    g.addEdge(2, 3); 
    g.addEdge(3, 5); 
    g.topologySort();
    // BST bst;
    // int n =17;
    // int arr[n] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    // //bst.temp = bst.insertIntoTree2(arr,n);
    // //bst.insertIntoTree(arr,n);
    // bst.insert(4);
    // bst.insert(5);
    // bst.insert(6);
    // bst.insert(2);
    // bst.insert(1);
    // bst.insert(0);
    // cout<<"is tree balanced : "<<bst.isTreeBalanced();
    // bst.insert(3);
    // cout<<"is tree balanced : "<<bst.isTreeBalanced();
    // bst.maxDepth();
    // //bst.levelNodes();
    // bst.inOrderTraversal(NULL);   
    // bst.insert(0);
    // bst.insert(1);
    // bst.insert(2);
    // bst.insert(3);
    // bst.insert(4);
    // bst.insert(5);
    // bst.insert(6);
    // Graph g(6);
    // g.addEdge(0,1);
    // g.addEdge(0,2);
    // g.addEdge(1,3);
    // g.addEdge(3,4);
    // g.addEdge(2,4);
    // g.addEdge(5,4);
    // g.DFS(0);
   /* Graph2 g(9);
    g.addEdge(0, 1,4);
    g.addEdge(0, 7,8);
    g.addEdge(1, 0,4);
    g.addEdge(1, 2,8);
    g.addEdge(1, 7,11);
    g.addEdge(2, 1,8);
    g.addEdge(2, 3,7);
    g.addEdge(2, 5,4);
    g.addEdge(2, 8,2);
    g.addEdge(3, 2,7);
    g.addEdge(3, 4,9);
    g.addEdge(3, 5,14);
    g.addEdge(4, 3,9);
    g.addEdge(4, 5,10);
    g.addEdge(5, 2,4);
    g.addEdge(5, 3,14);
    g.addEdge(5, 4,10);
    g.addEdge(5, 6,2);
    g.addEdge(6, 5,2);
    g.addEdge(6, 7,1);
    g.addEdge(6, 8,6);
    g.addEdge(7, 0,8);
    g.addEdge(7, 1,11);
    g.addEdge(7, 6,1);
    g.addEdge(7, 8,7);
    g.addEdge(8, 2,2);
    g.addEdge(8, 6,6);
    g.addEdge(8, 7,7);
    //g.printNodes();
    g.print();
    g.dijkstra(0);
    g.print();*/
}