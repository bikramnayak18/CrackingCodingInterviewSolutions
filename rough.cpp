#include<iostream>
#include<vector>
#include<list>
#include<tuple>
using namespace std;
#include<unordered_map>
#include<algorithm>
#include<bits/stdc++.h>
void ifPossible(string str, string ptr){
    bool isEqual  = str.length()  == ptr.length();
    int j = 0; bool mismatch = false ;
    for(int i =0 ;i< str.length() ; i++, j++){
        if(str[i]==ptr[j]) continue;
        if(!mismatch){
            mismatch = true;
            if(!isEqual) 
                j--;
        }
        else if(mismatch)
        {
            cout<<"false"<<endl;
            return;
        }

        
    }
    cout<<"True"<<endl;
}

void stringCompression(string str){
    int counter = 1;
    string output = "";
    int n  = str.length();
    for(int i = 1 ;i<n;i++){
        //cout<<str[i];
        if(str[i-1] == str[i]){
            counter++;
        }
        else{
            //cout<<output<<str[i-1]<<counter<<endl;
            output +=  str[i-1] + to_string(counter);
            counter = 1;
        }
    }
    output =output +  str[n-1] + to_string(counter);
    cout<<output<<endl;
}

//sub is a substring of str
int isSubstring(string sub, string str){
    int m  = sub.length();
    int n = str.length();
    cout<<n-m<<str<<endl;
    for(int i =0 ;i<n-m;i++){
        int j = 0 ;
        for(j=0;j<m;j++){
           
            if(sub[j] != str[i+j]) { break;}
        }
        if(j == m) return i;
    }
    return -1;
}

void stringRotation(string str, string ptr){
    ptr += ptr;
   // cout<<ptr<<str<<isSubstring(ptr,str);
    if(isSubstring(str,ptr)!=-1) cout<<"possible";
    else cout<<"not possible";
}



class Box {
   public:
      // Constructor definition
      Box(double l = 2.0, double b = 2.0, double h = 2.0) {
         cout <<"Constructor called." << endl;
         length = l;
         breadth = b;
         height = h;
      }
      double Volume() {
         return length * breadth * height;
      }
      
   private:
      double length;     // Length of a box
      double breadth;    // Breadth of a box
      double height;     // Height of a box
};


class testobj{
    public: int a=0; int b=0;
};

void testArray( int a[3], testobj* obj){
        a[0]=2;
        a[1]=4;
        a[2] =3;
        obj->a=99;
}

string getTagName(string str){
    int end = str.find(' ');
    return str.substr(1,end-1);
}

bool isEndTag(string a, string b){
    if(b.find('/') == string::npos) return false;
    return b.substr(1,b.length()-2) == a;
}

string getAttributeValue(string str, string xml){
    string attrName = str.substr(str.find('~')+1);
    int start = -1;
    int p=0;
    for(int i =0;i<xml.length();i++){
        if(xml[i]==' ')
        {
            string word = xml.substr(p, i-p);
            if(word == attrName){
                start = i+4;
                break;
            }
            p=i+1;
        }
    }
    
    if(start ==-1) return "Not Found!";
    int length = xml.find('"',start);
    string value = xml.substr(start, length-start);
    return value;
}
//this need to be modified to indentify proper tag index for nested tags as well...
int findTag(string xml[], string query, int n){
    string prevTag = "";
    size_t position = 0;
    int prev =0;
    int j=0;
    while(position < query.find('~')){
        position = query.find('.', position+1);
        if(position == string::npos)//. is not present anymore, search for ~
            position = query.find('~');
        string tag = query.substr(prev, position-prev);
        prev = position +1;
        for(int i =j ;i<n;i++){
            string t = getTagName(xml[i]);
            if(!isEndTag(prevTag, t)){
                if(t==tag)
                    break;
            }else{
                return -1;
            }
            j++;
        }
        prevTag = tag;
    }
    if(j==0){
        string t = getTagName(xml[0]);
        string tag = query.substr(0, query.find('~'));
        if(t != tag)
            return -1;
    }
    return j;
}

void printValue(string xml[], string queries[], int n, int q){
    for(int i=0;i<q;i++){
        int tagIndex = findTag(xml, queries[i], n);
        //cout<<"tagindex "<<tagIndex<<endl;
        if(tagIndex == -1) {
            cout<<"Not Found!"<<endl;
        }
        else{
            string value = getAttributeValue(queries[i], xml[tagIndex]);
            cout<<value<<endl;
        }
    }
}

tuple<int, char> testtuple(){
    return make_tuple(1, 'c');
}

void testStringStream(string str){
    stringstream ss(str);
    while (ss.good())
    {
        string sub;
        getline(ss, sub, ' ');
        cout<<sub<<endl;
    }
    cout<<endl;
}

void combination(char arr[], int index, int n, string prefix){
    for(int i=index;i<n;i++){
        string temp = prefix + arr[i];
        cout<< temp<<endl;
        combination(arr, i+1, n, temp);
    }
}
void getCombination(vector<int> input, int index, int k, vector<int> buffer, int output){
    for(auto itr=input.begin()+index;itr!=input.end();itr++){
        vector<int> temp;
        int sum = *itr;
        temp.push_back(*itr);
        for(auto ptr = buffer.begin();ptr!=buffer.end();ptr++){
            sum += *ptr;
            temp.push_back(*ptr);
        }
        if(sum%k==0 && output< temp.size()){
            output = temp.size();
        }
        getCombination(input, index, k, temp, output);
    }
}

void decToBinary(unsigned int n){
    if(n==0) return ;
    int a = n&1;
    decToBinary(n>>1);
    cout<<a;
}

int nonDivisibleSubset(int k, vector<int> s) {
    int output=0;
    vector<int> buffer;
    getCombination(s, 0, k, buffer, output);
    return output;
}

int commonSub(string virus, string person){
    
}

int main(){
    decToBinary(33);
    // char arr[4] = {'a','b','c','d'};
    // combination(arr, 0, 4, "");
    // int n=4;
    // string str[4];
    // int i=0;
    // while(n-- > 0){
    //     getline(cin, str[i++]);
    // }
    // string arr[4][5];
    
    // for(i=0;i<4;i++){
    //     stringstream ss(str[i]);
    //     int j=0;
    //     while(ss.good()){
    //         getline(ss,arr[i][j++],' ' ) ;
    //     }
    // }
    // cout<<"printing..."<<endl;
    // for(i=0;i<4;i++){
    //     for(int j=0;j<5;j++)
    //         cout<<arr[i][j]<<" ";
    //     cout<<endl;
    // }
    //testStringStream("1 2 3 4");
    // int i; char j;
    // tie(i, j) = testtuple();
    // cout<<i<<" "<<j<<endl;
    // tuple<int, char> test = make_tuple(1,'2');
    // tuple<int, char> test2 = make_tuple('d','r');
    // test.swap(test2);
    // cout<<get<0>(test)<<get<1>(test)<<endl;
    // cout<<get<0>(test2)<<get<1>(test2)<<endl;
    // string xml[10] = {
    //     "<a value = \"GoodVal\">","<b value = \"BadVal\" size = \"10\">","</b>","<c height = \"auto\">","<d size = \"3\">","<e strength = \"2\">",
    //     "</e>","</d>","</c>","</a>"
    // };
    // string queries[10]={"a~value","b~value","a.b~size","a.b~value","a.b.c~height","a.c~height","a.d.e~strength","a.c.d.e~strength","d~sze","a.c.d~size"};
    // printValue(xml, queries, 10,10);
//      std::string str ("There are two needles in this haystack with needles.");
//   std::string str2 ("needless");

//   // different member versions of find in the same order as above:
//   std::size_t found = str.find(str2);
//   cout<<found<<endl;
//   if (found!=std::string::npos)
//     std::cout << "first 'needle' found at: " << found << '\n';

//   found=str.find("needles are small",found+1,6);
//   if (found!=std::string::npos)
//     std::cout << "second 'needle' found at: " << found << '\n';
//     int arr[] = {10, 21, 5, 23 ,42, 20, 15};
//     int n = sizeof(arr)/sizeof(arr[0]);
//     list<int> vect(arr, arr+n);
 
//     cout << "Occurrences of 20 in vector : ";
 
//     // Counts the occurrences of 20 from 1st to
//     // last element
//     cout << count(vect.begin(), vect.end(), 20);
 
//     // find() returns iterator to last address if
//     // element not present
//     find(vect.begin(), vect.end(),5) != vect.end()?
//                          cout << "\nElement found":
//                      cout << "\nElement not found";
 
//     return 0;
//     unordered_map<string, vector<string>> test;
//     string ab="bikram";
//     string bb="bidsam";
//     bool result = ab>bb;
//     cout<<result <<endl;
//     test["bikram"].push_back("nayak");
//     test["bikram"].push_back("test");
//     test["test2"].push_back("test2vale");
//     for(auto x:test){
//         for(int i =0;i<x.second.size();i++)
//             cout<<x.first<<x.second[i]<<endl;
//     }
//      Box Box1(3.3, 1.2, 1.5);    // Declare box1
//    Box Box2(8.5, 6.0, 2.0);    // Declare box2
//     Box Box3(9, 6.0, 2.0);    // Declare box2
//    Box *ptrBox;                // Declare pointer to a class.

//    // Save the address of first object
//    ptrBox = &Box1;

//    // Now try to access a member using member access operator
//    cout << "Volume of Box1: " << ptrBox->Volume() << endl;

//    // Save the address of second object
//    ptrBox = &Box2;

//    // Now try to access a member using member access operator
//    cout << "Volume of Box2: " << ptrBox->Volume() << endl;
  
//    Box* ptrBox2 = new Box(9, 6.0, 2.0);
//    Box* ptr2 = ptrBox2;
   
//   //Box* ptrBox3 = Box3;//error
//    // Now try to access a member using member access operator
//    int a =10;
//    int *p ;
//     p = &a;
//    cout << "Volume of Box3: " << ptrBox2->Volume() << endl;
//     //assuming str1 is larger/equal then str2 
//     int arr[3]={1,1,1};
//     arr[0]=0;
//     arr[1]=0;
//     arr[2]=0;
//     int d= 2;
//     for(int i=0;i<3;i++) cout<<arr[i]<<" ";
//     cout<<d;
//     testobj obj;
//     testArray(arr,&obj);
//     for(int i=0;i<3;i++) cout<<arr[i]<<" ";
//     cout<<obj.a;
//     string str1 = "", str2="", str3="", str4="";
//     std::vector<int> myvector;
//   for (int i=1; i<=5; i++) myvector.push_back(i);

//   std::cout << "myvector contains:";
//   for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); it++)
//     std::cout << ' ' << *it;
//   std::cout << '\n';
//     while(false){
//             cout<<"enter string 1 "<<endl;
//             getline(cin, str1);
//             cout<<"enter string 2 "<<endl;
//             getline(cin, str2);
//             stringRotation(str1, str2);
//             cout<<"do you want to quit yes/no";
//             getline(cin, str3);
//             if(str3 == "y")
//                 break;
//         }

//     while(false){
//         cout<<"enter string 1 "<<endl;
//         getline(cin, str4);
//         stringCompression(str4);
//         cout<<"do you want to quit yes/no";
//         getline(cin, str3);
//         if(str3 == "y")
//             break;
//     }
//     while(false){
    //     cout<<"enter string 1 "<<endl;
    //     getline(cin, str1);
    //     cout<<"enter string 2 "<<endl;
    //     getline(cin, str2);
    //     ifPossible(str1, str2);
    //     cout<<"do you want to quit yes/no";
    //     getline(cin, str3);
    //     if(str3 == "yes")
    //         break;
    // }
}