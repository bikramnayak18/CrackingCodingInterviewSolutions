#include<iostream>
#include<algorithm>
#include<list>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<fstream>
#include<queue>
using namespace std;

int getIBit(int n, int column){
    return (n>>column) & 1;
}

int findMissing(list<int> input, int column){
    if(column>= sizeof(int)*8) return 0;
    list<int> zero;
    list<int> one;
    for(auto item:input){
        if(getIBit(item, column) == 0)
            zero.push_back(item);
        else
            one.push_back(item);
    }
    if(zero.size()<= one.size())
    {
        int v = findMissing(zero, column+1);
        return (v<<1)|0;
    }else{
        int v = findMissing(one, column+1);
        return (v<<1)|1;
    }
}

bool isChar(char c){
    int x = (int) c;
    if(x>=97 && x<= 122)
        return true;
    else if(x>=65 && x<=90)
        return true;
    else return false;
}

int calculatMaxSub(int arr[], int n){
    unordered_map<int, int> map ;
    int maxSum = 0;
    map[0]=-1;
    for(int i=0;i<n;i++){
        if(map.find(arr[i]) == map.end())
        {
            map[arr[i]]= i;
        }else{
            int a = map[arr[i]];
            maxSum = std::max(maxSum, i - a);
        }
    }
    return maxSum;
}

//given an array of letter and number, find max size of sub array containing equal number of letters and numbers
int findLongestSubarray(string input, int n){
    cout<<input<<":"<<n<<endl;
    int maxCount = 0;
    int deltas[n];
    int currentNumber = 0;
    int currentChar = 0;
    for(int i=0;i<n;i++){
        if(isChar(input[i]))
            currentChar++;
        else
            currentNumber++;
        deltas[i] = currentChar - currentNumber;
        cout<<deltas[i];
    }
    cout<<endl;
    return calculatMaxSub(deltas, n);
}

class Node{
    public:
        string name="";
        int frequency=0;
        bool isVisited = false;
        vector<Node*> child;
};

class Graph{
    public:
    int v;
    unordered_map<string, Node*> mapper;
    Graph(int v){
        this->v = v;
    }

    void createGraph(Node nameFrequency[]){
        for(int i=0;i<this->v;i++){
            Node* temp = new Node;
            temp->name = nameFrequency[i].name;
            temp->frequency = nameFrequency[i].frequency;
            mapper[temp->name] = temp;
        }
    }

    void addEdge(string u, string v){
        Node* node1 = mapper[u];
        Node* node2 = mapper[v];
        node1->child.push_back(node2);
        node2->child.push_back(node1);
    }

    int calculateGroupFrequency(Node* root){
        int sum = root->frequency;
        root->isVisited = true;
        for(int i=0;i<root->child.size();i++){
            if(!root->child[i]->isVisited)
                sum += calculateGroupFrequency(root->child[i]);

        }
        return sum;
    }

    vector<pair<string, int>> findTrueFrequency(){
        vector< pair<string, int>> output;
        for(auto itr=mapper.begin();itr!=mapper.end();itr++){
            Node* temp = itr->second;
            if(!temp->isVisited){
                string name = temp->name;
                int sum = calculateGroupFrequency(temp);
                output.push_back( make_pair(name, sum));
            }
        }
        return output;
    }
};


int findMax(int arr[], int memo[], int n, int i){
    if(i>=n)
        return 0;
    
    if(memo[i]!=-1)
        return memo[i];
    int sum1 = findMax(arr, memo, n, i+1);
    int sum2 = arr[i] + findMax(arr, memo, n , i+2);
    int sum = std::max(sum1, sum2);
    memo[i] = sum;
    return sum;
}

int findMaxIterative(int arr[], int n){
    int next=0, nextNext=0;
    int currBest =0;
    for(int i=n-1;i>=0;i--){
        int a = arr[i] + nextNext;
        int b = next;
        currBest = std::max(a,b);
        nextNext = next;
        next = currBest;
    }
    return currBest;
}

void findMaxSequence(){
    int arr[]={30,15,60,75,45,15,15,45};
    int n = sizeof(arr)/sizeof(arr[0]);
    int memo[n];
    for(int i=0;i<n;i++)
        memo[i] = -1;
    cout<<"max minutes iterative "<<findMaxIterative(arr, n)<<endl;

    cout<<"max minutes is "<<findMax(arr, memo, n, 0);
}

class Person{
    public:
        int height;
        int weight;
        Person(int height, int weight){
            this->height = height;
            this->weight = weight;
        }

        bool operator<(const Person p) const
        {
            return this->height<p.height;
        }
        bool isShorterHeight(Person p){
            return this->height < p.height;
        }

        bool isLighterWeight(Person p){
            return this->weight < p.weight;
        }
};

int maxHeight(Person persons[]){
    int max = -1;

    return max;
}

Person** getList(){
    Person** persons = new Person*[10];
    persons[0] = new Person(10,5);
    return persons;
}

class Circus{
    int n;
    Person** persons;
    public:
    Circus(int n){
        this->n = n;
        persons = new Person*[n];
    }

    void addPeople(){
        persons[0]  = new Person(17,45);
        persons[1]  = new Person(10,90);
        persons[2]  = new Person(9,70);
        persons[3]  = new Person(8,72);
        persons[4]  = new Person(8,50);        
        persons[5]  = new Person(6,88);        
        persons[6]  = new Person(5,70);
        persons[7]  = new Person(4,50);       
        persons[8]  = new Person(2,10);
        persons[9]  = new Person(1,45);
    }

    int findMax(){        
        return findMax(persons, n);
       // std::sort(persons, persons+10);
        // vector<Person*> sequence;
        // sequence = buildSequence(persons, sequence,10,0);
        // return sequence.size();
    }

    bool canAppend(vector<Person*> sequence, Person* p){
        if(sequence.size()==0)
            return true;
        Person* temp = sequence.back();
        return p->weight < temp->weight;
    }

    int findMax(Person** arr, int n){
        vector<Person*> bestHeight[n];
        vector<Person*> max;
        vector<Person*> biggest;
        int totalMax=0;
        int maxSize=0;
        for(int i=0;i<n;i++){
            int j=0;
            for(auto &p:bestHeight){
                if(i==j)
                    break;
                int psize = p.size();                    
                if(canAppend(p, arr[i]) && maxSize< psize){
                    maxSize = p.size();
                    max = p;
                }
                j++;
            }
            if(maxSize>0)
                bestHeight[i] = max;
            bestHeight[i].push_back(arr[i]);
            maxSize = -1;
            if(totalMax<bestHeight[i].size()){
                totalMax = bestHeight[i].size();
                biggest = bestHeight[i];
            }
        }

        for(auto itr=biggest.begin();itr!=biggest.end();itr++){
            cout<<(*itr)->height<<":"<<(*itr)->weight<<endl;
        }
        return totalMax;
    }

    vector<Person*> buildSequence(Person **persons, vector<Person*> sequence, int n, int index){
        if(index>=n)
            return sequence;
        vector<Person*> bestWith;
        vector<Person*> bestWithout;
        if(canAppend(sequence, persons[index])){
            vector<Person*> cloned = sequence;
            cloned.push_back(persons[index]);
            bestWith = buildSequence(persons, cloned, n, index+1);
        }
        bestWithout = buildSequence(persons, sequence, n, index+1);

        if(bestWith.size()==0 ||(bestWithout.size()>bestWith.size()))
            return bestWithout;
        else
            return bestWith;    
    }
};

//find kth element whose factor is either 3,5,7
int findKth(int k){
    list<int> three;
    list<int> five;
    list<int> seven;
    three.push_back(1);
    int val=0;
    for (size_t i = 0; i < k; i++)
    {
        int a = three.size()>0?three.front():INT_MAX;
        int b = five.size()>0?five.front():INT_MAX;
        int c = seven.size()>0?seven.front():INT_MAX;
        val = std::min(a,std::min(b,c));
        if(val == a){
            three.pop_front();
            three.push_back(val*3);
            five.push_back(val*5);
            seven.push_back(val*7);
        }else if(val == b){
            five.pop_front();
            five.push_back(val*5);
            seven.push_back(val*7);
        }else
        {
            seven.pop_front();
            seven.push_back(val*7);
        }
    }
    return val;
}

bool validate(int candidate, int arr[], int n){
    bool valid;
    int count =0;
    for(int i=0;i<n;i++){
        if(arr[i] == candidate)
            count++;
    }
    return count > n/2;
}

int getCandidate(int arr[], int n);

int majorityElement(int arr[], int n){
    if(n==0) return -1;
    int candidate = getCandidate(arr, n);
    bool valid = validate(candidate, arr, n);
    return valid?candidate:-1;
}

int getCandidate(int arr[], int n){
    int majority=arr[0];
    int count=0;
    for(int i=0;i<n;i++){
        if(count==0)
            majority = arr[i];
        if(majority == arr[i])
            count++;
        else 
            count --;
    }
    return majority;
}

int findBest(int location1, int location2, int best){
    if(location1==-1 || location2==-1)
        return INT_MAX;
    int distance  = abs(location1-location2);
    return std::min(distance-1, best);
}

int findMinDistanceBetweenWord(string word1, string word2){
    if(word1 == word2)
        return 0;
    int best = INT_MAX;
    ifstream fileData;
    fileData.open("./inputWords.txt");
    string word;
    int a=-1;
    int b=-1;
    int index = 1;
    while(!fileData.eof()){
        fileData>>word;
        if(word == word1)
        {
            a = index;
            best = findBest(a,b,best);
        }
        else if(word == word2)
        {
            b = index;
            best = findBest(a,b,best);
        }
        index++;
    }
    fileData.close();
    return a==-1 || b ==-1?-1:best;
}

class WordLocation{
    unordered_map<string, vector<int>> wordLocation;
     int findBest(int location1, int location2, int best){
        if(location1==-1 || location2==-1)
            return INT_MAX;
        int distance  = abs(location1-location2);
        return std::min(distance-1, best);
    }
    public:
    void createMap(){
        ifstream file;
        file.open("inputWords.txt");
        string word;
        int index = 1;
        while(!file.eof()){
            file>>word;
            wordLocation[word].push_back(index++);
        }
    }

    int findMinDistance(string word1, string word2){
        vector<int> a = wordLocation[word1];
        vector<int> b = wordLocation[word2];
        if(a.size()==0 || b.size()==0)
            return -1;
        int best = INT_MAX;
        auto itr = a.begin();
        auto ptr = b.begin();
        while(itr!= a.end() && ptr!= b.end()){
            best = findBest(*itr, *ptr, best);
            if(*itr < *ptr)
                itr++;
            else 
                ptr++;
        }

        return best;
    }

   
};

class Parse{
    public:
    int invalid = 0;
    string parsed = "";
    Parse(int invalid, string parsed){
        this->invalid = invalid;
        this->parsed = parsed;
    }
};

Parse* reSpace(string input, unordered_set<string> dict, int start, Parse* memo[]){
        if(start>=input.length())
        {
            Parse *p = new Parse(0,"");
            return p;
        }
        if(memo[start] != NULL)
            return memo[start];
        int bestInvalid = INT_MAX;
        string bestPartial = "";
        string partial = "";
        
        for(int i = start ;i<input.length();i++){
            partial += input[i];            
            int invalid = dict.find(partial)!=dict.end()? 0 : partial.length();
            if(invalid < bestInvalid){
                Parse* partialResult = reSpace(input, dict, i+1, memo);
                if(invalid + partialResult->invalid < bestInvalid )
                {
                    bestInvalid = invalid + partialResult->invalid ;
                    bestPartial = partial +" "+ partialResult->parsed;
                    if(bestInvalid ==0)
                        break;
                }
            }
        }
        Parse* output = new Parse(bestInvalid, bestPartial);
        //cout<<output.parsed<<endl;
        output->invalid = bestInvalid;
        output->parsed = bestPartial;
        return output;
    }

    bool canBuildWords(string word, unordered_set<string> dict, bool isOriginal){
        if(dict.find(word)!=dict.end() && !isOriginal)
            return true;
        string left = "", right = "";
        for(int i = 1; i<word.length();i++){
            left = word.substr(0, i);
            right = word.substr(i, word.length()-i);
            if(dict.find(left) != dict.end() && canBuildWords(right, dict, false))
            {
                return true;
            }
        }
        return false;
    }

    bool compare(string a, string b){
        return a.length()>b.length();
    }

    string longestWord(vector<string> words){
        std::sort(words.begin(), words.end(), compare);
        unordered_set<string> dict;
        for(auto word:words){
            cout<<word<<endl;
            dict.insert(word);
        }
        for(auto word:words){
            if(canBuildWords(word, dict, true)){
                return word;
            }
        }
        return "";
    }

//two consecutive cells cannot be choosen and we have to find the max value possible
int findOptimalHour(int arr[],int memo[], int index, int n){
    if(index>=n)
        return 0;
    if(memo[index]!=-1)
        return memo[index];
    int max = 0;
    int maxWith = arr[index] + findOptimalHour(arr,memo, index+2,n) ;
    int maxWithout = findOptimalHour(arr,memo, index+1, n);
    max = std::max(maxWith, maxWithout);
    memo[index] = max;
    return max;
}

int findOptimalHour(int arr[], int n){
    for(int i=n-2;i>=0;i--){
        if(i<n-2)
            arr[i] = std::max(arr[i]+arr[i+2], arr[i+1]);
        else
            arr[i] = std::max(arr[i], arr[i+1]);
    }
    return arr[0];
}

const int alphabetSize = 26;

// class Trie{
//     public:
//     class Node{
//         public:
//         Node* child[alphabetSize];
//         bool isEnd = false;
//     };
//     Node* root = NULL;
//     unordered_map<string , vector<int>> dict;
//     Node* getNode(){
//         Node* node = new Node();
//         node->isEnd = false;
//         for(int i=0;i<alphabetSize ;i++){
//             node->child[i] = NULL;
//         }
//         return node;
//     }
    
//     void insert(string word){
//         if(!root ){
//             this->root = getNode();
//         }
//         Node* crawl = root;
//         for(int i=0;i<word.length();i++){
//             int index = word[i] - 'a';
//             if(!crawl->child[index] )
//                 crawl->child[index] = getNode();
//             crawl = crawl->child[index];    
//         }
//         crawl->isEnd = true;
//     }

//     bool checkPrefix(string word){
//         Node* crawl = root;
//         for(int i=0;i<word.length();i++){
//             int index = word[i] - 'a';
//             crawl = crawl->child[index];
//             if(!crawl)
//                 return false;
            
//         }
//         return true;
//     }

//     bool isComplete(string word)
//     {
//         Node* crawl = root;
//         for(int i=0;i<word.length();i++){
//             int index = word[i] - 'a';
//             crawl = crawl->child[index];
//             if(!crawl)
//                 return false;
//         }

//         return crawl!=NULL && crawl->isEnd;
//     }
//     void addCount(string word, int index, Node* root, string partial)
//     {
//         if(index>=word.length())
//             return;
//         int a = word[index] - 'a';
//         Node* newRoot = root->child[a];
//         if(newRoot){
//             partial += word[index];
//             if(newRoot->isEnd)
//                 dict[partial].push_back(index +1 - partial.length());
//             addCount(word, index+1, newRoot, partial);
//         }
//         else{
//             return;
//         }
//     }

//     void addCountIter(string word, int index, Node *root){
//         string partial = "";
       
//         for(int i=index;i<word.length();i++){
//             int a = word[i] - 'a';
//             root = root->child[a];
//             if(root){
//                 partial += word[i];
//                 if(root->isEnd)
//                     dict[partial].push_back(index);
//             }else
//                 return;
//         }
//         return;
//     }

//     void search(string word){
//         for(int i=0;i<word.length();i++){
//             //addCount(word, i, root, "");
//             addCountIter(word, i, root);
//         }
//         for(auto itr = dict.begin();itr!=dict.end();itr++)
//         {
//             vector<int> positions = itr->second;
//             string word = itr->first;
//             cout<<word<<" ";
//             for(auto ptr=positions.begin();ptr!=positions.end();ptr++)
//                 cout<<*ptr<<" ";
//             cout<<endl;
//         }            
//     }

// };

int findMinSub(int large[], int small[], int m, int n){
    list<int> mapper[n];
    for(int i=0;i<n;i++){
        int a = small[i];
        list<int> position;
        for(int j=0;j<m;j++){
            if(large[j] == small[i])
                position.push_back(j);
        }
        mapper[i]=position;        
    }
    int minArray = INT_MAX;
   while(true){
        int minIndex = 0;
        int min = INT_MAX, max = -INT_MAX;
        for(int j=0;j<n;j++){
            if(mapper[j].size()<=0)
                return minArray;
            int head = mapper[j].front();
            if(min>head)
            {
                min = head;
                minIndex = j;
            }
            if(max<head)
            {
                max = head;
            }
        }
        mapper[minIndex].pop_front();
        minArray = std::min(minArray, max - min+1);
    }
    return minArray;
}

int findMinSub2(int large[], int small[], int l, int s){
    unordered_map<int, list<int>> mapper;
    
    for(int i=0;i<s;i++){
        mapper[small[i]];
    }

    for(int i=0;i<l;i++){
        if( mapper.find(large[i]) !=mapper.end())
        {
            mapper[large[i]].push_back(i);
        }
    }
    int finalMin = INT_MAX;
    while(true){
        int minIndex;
        int minValue = INT_MAX;
        int maxValue = -INT_MAX;
        for(auto itr = mapper.begin();itr!=mapper.end();itr++){
            if(itr->second.size()<=0)
                return finalMin;
            list<int> position = itr->second;
        
            if(minValue>position.front()){
                minValue = position.front();
                minIndex = itr->first;
            }
            if(maxValue<position.front()){
                maxValue = position.front();
            }
        }
        mapper[minIndex].pop_front();
        finalMin = std::min(finalMin, maxValue - minValue+1);
    }
    return finalMin;
}

class MedianGenerator{
    priority_queue<int> max;
    priority_queue<int, vector<int>, greater<int>> min;
    int median= INT_MAX;

    void insert(int n){
        
        if(n<=median)
            max.push(n);
        else 
            min.push(n);
        //ensure always max size is equal or greater by 1 from min
        if(max.size()-1>min.size())
        {
            int a = max.top();
            max.pop();
            min.push(a);
        }else if(min.size()>max.size()){
            int a = min.top();
            min.pop();
            max.push(a);
        }
    }

    public:
    
    int generateMedian(int n){
        insert(n);
        if(max.size() == min.size())            
            return median = max.top() + min.top(), median/2;
        if(max.size()-1 == min.size())
            return median = max.top(), median;
        return INT_MAX;
    }
};


class element{
    public:
        int position;
        int value;
    element(int position, int value){
        this->position = position;
        this->value = value;
    }
};


class myComparator{
    public:
    bool operator()(element a, element b){
        return a.position>b.position;
    }
};

int findMinSubUsingHeap(int large[], int small[], int l, int s){
    unordered_map<int, list<element>> mapper;
    
    for(int i=0;i<s;i++){
        mapper[small[i]];
    }

    for(int i=0;i<l;i++){
        if( mapper.find(large[i]) !=mapper.end())
        {
            int position = i;
            int value = large[i];
            element el(position, value);
            mapper[large[i]].push_back(el);
        }
    }
    int finalMin = INT_MAX;
    priority_queue<element, vector<element>, myComparator> queue;
    int max = -INT_MAX;
    for(auto itr=mapper.begin();itr!=mapper.end();itr++){
        int value = itr->first;
        if(itr->second.size()<=0)
            return -1;
        queue.push(itr->second.front());
        int position = itr->second.front().position;
        if(max<position)
            max = position;
    }

    while(true){
        element minElement = queue.top();
        queue.pop();
        finalMin = std::min(finalMin, max - minElement.position + 1);
        mapper[minElement.value].pop_front();
        if(mapper[minElement.value].size()<=0)
            return finalMin;
        element newElement = mapper[minElement.value].front();
        queue.push(newElement);
        if(max<newElement.position)
            max = newElement.position;
    }

    return finalMin;
}

class Point{
    public:
    int rowStart, rowEnd, colStart, colEnd, best;
    Point(int rowStart, int rowEnd, int colStart, int colEnd, int best){
        this ->rowEnd = rowEnd;
        this ->rowStart = rowStart;
        this->colStart = colStart;
        this->colEnd = colEnd;
        this->best = best;
    }
};

class Matrix{
    int col;
    int row;
    vector<vector<int>> matrix;
    public:
    Matrix(int row, int col){
        this->col = col;
        this->row = row;
    }

    void createMatrix(vector<vector<int>> &v){
        matrix = v;
    }

    Point* findMaxSubArray(int arr[]){
        int best=-INT_MAX;
        int partialBest = 0;
        int start = 0;
        Point *p;
        for(int i=0;i<col;i++){
            partialBest += arr[i];
            if(partialBest>best){
                best = partialBest;
                p = new Point(0,0,start, i, partialBest);
            }
            if(partialBest<0){
                start = i+1;
                partialBest = 0;
            }
        }
        return p;
    }

    Point* findSquareSum(int rowStart){
        int partial[col]={0};
        Point* bestPoint = NULL;
        int best = -INT_MAX;
        for (size_t i = rowStart; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                partial[j] += matrix[i][j];
            }
            Point* partialBest = findMaxSubArray(partial);
            if(partialBest->best > best)
            {
                best = partialBest->best;
                bestPoint = partialBest;
                bestPoint->rowEnd = i;
                bestPoint->rowStart = rowStart;
            }
        }
        return bestPoint;
    }

    Point* findMaxSum(){
        int best = -INT_MAX;
        Point* bestPoint = NULL;
        for(int i=0;i<col;i++){
            Point* p = findSquareSum(i);
            if(best<p->best)
            {
                best = p->best;
                bestPoint = p;
            }
        }
        return bestPoint;            
    }
};

class Trie{
    public:
    class Node{
        public:
        Node* child[alphabetSize];
        bool isEnd = false;
    };
    Node* root = NULL;
    unordered_map<string , vector<int>> dict;
    Node* getNode(){
        Node* node = new Node();
        node->isEnd = false;
        for(int i=0;i<alphabetSize ;i++){
            node->child[i] = NULL;
        }
        return node;
    }
    
    void insert(string word){
        if(!root ){
            this->root = getNode();
        }
        Node* crawl = root;
        for(int i=0;i<word.length();i++){
            int index = word[i] - 'a';
            if(!crawl->child[index] )
                crawl->child[index] = getNode();
            crawl = crawl->child[index];    
        }
        crawl->isEnd = true;
    }

    bool checkPrefix(string word){
        Node* crawl = root;
        for(int i=0;i<word.length();i++){
            int index = word[i] - 'a';
            crawl = crawl->child[index];
            if(!crawl)
                return false;
            
        }
        return true;
    }

    bool isComplete(string word)
    {
        Node* crawl = root;
        for(int i=0;i<word.length();i++){
            int index = word[i] - 'a';
            crawl = crawl->child[index];
            if(!crawl)
                return false;
        }

        return crawl!=NULL && crawl->isEnd;
    }
    void addCount(string word, int index, Node* root, string partial)
    {
        if(index>=word.length())
            return;
        int a = word[index] - 'a';
        Node* newRoot = root->child[a];
        if(newRoot){
            partial += word[index];
            if(newRoot->isEnd)
                dict[partial].push_back(index +1 - partial.length());
            addCount(word, index+1, newRoot, partial);
        }
        else{
            return;
        }
    }

    void addCountIter(string word, int index, Node *root){
        string partial = "";
       
        for(int i=index;i<word.length();i++){
            int a = word[i] - 'a';
            root = root->child[a];
            if(root){
                partial += word[i];
                if(root->isEnd)
                    dict[partial].push_back(index);
            }else
                return;
        }
        return;
    }

    void search(string word){
        for(int i=0;i<word.length();i++){
            //addCount(word, i, root, "");
            addCountIter(word, i, root);
        }
        for(auto itr = dict.begin();itr!=dict.end();itr++)
        {
            vector<int> positions = itr->second;
            string word = itr->first;
            cout<<word<<" ";
            for(auto ptr=positions.begin();ptr!=positions.end();ptr++)
                cout<<*ptr<<" ";
            cout<<endl;
        }            
    }

};
class wordStack{
    public:
    unordered_set<string> words;
    vector<string> stack;
    int height; int length;
    wordStack(int length){
        this->length = length;
        this->height = 0;

    }
    void print(){
        for(auto itr = stack.begin();itr!=stack.end();itr++)
            cout<<*itr<<endl;
    }
    wordStack* append(string word){
        wordStack* newRectangle = new wordStack(length);

        if(words.find(word)==words.end())
        {
            newRectangle->stack =  this->stack;
            newRectangle->stack.push_back(word);
            newRectangle->words = this->words;
            newRectangle->words.insert(word);
            newRectangle->height = newRectangle->words.size();
            return newRectangle;
        }
        return NULL;
    }

    string getColumn(int i){
        string partial="";
        for(auto itr = stack.begin();itr!=stack.end();itr++){
            partial += (*itr)[i];
        }
        return partial;
    }

    bool isPartialOk(Trie trie){
        if(height == 0)
            return true;
      
        for(int i=0;i<length;i++){
            string partial = getColumn(i);
            bool found = trie.checkPrefix(partial);
            if(!found)
                return false;
        }
        return true;
    }

    bool isComplete(unordered_set<string> words){
        for(int i=0;i<length;i++){
            string partial = getColumn(i);
            if(words.find(partial) == words.end())
                return false;
        }
        return true;
    }
};

class WordMatrix{
    unordered_map<int, unordered_set<string>> dict;
    Trie* trie;
    int maxLength=-1;
    public: 
    void push(string word){
        int length = word.length();
        maxLength = std::max(maxLength, length);
        dict[length-1].insert(word);
    }

    wordStack* createWordMatrix(int length, int height, wordStack* rectangle){
        if(rectangle->height == height){
            if(rectangle->isComplete(dict[height-1]))
                return rectangle;
            return NULL;    
        }
        if(dict.find(height-1)==dict.end())
            return NULL;
        if( !rectangle->isPartialOk(trie[height-1]))
            return NULL;

        unordered_set<string> group = dict[length-1];
        for(auto itr = group.begin();itr!=group.end();itr++){
            wordStack* newRectangle = rectangle->append(*itr);
            if(newRectangle){
                wordStack* valid = createWordMatrix(length,height, newRectangle);
                if(valid)
                    return valid;
            }
        }
        return NULL;
    }

    void createTrie(unordered_map<int, unordered_set<string>> wordGroups){
        trie = new Trie[maxLength];
        for(auto itr = wordGroups.begin();itr!=wordGroups.end();itr++){
            int index = itr->first;
            for(auto ptr = itr->second.begin();ptr!=itr->second.end();ptr++)
            {
                trie[index].insert(*ptr);
            }
        }
    }

    void findWordRectange(){
        createTrie(dict);
        for(int length= maxLength;length>0;length--){
            if(dict.find(length-1) != dict.end()){
                for(int height = dict[length-1].size();height>0;height--){
                    wordStack* rectangle = new wordStack(length);
                    wordStack* output = createWordMatrix(length, height, rectangle);
                    if(output){
                        output->print();
                        return ;
                    }
                }
            }
        }
    }

};

class SparseMatrix{
    unordered_map<int, vector<int>> wordToDoc;

    void wordToDocMapper(int** arr, int m, int n){
        for(int i=0;i<m;i++){
            int value = i;
            for(int j=0;j<n;j++){
                int key = arr[i][j];
                wordToDoc[key].push_back(value);
            }
        }
    }

    unordered_map<string, int> createIntersection(){
        unordered_map<string, int> intersect;
        for(auto itr = wordToDoc.begin();itr!=wordToDoc.end();itr++){
            vector<int> docId = itr->second;
            std::sort(docId.begin(),docId.end());
            for(auto i = docId.begin();(i+1)!=docId.end();i++){
                for(auto j = i+1;j!=docId.end();j++){
                    string key =to_string(*i) +" " + to_string(*j);
                   
                    if(intersect.find(key) == intersect.end())
                        intersect[key] = 1;
                    else
                        intersect[key]++;
                }
            }
        }

        return intersect;
    }

    public:
    void printIntersection(int** arr, int m, int n){
        wordToDocMapper(arr, m, n);
        unordered_map<string, int> output = createIntersection();
        for(auto itr = output.begin();itr!=output.end();itr++){
            cout<<itr->first<<" intersection value "<<itr->second<<endl;
        }
    }
};

// int testfunction(int** arr){
//     //do something
//     for(int i=0;i<2;i++)
//         for(int j=0;j<2;j++)
//             cout<<arr[i][j]<<" ";
//     return 1;
// }

int main(){
    SparseMatrix docs;
    int arr[4][3] = {{12,13,15},{12,13,17},{17,19,21},{99,8,77}};
    int **p = new int*[4];
    for(int i=0;i<4;i++)
        p[i] = arr[i];
    docs.printIntersection(p,3,3);
    // int arr[2][2]={{1,2},{1,2}};
    // int **p = new int*[2];
    // for(int i=0;i<2;i++)
    //     p[i] = arr[i];
    // testfunction(p);
    // WordMatrix matrix;
    // matrix.push("abcd");
    // matrix.push("bbcd");
    // matrix.push("zzzz");
    // matrix.push("ddde");
    // matrix.push("abc");
    // matrix.push("bbc");
    // matrix.push("cc");
    // matrix.push("abd");
    // matrix.push("bbd");
    // matrix.push("ccd");
    // matrix.push("ddd");
    // //matrix.push("dd");
    // matrix.findWordRectange();
    // Matrix matrix(7,7);
    // int arr[7][7]={
    //             {-20,-100,-23,100,2,3,-99},
    //             {-20,100,-23,100,2,3,-99},
    //             {-20,-100,23,100,2,3,-99},
    //             {-20,-100,23,-100,2,3,-99},
    //             {-20,100,23,100,2,3,99},
    //             {-20,100,23,100,2,3,99},
    //             {-20,100,23,100,2,3,-99}
    //             };
    // vector<vector<int>> input;
    // for(int i=0;i<7;i++){
    //     vector<int> cols;
    //     for(int j=0;j<7;j++){
    //         cols.push_back(arr[i][j]);
    //     }
    //     input.push_back(cols);
    // }
    // matrix.createMatrix(input);
    // Point* p = matrix.findMaxSum();
    // cout<<p->rowStart<<":"<<p->colStart<<endl;
    // cout<<p->rowEnd<<":"<<p->colEnd<<endl;
    // MedianGenerator mg;
    
    // int n ;
    // while(true){
    //     cout<<"enter number";
    //     cin>>n;
    //     if(n==-11)
    //         break;
    //     cout <<endl<<"current median"<<mg.generateMedian(n)<<endl;
    // }
    // int large[] = {7,5,9,9,2,1,3,5,0,9,1,1,5,8,8,9,7};
    // int small[] = {1,5,9};
    // int m = sizeof(large)/sizeof(large[0]);
    // int n = sizeof(small)/sizeof(small[0]);
    // cout<<findMinSubUsingHeap(large, small, m, n);
    // Trie words;
    // words.insert("is");
    // words.insert("ppi");
    // words.insert("hi");
    // words.insert("sis");
    // words.insert("i");
    // words.insert("ssippi");

    // string input ="mississippi";
    // words.search(input);
    // int arr[] = {30, 15, 60, 75, 45, 15, 15, 45};
    // int memo[8];
    // for(int i=0;i<8;i++)
    //     memo[i] = -1;
    // //cout<<findOptimalHour(arr,memo,0, 8);;
    // cout<<findOptimalHour(arr, 8);
    // vector<string> input;
    // input.push_back("cat");
    // input.push_back("rat");
    // input.push_back("ball");
    // input.push_back("rock");
    // input.push_back("ratball");
    // input.push_back("rockpapperrscissor");
    // input.push_back("papper");
    // input.push_back("ballscissor");
    // input.push_back("scissor");
    // input.push_back("choclateball");
    // string output = longestWord(input);
    // cout<<"longest word is "<< output;
    
    // unordered_set<string> dictionary;
    // dictionary.insert("looked");
    // dictionary.insert("just");
    // dictionary.insert("like");
    // dictionary.insert("her");
    // dictionary.insert("brother");
    // dictionary.insert("is");
    // string input = "jessisjustliketommherbrother";
    // Parse* memo[input.length()] ;
    // for(int i=0;i<input.length();i++)
    //     memo[i] = NULL;
    // Parse* output = reSpace(input, dictionary, 0 ,memo);
    // cout<<output->invalid<<":"<<output->parsed;
    // WordLocation words;
    // words.createMap();
    // cout<<words.findMinDistance("bikram","nayak")<<endl;
    // cout<<words.findMinDistance("kotwal", "chetna")<<endl;
    //cout<<findMinDistanceBetweenWord("bikram","nayak");
    // int n ;
    // cin>>n;
    // cout<<findKth(n)<<endl;
    // Circus circus(10);
    // circus.addPeople();
    // circus.findMax();
    // Node arr[9];
    // arr[0].name = "John";
    // arr[0].frequency = 10;

    // arr[1].name = "Jon";
    // arr[1].frequency = 3;

    // arr[2].name = "Davis";
    // arr[2].frequency = 2;

    // arr[3].name = "Kari";
    // arr[3].frequency = 3;

    // arr[4].name = "Johnny";
    // arr[4].frequency = 11;

    // arr[5].name = "Carlton";
    // arr[5].frequency = 8;

    // arr[6].name = "Carleton";
    // arr[6].frequency = 2;

    // arr[7].name = "Jonathan";
    // arr[7].frequency = 9;

    // arr[8].name = "Carrie";
    // arr[8].frequency = 5;

    // Graph graph(9);
    // graph.createGraph(arr);
    // graph.addEdge("Jonathan", "John");
    // graph.addEdge("Jon", "Johnny");
    // graph.addEdge("Johnny", "John");
    // graph.addEdge("Kari", "Carrie");
    // graph.addEdge("Carleton", "Carlton");

    // vector<pair<string, int>> output = graph.findTrueFrequency();
    // for(int i=0;i<output.size();i++){
    //     string name = output[i].first;
    //     int frequency = output[i].second;
    //     cout<<name<<" : "<<frequency<<endl;
    // }
    // string input = "aaaa11a11aa1aa1aaaaa";
    // cout<<"lonsest sub length :"<<findLongestSubarray(input, input.length());
    // list<int> input;
    // input.push_back(0);
    // input.push_back(1);
    // input.push_back(2);
    // input.push_back(3);
    // input.push_back(4);
    // input.push_back(5);
    // input.push_back(6);
    // input.push_back(7);
    // input.push_back(8);
    // //input.push_back(9);
    // input.push_back(10);
    // input.push_back(11);
    // cout<<"missing element is "<<findMissing(input, 0)<<endl;
}