#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

struct trie{
    bool wordEnd;
    unordered_map<char, trie*> maped;
};

class WordDictionary{
    trie* head = NULL;

    trie* getNode(){
        trie* node = new trie;
        node->wordEnd = false;
        return node;
    }

    public:
    void insert(string str){
        if(head == NULL){
            head = getNode();
        }
        trie* curr = head;
        for(int i=0;i<str.length();i++){
            if(curr->maped.find(str[i])==curr->maped.end()){
                curr->maped[str[i]] = getNode();
            }
            curr = curr->maped[str[i]];
            
        }
        curr->wordEnd = true;
    }

    bool search(string str){
        if(head == NULL)
            return false;
        trie* curr = head;
        for(int i=0;i<str.length();i++){
            curr = curr->maped[str[i]];
            if(curr == NULL)
                return false;
        }
        return curr->wordEnd;
    }

    // trie* getCurrentNode(char c, trie* curr){
    //     return curr->maped[c];
    // }
    
    string numberToLetter(int n){
        string mapping[10]= {"", "", "abc", "def","ghi", "jkl", "mno", "pqrs", "tuvw", "xyz" };
        return mapping[n];
    }

    void makeWords(string input, int n, string output, vector<string> &totalList, int index, trie* curr){
        if(index == n){
            if(curr->wordEnd)
                totalList.push_back(output);
            return ;
        }
        int number =  input[index]-'0';
        string charSet = numberToLetter(number);
        if(charSet.length()==0)
            makeWords(input, n, output, totalList, index+1);
        else{
            for(int i=0;i<charSet.length();i++){        
                curr = curr->maped[charSet[i]];
                if(curr == NULL) return ;
                makeWords(input, n, output+charSet[i], totalList, index+1);
            }
        }
    }

    void getValidWords(string input, int n, vector<string> &totalList, int index){
        trie* curr = head;
        makeWords(input, n, "", totalList, 0,curr);
    }
};


int main()
{
    WordDictionary dict;
    string words[] = {"test","tess","tap","cat","cap","pet","pat","sold","gold","bottle"};
    for(int i=0;i<10;i++){
        dict.insert(words[i]);
    }
     vector<string> output;
    string input = "8700";
    dict.getValidWords(input, 4, output, 0);
    for(auto i:output){
        cout<<i<<endl;
    }
    // cout<<dict.search("test");
    // cout<<dict.search("tess");
    // cout<<dict.search("bottle");
    // cout<<dict.search("bott");
    // cout<<dict.search("tes");
    // cout<<dict.search("cati");
}