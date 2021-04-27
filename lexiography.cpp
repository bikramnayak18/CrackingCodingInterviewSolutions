#include<iostream>
using namespace std;

string greaterThenBigger(string input){
    int arr[26];
    for(int i=0;i<26;i++)
        arr[i] = -1;
    char max='a';
    for(int i=0;i<input.length();i++){
        int index = input[i] - 'a';
        arr[index] = 1;
        if(input[i]>max)
            max = input[i];
    }
    int s1=0, s2=0;
    int i=0;
    for(i=input.length()-1;i>=0;i--){
        if(input[i]!=max)
        {
            s1 = i;
            break;
        }
    }
    char a = input[i];
    char b ;
    for(i=a-'a'+1;i<26;i++)
    {
        if(arr[i]!=-1){
            b ='a' + i;
            break;
        }
    }
    for(i=input.length()-1;i>=0;i--)
        if(input[i] == b)
        {
            s2 = i;
            break;
        }
    if(s1==s2)
        return "no answer";
    char temp = input[s1];
    input[s1] = input[s2];
    input[s2] = temp;
    return input;
}

void swap(string &arr, int i, int j){
    char temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

string nextGreater(string input){
    int s1=-1, s2=-1;
    int i=0;
    for(i=input.length();i>0;i--){
        if(input[i]>input[i-1])
        {
            s1= i-1;
            break;
        }
    }
    if(s1==-1)
        return "no answer";
    for(i=input.length();i>0;i--){
        if(input[i]>input[s1])
        {
            s2 = i;
            break;
        }
    }
    if(s1==s2)  return "no answer";
    while(s2!=input.length()){
        swap(input, s1++,s2++);
    }
    return input;
} 

int main()
{
    string input = "";
    getline(cin, input);   
    cout<<nextGreater(input)<<endl;
}