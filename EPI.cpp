#include<iostream>
#include<bits/stdc++.h>
#include<stack>
using namespace std;

int evalRPN(const string& expression){

    stack<int> result;
    stringstream ss(expression);
    string token;
    const char delimeter = ',';
    while(getline(ss, token, delimeter)){
        if(token == "+" || token =="-" || token =="*" || token =="/"){
            int b = result.top();
            result.pop();
            int a = result.top();
            result.pop();
            switch (token.front())
            {
            case '+':
                result.emplace(a + b);
                break;
            
            case '-':
                result.emplace(a - b);
                break;

            case '*':
                result.emplace(a * b);
                break;

            case '/':
                result.emplace(a / b);
                break;                                
            }
        }
        else{
            result.emplace(stoi(token));
        }
    }
    return result.top();
}

int main(){
    cout<<evalRPN("5,10,+,2,*,10,-");
}