#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<list>
using namespace std;

int solution(vector<int> &A, int S) {
    int final=0;
    for(int i=0;i<A.size();i++){
        int count=0, sum=0;
        for (int j=i;j<A.size();j++){
            sum += A[j];
            count++;
            if(count*S == sum) final++;
        }
    }
    return final;
}

int arithmaticSum(vector<int> &A, int S){
    unordered_map<int, int> q;
    int p[A.size()+1];
    p[0]=0;
    q[0] = 1;
    for(int i=1;i<=A.size();i++){
        p[i] = p[i-1] + A[i-1] ;
        int index = p[i] - S*i;
        if(q.find(index) == q.end())//not present
        {
            q[index] = 1;
        }else{
            q[index]++;
        }
    }
    int final = 0;
    for(auto itr = q.begin();itr!=q.end();itr++){
        int n = itr->second;
        final += n*(n-1)/2;
    }

    return final;
}

string getHashIndex(string name){
    int length = name.length();
    int j;
    int count =0;
    for(j=length-1;j>=0;j--)
    {
        int ascii = (int) name[j];
        if(ascii<97 || ascii>122 )
            break;
        count++;
    }
    return name.substr(0, length - count );
}

int solution(vector<string> &T, vector<string> &R) {
    unordered_map<string, string> result;
    if(T.size() != R.size()) return 0;
    for(int i=0;i<T.size();i++)   
    {
        string key = getHashIndex(T[i]);
        if(result.find(key) != result.end())
            result[key] = R[i];
        else if(result[key] == "OK")
            result[key] = R[i];
    }
    int final=0;
    int group=0;
    for (unordered_map<string,string>::iterator i = result.begin(); i != result.end(); i++)
    {
        if( i->second == "OK") final++;
        group++;
    }
    return (final*100)/group;
}

unordered_map<int,int> uniqueElements(vector<int> a){
    unordered_map<int,int> map;
    for(int i=0;i<a.size();i++){
        map[a[i]] = 0;
    }
    return map;
}

int solution(vector<int> &A) {
    int count =0;
    unordered_map<int, int> unique = uniqueElements(A);
    int uniqueCount = unique.size();
    int min = INT_MAX;
    for(int i=0;i<A.size();i++){
        for(auto itr = unique.begin();itr!=unique.end();itr++){
            itr->second = 0;
        }
        int minCount = 0;
        count = 0;
        bool match = false;
        if(i+1<A.size() && A[i] == A[i+1])
            continue;
        for(int j=i;j<A.size();j++){

            if(unique[A[j]] == 0 )
            {
                count++;
                unique[A[j]] =  1;
            }
            minCount++;
            if(count == uniqueCount){
                match = true;
                break;
            }
        }
        if(match && min>minCount) min = minCount;
        cout<<"min value "<<min<<endl;
    }
    return min;    
}

int main(){
    int arr[7] = {5,3,6,2,5,5,2};
    vector<int> test;
    for(int i=0;i<7;i++)
        test.push_back(arr[i]);
    int result = arithmaticSum(test,4);
    cout<<"final result "<<result;
    // int arr[] = { 1, 1, 2, 1, 1, 3, 4, 3 }; 
    // int n = sizeof(arr) / sizeof(arr[0]); 
  
    // unordered_map<string, string> m; 
    // for (int i = 0; i < n; i++) 
    //     m[getHashIndex("bikram12az")]="ok"; 
    
    // cout << "Element Frequency" << endl; 
    // for (auto i : m) 
    //     cout << i.first << "    " << i.second 
    //          << endl; 
    // cout<<getHashIndex("bikram12az");
}