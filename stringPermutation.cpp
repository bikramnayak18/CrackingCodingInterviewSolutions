#include <iostream>
#include<unordered_map>
//#include<string>
using std::cout;
using std::string;
using namespace std;

void permutation(string str, string prefix){
    if(str.length()==0)
        cout<< prefix<<endl;//this is a permutated string
    for(int i =0;i< str.length();i++){
        string rem = str.substr(0,i) + str.substr(i+1);
        cout<<"str "+rem<<" prefix "+prefix+str.at(i)<<endl;
        permutation(rem, prefix + str.at(i));
    }
}


void checkIfTwoStringsArePermutable(string str, string str2){
    
    if(str.length()!=str2.length()){
        cout<<"Not a valid case";
        return;
    }else if(str.length()==0 && str2.length()==0) cout<<"yes";

    unordered_map<char, int> charFrequency ;
    for(int i =0;i<str.length();i++){
        if(charFrequency.find(str[i]) == charFrequency.end())
            charFrequency.insert(make_pair(str[i],1));
        else
            charFrequency[str[i]]++;            
    }

    for(int i=0;i<str2.length();i++){
        if(charFrequency.find(str2[i])==charFrequency.end()){
            cout<<"no";
            return;
        }else if(charFrequency[str2[i]]<=0)
        {
            cout<<"no";
            return;
        }else{
            charFrequency[str2[i]]--;
        }
    }

    cout<<"Yes";
}

bool pallindromePermutation(string str1){
    unordered_map<char,int> dict;
    int charCount=0;
    for(int i=0;i<str1.length();i++){
        charCount++;
        if(dict.find(str1[i]) == dict.end())//new char
            dict[str1[i]] = 1;
        else
            dict[str1[i]]++;
    }
    
    bool isEven = charCount%2==0;
    //cout<< isEven<<endl;
    for(auto itr = dict.begin();itr!=dict.end();itr++){
        //cout<<itr->first << itr->second<<endl;
        if(isEven) 
           // cout<<"Even";
            if(itr->second %2 !=0 ) 
                //cout<<"invalid";
                return false;
        else
            //cout<<"odd";
            if(itr->second % 2 !=0)
                isEven = true;
              //  cout<<"isEven";
    }
    return true;
}


int main()
{
    string str;
    cout << "Hello World" << endl;
    getline(cin,str );
    cout<<pallindromePermutation(str);
    
}
