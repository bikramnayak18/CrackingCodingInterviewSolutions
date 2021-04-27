#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'nonDivisibleSubset' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY s
 */
int outputCount = 0;
void getCombination(vector<int> input, int index, int k, unordered_map<int,int> buffer, int output, string prefix){
    int count =0;
    int remainder = -1;
    
    for(auto itr=input.begin()+index;itr!=input.end();itr++){
        count++;
        int search = *itr%k==0?0:k-(*itr%k);
        if(remainder!=-1)
            buffer[remainder]--;
        if(buffer.find(search)==buffer.end() || buffer[search]==0){
            remainder = *itr%k;
            if(buffer.find(remainder)==buffer.end())
                buffer[remainder] = 1;
            else
                buffer[remainder]++;
            
            if(outputCount<(output+1)){
                outputCount = output+1;
            }
            
            getCombination(input, index+count, k, buffer, output+1,prefix+"," + to_string(*itr));
        }
    }
}


int nonDivisibleSubset2(int k, vector<int> s) {
    unordered_map<int,int> buffer;
    getCombination(s, 0, k, buffer, 0,"");
    cout<<outputCount;
    return outputCount;
}

int nonDivisibleSubset(int k, vector<int> s) {
    unordered_map<int, int> remainders;
    for(auto i:s){
        int rem = i%k;
        if(remainders.find(rem) == remainders.end())//new
            remainders[rem] = 1;
        else
            remainders[rem]++;
    }
    int output=0;
    for(auto i=remainders.begin();i!=remainders.end();i++){
        int a = i->first;
        int b = k - a;
        if(a == b)
            output++;
        else if(a==0)
            output++;
        else if(remainders.find(b)!=remainders.end() ){
            if(i->second>remainders[b]){
                output += i->second;
                i->second = 0;
                remainders[b] = 0;
            }
            else{
                output += remainders[b];
                i->second = 0;
                remainders[b] = 0;
            }
        }else{
            output += i->second;
            i->second = 0;
        }
    }
    return output;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string s_temp_temp;
    getline(cin, s_temp_temp);

    vector<string> s_temp = split(rtrim(s_temp_temp));

    vector<int> s(n);

    for (int i = 0; i < n; i++) {
        int s_item = stoi(s_temp[i]);

        s[i] = s_item;
    }

    int result = nonDivisibleSubset(k, s);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
