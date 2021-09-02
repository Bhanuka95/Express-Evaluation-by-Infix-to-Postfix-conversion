#include<iostream>
#include<fstream>
#include<stack>
#include<string>

using namespace std;

bool IsOperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/')
        return true;

    
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

double Calculation(char optr, int operand1, int operand2){
    cout << "Calculation is called!!\n";
    double ans;
    switch(optr){
        case '+':
            ans = operand1 + operand2;
            break;
        case '-':
            ans = operand1 - operand2;
            break;
        case '*':
            ans = operand1*operand2;
            break;
        case '/':
            ans = operand1/operand2;
            break;
    }
    return ans;
}

int getIntOperand(char c){
    switch(c){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }
}

string InfixToPostfix(string exp){
    cout << "InfixToPostfix is called!!\n";
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

double CalculatePostfix(string postfix){
    cout << "CalculatePostfix is called!!\n";
    
    stack<double> s;
    for(int i=0; i<postfix.length(); i++){
        //ignore delimiters
        if(postfix[i] == ' ' || postfix[i] == ',' || postfix[i] == '=') continue;

        else if(IsOperand(postfix[i]) && postfix[i] - '0' >= 0){
			int operand = getIntOperand(postfix[i]);
			
			s.push(operand);
		}

        else if(IsOperator(postfix[i])){
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();
            double answer = Calculation(postfix[i], operand1, operand2);
            s.push(answer);
            cout << "calculate another\n";

        }
    }
    return s.top();
}

int main(){
    string exp, postfix;
    double result;

    ifstream ReadFile("formulas.txt");
    (getline(ReadFile, exp));
        // cout << reading << "\nlength is:" << reading.length();
    postfix = InfixToPostfix(exp);
    cout << postfix << "\n";
    result = CalculatePostfix(postfix);
    cout << "The answer is: " << result << "\n\n";
        

    return 0;
}