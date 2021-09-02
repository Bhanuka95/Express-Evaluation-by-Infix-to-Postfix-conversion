#include<iostream>
#include<fstream>
#include<stack>
#include<string>

using namespace std;

bool IsOperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/')
        return true;

    else
        return false;
}
bool IsOperand(char c){
    if(c >= '0' && c <= '9')
        return true;
    else
        return false;
}

int OptrPrecedence(char c){
    int prec;
    if(c == '+' || c == '-'){
        prec = 1;
    }
    else if(c == '*' || c == '/'){
        prec = 2;
    }
    else{
        prec = -1;
    }
    return prec;
}

bool IsHigherPrecedence(char c1, char c2){
    int prec1 = OptrPrecedence(c1);
    int prec2 = OptrPrecedence(c2);

    if(prec1 == prec2){
        return true;
    }
    else if(prec1 > prec2){
        return true;
    }
    else{
        return false;
    }
}

string InfixToPostfix(string exp){
    string postfix_ans;
    stack<char> s;

    for(int i=0; i<exp.length(); i++){
        //checking for delimeters
        if(exp[i] == ' ' || exp[i] == ',' || exp[i] == '=') continue;

        else if(IsOperand(exp[i])){
            postfix_ans += exp[i];
        }

        else if(IsOperator(exp[i])){
            while(!s.empty() && s.top() != '(' && IsHigherPrecedence(s.top(), exp[i])){
                postfix_ans += s.top();
                s.pop();
            }
            s.push(exp[i]);
        }

        else if(exp[i] == '('){
            s.push(exp[i]);
        }

        else if(exp[i] == ')'){
            while(!s.empty() && s.top() != '('){
                postfix_ans += s.top();
                s.pop();
            }
            s.pop();
        }

    }

    //adding the remaining operators in stack
    while(!s.empty()){
        postfix_ans += s.top();
        s.pop();
    }

    return postfix_ans;
}

int main(){
    string exp, postfix;
    double ans;

    ifstream ReadFile("formulas.txt");
    (getline(ReadFile, exp));
        // cout << reading << "\nlength is:" << reading.length();
    postfix = InfixToPostfix(exp);
    cout << postfix << "\n\n";
        

    return 0;
}