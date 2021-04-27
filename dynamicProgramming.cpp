#include<iostream>
#include<stack>

using namespace std;
void findPermutation(string arr, string output, int size){
    if(output.length() == size)
    {
        cout<<output<<endl;
        return;
    }

    for(int i=0;i<size;i++){
        findPermutation(arr, output+arr[i], size);
    }
}

const int m=4;
const int n=4;

void findPath(int arr[m][n], int i, int j, bool &v, stack<string> &output){
    if(arr[i][j]==-1)
    {
        return;
    }
    if(i==m-1 && j==n-1)
    {
        v = true;
        output.push(to_string(i)+" : "+to_string(j));
        return;
    }
    //cout<<i<<j<<":"<<arr[i][j]<<endl;
    if(!v && i+1<m && j<n)
        findPath(arr,i+1,j,v,output);
    if(!v && i<m && j+1<n)
        findPath(arr,i,j+1,v,output);
    
    if(v){
        //cout<<arr[i][j]<<endl;
        output.push( to_string(i) + " : "+ to_string(j));
    }
}


int countWays(int n, int memo[]){
    if(n<0) return 0;
    else if (n==0) return 1;
    if(memo[n]) return memo[n];
    memo[n] =  countWays(n-1,memo) + countWays(n-2,memo) + countWays(n-3,memo);
    return memo[n];
}

int magicIndex(int arr[], int start, int end){
    if(end<start) return -1;
    int mid = (start+end)/2;
    if(arr[mid] == mid) return mid;
    int left = min(mid-1, arr[mid]);
    int right = max(mid+1, arr[mid]);
    int l  = magicIndex(arr,start, left);
    if(l>=0) return l;
    int r = magicIndex(arr, right, end);
    return r;
}

void combination(int arr[], int i, int n, string output){
    if(i==n) return;
    for(int j= i;j<n;j++){
        cout<<output<<arr[j]<<endl;
        combination(arr, j+1, n, output+ to_string(arr[j]));
    }
}

void findCombination(int arr[], int n){
    cout<<"@"<<endl;
    string output= "";
    
    combination(arr, 0, n, output);
}
//find multiplication of two number without using * or / operation.
//assumption - first input is smaller then 2nd one.
int findMultiplication(int smaller, int bigger){
    if(smaller == 0) return 0;
    if(smaller == 1) return bigger;
    int mid = smaller >> 1;
    int half = findMultiplication(mid, bigger);
    if(smaller % 2 == 0)
        return half + half;
    else 
        return half + half + bigger; 
}

void towerOfHanoi(int n, int start, int spare, int end){
    if(n==1) {
        cout<<"Move disk 1 from"<<start<<" to "<< end<<endl;
        return ;
    }
    towerOfHanoi(n-1,start, end, spare);
    cout<<"Move disk "<<n <<"from "<<start<< "to "<< end<<endl;
    towerOfHanoi(n-1, spare, start, end);
}

void permutation(string prefix, string input){
    if(input == ""){
        cout<<prefix<<endl;
         return;
    }

    for(int i =0;i<input.length() ; i++){
        string t = input.substr(0,i) + input.substr(i+1, input.length() - i - 1);
        char c = input.at(i);
        if(i>0 && input[i-1]==c)
            continue;
        permutation(prefix+c, t);
    }
}

void createPeran( int left , int right, char input[], int count, int n){
    if(left < 0 || right < left ) return ;
    
    if(left == 0 && right ==0 )//valid condition
    {
        for(int i=0;i<n;i++){
            cout<<input[i];
        }cout<<endl;
    }

    if(left>0){
        input[count] = '(';
        createPeran(left-1, right, input, count+1,n);
    }

    if(right>left){
        input[count] = ')';
        createPeran(left, right-1, input, count+1,n);
    }
}


void coins(int n, int arr[],int length,  int &output, int ind){
    if(n<0) return;
    if(n==0){ 
        //cout<<"match found";
        output+=1;
    }
    for(int i=ind;i<length;i++)
        coins(n-arr[i], arr, length, output, i);
}

void coinsWithCache(int n,int memo[][4], int arr[], int length, int &output, int ind){
    if(n<0) return ;
    if(n==0){ 
        //cout<<"match found"<<endl;
        output+=1;
    }
    for(int i=ind;i<length; i++){
        int tempOut= output;
        //cout<<"before output "<<tempOut<<endl;
        //cout<<"memo "<<memo[n][i]<<endl;
        if(memo[n][i]){ 
            output += memo[n][i];
            continue;
        }
        coinsWithCache(n - arr[i], memo, arr, length, output, i);
        //cout<<"after output "<<output<<endl;
        memo[n][i] = output - tempOut;
    }
}

//coumns[i] contain column number which has a queen.
bool validCell(int row1,int col1, int columns[]){

    for(int row2=0;row2<row1; row2++){
        if(columns[row2] == col1)//queen is already placed in that column
            return false;
        int colDiff = col1 - columns[row2];
        int rowDiff = row1 - row2;
        if(abs(colDiff) == abs(rowDiff))
            return false;

    }

    return true;
}
void eightQueen(int columns[], int row){
    //if(row>=8) return;
    if(row ==8){
        cout<<"path :";
        for(int i =0;i<8;i++){
            cout<<columns[i];
        }
        cout<<endl;
        return ;
    }
    for(int i=0;i<8;i++){
        if(validCell(row, i, columns)){
            columns[row] = i;
            eightQueen(columns, row+1);
        }
    }
}

int main(){
    int arr[8];
    for(int i=0;i<8;i++)
        arr[i] = 0;
   
    // string str = "bikram";
    // cout<<str;
    // str[0] = 'B';
    // cout<<str;
    //eightQueen(arr, 0);
    // int arr[] = {25,10,5,1};
    // int output_old = 0;
    // int output = 0;
    // int n;
    // cin>>n;
    // auto start = high_resolution_clock::now();
    // //coins(n, arr, 4, output_old,0);
    // auto end = high_resolution_clock::now();
    // auto duration = duration_cast<seconds>(end - start);
    // //cout<<"time taken for this function : "<<duration.count()<<endl;
    // //cout<<"without cache"<<output_old<<endl;
    // int memo[n+1][4] ;
    // //cout<<"size "<<sizeof(memo)/sizeof(memo[0])<<endl;
    // for(int i =0;i<=n;i++){
    //     for(int j=0;j<4;j++){
    //         memo[i][j] = 0;
    //     }
    // }
    // start = high_resolution_clock::now();
    // coinsWithCache(n,memo,arr,4, output, 0);
    // end = high_resolution_clock::now();
    // duration = duration_cast<seconds>(end - start);
    // cout<<"time taken for this function : "<<duration.count()<<endl;
    // cout<<"with cache  "<<output<<endl;
    // for(int i =0;i<=n;i++){
    //     for(int j=0;j<4;j++){
    //         cout<<"memo diff "<<i<<" key "<<arr[j]<<" value "<<memo[i][j]<<endl;
    //     }
    // }
    
    // int n=2;
    // cin>>n;
    // char ip[2*n];
    // createPeran(n,n,ip,0,2*n);
    
    // permutation("", "AADDBBBB");
    
    
    // int n=4;
    // int arr[n+1] = {1,2,3,4};
    // findCombination(arr, n);
    // int a;
    // cin>>a;
    // towerOfHanoi(a,1,2,3);
    //cout << "Multiplication : "<<findMultiplication(7,9);
    //cout<<countWays(n,arr);
    // int arr[m][n]={{0,0,-1,0},{0,0,0,0},{0,-1,0,0},{-1,0,-1,0}};
    // stack<string> output;
    // bool found = false;
    // findPath(arr,0,0,found, output);
    // cout<<"output ";
    // while(!output.empty()){
    //     cout<<output.top()<<endl;
    //     output.pop();
    // }
   
    // char steps[3]={'1','2','3'};
    // string name = "abcdef";
    // findPermutation(name, "",5);
    // cout<<"hello world";
}