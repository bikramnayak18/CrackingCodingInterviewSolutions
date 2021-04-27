#include<iostream>
#include<math.h>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<map>
#include<fstream>

using namespace std;

int partition(int arr[], int left, int right){
    int mid = (left+right)/2;
    int partion = arr[mid];
    while(left<=right){
        while(arr[left]<partion) left++;
        while(arr[right]>partion) right--;
        if(left<=right){
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;right--;
        }
    }
    return left;
}

void quickSort(int arr[], int left, int right){
   
   int pivot = partition(arr, left , right);
   if(left<pivot-1)
        quickSort(arr, left, pivot-1);
   if(right>pivot) 
        quickSort(arr, pivot, right);
}

void mergeArray(int arr[], int helper[], int left, int mid, int right){
    for(int i=left;i<=right;i++)
        helper[i] = arr[i];

    int curr = left;
    int lp = left;
    int rp = mid+1;
    while(lp<=mid && rp<=right){
        if(helper[lp]<=helper[rp])
        {
            arr[curr] = helper[lp];
            lp++;
        }else{
            arr[curr] = helper[rp];
            rp++;
        }
        curr++;
    }

    while(lp<=mid){
        arr[curr] = helper[lp];
        lp++;
        curr++;
    }
}

void mergeSort(int arr[], int helper[], int left , int right){
    if(left<right)
    {
        int mid = (left + right)/2;
        mergeSort(arr, helper, left, mid);
        mergeSort(arr, helper, mid+1, right);
        mergeArray(arr, helper, left, mid, right);
    }
}

void mergeSort(int arr[], int n){
    cout<<"calling merge sort: "<<endl;
    int helper[n];
    mergeSort(arr, helper, 0, n-1);
}

//taking only positive number for sorting
void countingSort(int arr[], int n, int max){
   
    int helper[max];
    for(int i=0;i<max;i++){
        helper[i] = 0;
    }

    for(int i=0;i<n;i++){
        helper[arr[i]]++;
        cout<<helper[arr[i]]<<endl;
    }

    for(int i=1;i<max;i++){
        helper[i] += helper[i-1];
        cout<<"adding count "<<helper[i]<<endl;
    }

    for(int i =0;i<max; i++)
        cout<<helper[i];
    cout<<endl;
    int output[n];
    for(int i=0;i<n;i++)
        output[i] = 0;
    for(int i=0;i<n;i++){
        int temp = helper[arr[i]]--;
        cout<<arr[i]<<":"<<temp<<endl;

        output[temp-1] = arr[i];   
    }        

    cout<<"printing sorted array by counting sort";
    for(int i=0;i<n;i++)
        arr[i] = output[i];
}

void countingSort(int arr[], int n){
    int max =-1;
    for(int i=0;i<n;i++){
        if(max<arr[i])
            max = arr[i];
    }
    max++;
    return countingSort(arr, n, max);
}

int getMax(int arr[], int n){
    int max =-1;
    for(int i=0;i<n;i++){
        if(max<arr[i])
            max = arr[i];
    }
    int size=0;
    while(max>0){
        size++;
        max = max/10;
    }
    return size;
}

void countSortForRedix(int arr[], int n, int exp){
    int count[10];
    int output[n];
    for(int i=0;i<10;i++)
        count[i] = 0;

    for(int i=0;i<n;i++)
        output[i] = 0;

    for(int i=0;i<n;i++)
        count[(arr[i]/exp)%10]++;

    for(int i=1;i<10;i++)
        count[i]+=count[i-1];

    for(int i=n-1;i>=0;i--)
    {
        int position =  count[(arr[i]/exp)%10]-1;
        //cout<<position<<endl;
        output[position] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for(int i=0;i<n;i++)
    {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n){
    int max = 10;//considering number base 10
    int size = getMax(arr, n);
    cout<<"size"<<size<<endl;
    for(int i=0;i<size;i++){
        cout<<"current exp"<<pow(10,i);
        countSortForRedix(arr, n, pow(10,i));
    }
    cout<<endl;
}


void bucketSort(float arr[], int n){
    vector<float> buckets[n];  //if i make array of 100 each element will have un
    for(int i=0;i<n;i++){
        int index = arr[i]*n;//this hashing only works if arr[i] is always between 0-1
        buckets[index].push_back(arr[i]);
    }
    //sort each bucket
    for(int i=0;i<n;i++)
        sort(buckets[i].begin(), buckets[i].end());

    //merge all buckets
    int index = 0;
    for(int i=0;i<n;i++){
        for(auto j=0;j<buckets[i].size();j++)        {
            arr[index++] = buckets[i][j];   
        }
    }

}

//a is large enough array to hold elements of b as well. Perform in place sorting.. no extra memory
//empty cells are represented by -1
void sortedMerge(int a[], int b[], int m, int n){
    int aend=-1;
    int bend=n-1;
    for(int i=0;i<m;i++){
        if(a[i]!=-1) aend++;
    }
    int end = aend+n;
    while(aend>=0 && bend>=0){
        if(a[aend]>b[bend])
            a[end] = a[aend--];
        else 
            a[end] = b[bend--];
        end--;
    }
    while(bend>=0)
        a[end--] = b[bend--];

}

//sorted array is rotated unkonwn times
//12345678
//34567812
int searchInRotatedArray(int arr[], int left, int right, int item){
    int mid = (left+right)/2;
    if(arr[mid] == item)     return mid;
    if(left>right) return -1;
    if(arr[left]<arr[mid]){//left is sorted
        if(item>=arr[left] && item<arr[mid])
            return searchInRotatedArray(arr, left, mid-1,item);
        else
            return searchInRotatedArray(arr, mid+1, right, item);
    }else if(arr[right]>arr[mid]){//right is sorted
        if(item<=arr[right] && item>arr[mid])
            return searchInRotatedArray(arr, mid+1, right, item);
        else
            return searchInRotatedArray(arr, left, mid-1, item);
    }

    if(arr[mid] == arr[left]){//duplicates are there....
        if(arr[mid] != arr[right])
            return searchInRotatedArray(arr, mid+1, right, item);
        else//search left and right
        {
            int result = searchInRotatedArray(arr, left, mid-1, item);
            if(result ==-1)
                return searchInRotatedArray(arr, mid+1, right, item);
            else
                return result;
        }
    }
    return -1;
}


void groupAnagrams(string arr[], int n){
    unordered_map<string, vector<string>> dict;

    for(int i=0;i<n;i++){
        string temp = arr[i];
        sort(temp.begin(),temp.end());
        dict[temp].push_back( arr[i]);
    }

    for(auto itr = dict.begin();itr!=dict.end();itr++){
        for(auto ptr = itr->second.begin();ptr!=itr->second.end();ptr++){
            cout<<*ptr<<" ";
        }
        cout<<endl;
    }
}

void missingInteger(){
    ifstream fileData;
    fileData.open("C:\\files\\input.txt");
    if(!fileData){
        cout<<"file could not be opened";
        return;
    }
    int total = 500000;
    
    int n = total/32;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        arr[i] = 0;
    }
    int i;
    cout<<"Reading from file"<<endl;
    while(!fileData.eof()){
        fileData>>i;
        int word = i/32;
        int bit = i%32;
        //cout<<i;
        arr[word]  = (arr[word] |  1 << bit); 
    }
   
    for(int i=0;i<n;i++){
        //if any cell is not all 1's
            for(int j=0;j<32;j++)
            {
                int mask = (arr[i] & 1<<j);
                if(mask == 0 ){
                    cout<<"missing element"<< (i*32 + j)<<endl;
                }
            }
    }
    fileData.close();
    cout<<"file end reached";
}

void findDuplicates(){
    ifstream readFile;
    readFile.open("C:\\files\\input.txt");
    int total = 500000;
    int n =total/32;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        arr[i] = 0;
    }
    int i=0;
    while(!readFile.eof()){
        readFile >> i;
        int word = i/32;
        int bit = i%32;
        if( (arr[word] & (1<<bit) )==0 )
            arr[word] = arr[word] | 1<<bit;
        else//duplicate found
            cout<< i<<endl;
    }
}

class BinaryTree{
    private: class node{
        public:
        int item = 0;
        node* right = NULL;
        node* left = NULL;
        int rank=0;
    };

    node* root = NULL;
    node* insert(node* root, int item){
       
        if(!root) 
        {
            node* temp = new node;
            temp->item = item;
            return temp;
        }

        if(item <= root->item){
            root->rank++;
            root->left = insert(root->left, item);
        }
        else{
            root->right = insert(root->right,item);
        }
        return root;
    }

    int getRank(node* root, int item){
        
        if(root->item == item) return root->rank;
        else{
            if(item > root->item){
                int rightRank = root->right == NULL?-1:getRank(root->right, item);
                if(rightRank==-1) return -1;
                else return 1 + root->rank + rightRank;
            }else
            {
                if(root->left == NULL) return -1;
                else return getRank(root->left, item);
            }
        }
    }

    public: void insert(int item){
        if(!root){
            root = insert(root, item);
        }else
        {
            insert(root, item);
        }
    }

    int getRank(int item){
        return getRank(root, item);
    }
};



void swap(int arr[], int i, int j, int k){//j is the peak index
    int max = -1;
    if(k==-1)
    {
        if(arr[i]>arr[j])
            max = i;
    }
    else if(arr[i]>arr[j] && arr[i]>arr[k])//i is max element
    {
        max = i;
    }else if(arr[k]>arr[j] && arr[k]>arr[i])//k is the max element
    {
        max = k;
    }
    if(max !=-1){
        int temp = arr[max];
        arr[max] = arr[j];
        arr[j] = temp;
    }
}

void peakValey(int arr[], int n){
    if(n<3) return ;
    for(int i=0;i<n;i += 2){
        if(i==0)
            swap(arr, 1,0,-1);//0 is peak index
        else if(i == n-1)
            swap(arr, i-1, i,-1);//i is peak index
        else 
            swap(arr, i-1, i , i+1);
    }

    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
}

int main(){

    int arr[7] = {9,1,0,4,8,7,1};
    peakValey(arr,7);
    // BinaryTree BT;
    
    // BT.insert(20);
    // BT.insert(15);
    // BT.insert(10);
    // BT.insert(5);
    // BT.insert(13);
    // BT.insert(25);
    // BT.insert(23);
    // BT.insert(24);
    // int n;
    // cin>>n;
    // cout<<"Rank of item "<<n<<" is "<<BT.getRank(n);
    // cout<<"missing integers "<<endl;
    // missingInteger();
    // cout<<"duplicates "<<endl;
    // findDuplicates();
    // int test, test2;
    // cin>>test>>test2;
    // cout<<test<<endl<<test2<<endl;
    // int arr[]={2,2,2,2,7,8,1,2};
    // int result  = searchInRotatedArray(arr, 0, 7, 8);
    // if(result==-1) cout<<"element not found"<<endl;
    // else cout<<"Element found at index "<<result<<endl;
    // string arr[] ={"test","estt","abbcd","nest","sent"};
    // groupAnagrams(arr, 5);
    //float arr[14] = {0.3,0.122,0.0,0.4,0.6,0.51,0.92,0.7,0.2,0.10,0.99,0.123,0.21,0.3};
 //   quickSort(arr, 0,9);
    //mergeSort(arr, 10);
   // radixSort(arr, 14);
   //bucketSort(arr, 14);
//    for(int i=0;i<14;i++)
//         cout<<arr[i]<<",";
    
//    int a[100] ;
//    int b[10] = {1,5,20,21,23,35,77,86,98,98};
//    for(int i=0;i<100;i++)
//         a[i] = -1;
//     for(int i=0;i<20;i++)
//         a[i] =i+i;
    
//     cout<<"a : ";
//     for(int i=0;i<100;i++)
//         cout<<a[i]<<",";
//     cout<<endl<<"b : ";
//     for(int j=0;j<10;j++)
//         cout<<b[j]<<",";
//     sortedMerge(a,b,100,10);
//     int i=0;
//     cout<<endl<<"after sorting..."<<endl;
//     while(a[i]!=-1){
//         cout<<a[i++]<<",";
//     }


}