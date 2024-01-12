#include<iostream>
#include<stdio.h>
#include<string>
#include<stack>
#include<vector>
#include<cctype>
#include<unordered_set>

using namespace std;

bool isOperator(const std::string& str) {
    // Set of some common operators, haven't considered unary operators until now
    if(str!="+" && str!="-" && str!="*" && str!="/" && str!="!=" && str!="==" && str!="<" && str!=">" && str!="^" && str!="|" && str!="%")
        return false;
    return true;
}

int find_value(string &oper , vector<string>&operands_pair)
{
    //cout<<operands_pair[0]<<" "<<operands_pair[1]<<endl;
    int a=stoi(operands_pair[0]),b=stoi(operands_pair[1]);

    //for subtraction and division which is order dependent, since we reverse the order that's why we use reverse of reverse for original order
    if(oper=="*")
        return a*b;
    else if(oper=="/")
        return a/b;
    else if(oper=="+")
        return a+b;
    else if(oper=="-")
        return a-b;
    else if(oper=="!=")
        return a!=b;
    else if(oper=="==")
        return a==b;
    else if(oper=="<")
        return a<b;
    else if(oper == ">")
        return a>b;
    else if(oper =="^")
        return a^b;
    else if(oper =="|")
        return a|b;
    else
        return b%a;
}

void calculate(vector<string>&expression, int &flag)
{
    // if it's a blank bracket, the case can come when the user has alread plugged in brackets at the start and the end
    if(expression.size()==0) return;

    int operator_cnt=0, operands_cnt=0;
    string op_string;
    vector<string>operands_pair;
    while(!(expression.size()==1 && operands_pair.size()==0))
    {
        if(isOperator(expression[expression.size()-1]))
        {
            op_string=expression[expression.size()-1];
            operator_cnt++;
            expression.pop_back();
        }
        else 
        {
            operands_pair.push_back(expression[expression.size()-1]);
            operands_cnt++;
            expression.pop_back();
        }  

        //cout<<operands_cnt<<" "<<operator_cnt<<"\n";  
        if(operator_cnt>0 && operands_cnt==0)
        {
            flag=1;
            return;
        }
        else if(operator_cnt==0 && operands_cnt>1)
        {
            flag=1;
            return;
        }
        else if(operator_cnt==1 && operands_cnt==2)
        {
            int val = find_value(op_string, operands_pair);
            operands_pair.clear();
            expression.push_back(to_string(val));
            operator_cnt=0;
            operands_cnt=0;
        }
    }
}
int main()
{
    cout<<"Enter expression\n";

    //line to take user input
    string line;
    getline(cin,line);

    //used here to store the elements and strings
    vector<string>elements;

    //initialise count to iterate through the characters in line
    int cnt=0;
    while(cnt<line.size())
    {
        if(line[cnt]==' ')
        {
            cnt++;
            continue;
        }
        if(line[cnt]=='(' || line[cnt]==')')
        {
            string temp="";
            temp.push_back(line[cnt]);
            elements.push_back(temp);
            cnt++;
        }
        else if (isdigit(line[cnt]))
        {
            string temp;
            while(cnt<line.size() && isdigit(line[cnt]))
            {
                temp+=line[cnt];
                cnt++;
            }
            elements.push_back(temp);
        }
        else
        {
            string temp;
            temp.push_back(line[cnt]);
            if(line[cnt]=='!' || line[cnt]=='=')
            {
                if(cnt+1<line.size() && line[cnt+1]=='=')
                {
                    temp.push_back(line[cnt+1]);
                    cnt++;
                }
            }
            if(!isOperator(temp))
                cout<<"'"<<temp<<"'"<<" is an invalid expression, please recheck!\n";
            else
                elements.push_back(temp);
            cnt++;
        }
    }


    stack<string>buff;
    
    //for stack based approach, checking explicitly if the start of the expression has '('
    elements.insert(elements.begin(),"(");
    elements.push_back(")");

    //intitiate counter
    
    cnt=0;
    while(cnt<elements.size())
    {
        //cout<<buff.size()<<endl;
        if(elements[cnt]==")")
        {            
            vector<string>current_expression;
            while(!buff.empty() && buff.top()!="(")
            {
                current_expression.push_back(buff.top());
                buff.pop();
            }
            if(buff.empty())
            {
                cout<<"invalid expression, missing paranthesis\n";
                return 1;
            }

            //checking if the current expression is valid or not (only for binary expression)
            int flag=0;
            calculate(current_expression,flag);

            if(flag==1)
            {
                cout<<"invalid expression, please check!\n";
                return 1;
            }

            buff.pop();
            buff.push(current_expression[0]);
        }
        else
            buff.push(elements[cnt]);
        cnt++;
    }

    cout<<buff.top()<<"\n";
}