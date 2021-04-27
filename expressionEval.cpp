#include <iostream> 
#include<vector>
#include<stack>
using namespace std; 
 enum Operator{
        ADD, SUBTRACT, MULTIPLY, DIVIDE, BLANK
    } ;
class Term{
    public:
   
    double value=0;
    Operator op = BLANK;
    
    Term(double value, Operator op){
        this->value = value;
        this->op = op;
    }

    Operator getOperator(){
        return this->op;
    }

    double getValue(){
        return this->value;
    }

    void setValue(double value){
        this->value = value;
    }

    
};
double calculate(double left, Operator op, double right){
        if(op == ADD) return left + right;
        else if (op == SUBTRACT) return left - right;
        else if (op == MULTIPLY) return left * right;
        else if (op == DIVIDE) return left/right;
        else return right;
    }

Term* collapse(Term* primary , Term* secondary){
        if(primary == NULL) return secondary;
        if(secondary == NULL) return primary;
        double value = calculate(primary->value, secondary->op, secondary->value);
        primary->value = value;
        return primary;
    }

vector<Term> getTerms(string sequence){
        //THIS FUNCTION SHOULD USE THE INPUT SEQUENCE TO GENERATE LIST OF TERMS INSTEAD OF HARDCODING VALUES...
        vector<Term> output;
        output.push_back(Term(2, ADD));
        output.push_back(Term(6, SUBTRACT));
        output.push_back(Term(7, SUBTRACT));
        output.push_back(Term(8, MULTIPLY));
        //output.push_back(Term(2, DIVIDE));
        output.push_back(Term(5, ADD));
        return output;
    }

double eval(string expression){
    vector<Term> terms = getTerms(expression);
    if(terms.size()==0) return INT_MIN;
    double result ;
    Term* processing = NULL;
    for(int i=0;i<terms.size();i++){
        Term* current = &terms[i];
        Term* next = i>=terms.size()? NULL:&terms[i+1];
        processing = collapse(processing, current);
        if(next == NULL || next->op == ADD || next->op == SUBTRACT)
        {
            result = calculate(result, processing->op, processing->value);
            processing = NULL;
        }
    }
    return result;
}


class Evaluate{
    int getPriority(Operator op){
        if(op == ADD) return 1;
        else if (op == SUBTRACT) return 1;
        else if (op == MULTIPLY) return 2;
        else if (op == DIVIDE) return 2;
        else return 0;
    }

    double calculate(double left, Operator op, double right){
        if(op == ADD) return left + right;
        else if (op == SUBTRACT) return left - right;
        else if (op == MULTIPLY) return left * right;
        else if (op == DIVIDE) return left/right;
        else return right;
    }

    string removeSpaces(string expression){
        string output;
        for(int i=0;i<expression.length();i++)
        {
            if( expression[i] != ' ')
                output += expression[i];
        }
        return output;
    }

    bool isDigit(char c){
        int x = (int) c;
        if(x>=48 && x<=57)
            return true;
        else 
            return false;
    }

    int findNextNumber(string input ,int offset){
        string temp ="";
        while(offset<input.length() && isdigit(input[offset])){
            temp += input[offset];
            offset++;
        }
        return stoi(temp);
    }

    Operator findNextOperator(string input, int offset){
        if(offset< input.length()){
            if(input[offset]=='+') return ADD;
            if(input[offset]=='-') return SUBTRACT;
            if(input[offset]=='*') return MULTIPLY;
            if(input[offset]=='/') return DIVIDE;
        }
        return BLANK;
    }

    void collapse(Operator curr, stack<double> &number, stack<Operator> &op){
        while(number.size()>1 && op.size()>0){
            if(getPriority(curr) <= getPriority(op.top())){
                double b = number.top();
                number.pop();
                double a = number.top();
                number.pop();
                Operator currOp = op.top();
                op.pop();
                double result = calculate(a, currOp, b);
                number.push(result);
            }else
                break;
        }
    }
    public:
    double eval(string expression){
        expression = removeSpaces(expression);
        stack<double> numbers;
        stack<Operator> ops;
        for(int i=0;i<expression.length();i++){
            int value = findNextNumber(expression, i);
            i += to_string(value).length();
            numbers.push(value);

            if(i+1>=expression.length())
                break;

            Operator op = findNextOperator(expression, i);
            collapse(op, numbers, ops);
            ops.push(op);
        }
        collapse(BLANK, numbers, ops);
        if(numbers.size()==1 && ops.size()==0)
            return numbers.top();
        return 0;
    }
};

int main(){
    Evaluate evalObj;
    cout<<"result from eval class : "<<evalObj.eval("2 - 6 - 7 * 8  + 5")<<endl;
}