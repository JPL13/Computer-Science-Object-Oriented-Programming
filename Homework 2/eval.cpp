//
//  eval.cpp
//  Homework 2
//
//  Created by Juan Piao on 2/2/18.
//  Copyright © 2018 Piao. All rights reserved.
//
#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;
//function declaration
int evaluate(string infix, const Map& values, string& postfix, int& result);
void convertInfixToPostfix(string infix, string& postfix);
int precedence(char ch);
bool evaluatePostfix(string postfix, const Map& values, bool& divideByZero, int&answer);
void removeSpaces(string& in);
bool infixValid(string infix);
bool contained(string infix, const Map& values);


//************************//
//function implementation //
//************************//
bool contained(string infix, const Map& values)
{
    for (int i=0; i<infix.size(); i++)
    {
        if (islower(infix[i]) && !values.contains(infix[i]))
        {
            return false;
        }
    }
    return true;
}


bool infixValid(string infix)
{
  
    removeSpaces(infix);
   
    for (int i=0; i<infix.size(); i++)
    {
        char ch=infix[i];
        if ((islower(ch)||ch=='+'||ch=='-'||ch=='/'||ch=='*'||isspace(ch))||ch=='('||ch==')')
        {
           // st.push(ch);
           
            
        }
        else
            return false;
    }
    
    return true;
   
}

int precedence(char ch)
{
    if(ch=='*'||ch=='/')
        return 3;
    if(ch=='+'||ch=='-')
        return 2;
    else
        return 0;
        
}

int evaluate(string infix, const Map& values, string& postfix, int& result)

{
   
    //     removeSpaces(infix);
   
        //int value;//to store the integer value that matches the character
        bool divideByZero=false;
    
       if(infixValid(infix)&&infix!="")
       {
           
           if(!contained(infix, values))
           {
              convertInfixToPostfix(infix, postfix);
               
               return 2;
           }
       
           convertInfixToPostfix(infix, postfix);
           
           evaluatePostfix(postfix, values,divideByZero, result);
           
           if(divideByZero)
               return 3;
        
          
           if(evaluatePostfix(postfix, values,divideByZero, result))
           
               return 0;
        
        }
return 1;

}

void convertInfixToPostfix(string infix, string& postfix)
{
    string postfixExp=""; //Initialize postfix to empty
    stack<char> aStack;
    
    for(int i=0; i<infix.size();i++)
    {
        char ch=infix[i];
 
            if( ch>='a'&&ch<='z')
               postfixExp=postfixExp+ch;
        
            if(ch== '(')
            {  aStack.push(ch);}
        
            if(ch==')')
            {   while(aStack.top()!='(')
                {
                    postfixExp=postfixExp+aStack.top();
                    aStack.pop();
                }//end while
                aStack.pop(); //remove the open parenthesis
            }
                //process stack operators of greater precedence
            if(ch== '+'||ch=='-'||ch== '*'||ch=='/')
            {
                while(!aStack.empty()&&aStack.top()!='('&&precedence(ch)<=precedence(aStack.top()))
                {
                    postfixExp=postfixExp+aStack.top();
                    aStack.pop();
                }//end while
                
                aStack.push(ch); //save new operator
            }
        
    }//end for
    
    //append to postfixExp the operators remaining in the stack
    while(!aStack.empty())
    {
        postfixExp=postfixExp+aStack.top();
        aStack.pop();
    }//end while
    
    postfix=postfixExp;
    
}


bool evaluatePostfix(string postfix, const Map& values, bool& divideByZero, int& answer)
{
    
    
    stack<int> aStack;
     int value;
    
    for(int i=0; i<postfix.size();i++)
    {
       
        char ch=postfix[i];
        if(islower(ch)) //if ch is an operand
          {
              values.get(ch, value);
              aStack.push(value);
          }
        else           // ch is a binary operator
        {
            int operand2, operand1;
            
            if(aStack.empty())
                return false;
            
             operand2=aStack.top();
                aStack.pop();
                if(aStack.empty())
                    return false;
               { operand1=aStack.top();
                 aStack.pop();
            
               }
            
            
            if(ch=='+')
            {
                value=operand1+operand2; aStack.push(value);
            }
            if(ch=='-')
            {
                value=operand1-operand2; aStack.push(value);
            }
            if(ch=='*')
            {
                value=operand1*operand2; aStack.push(value);
            }
            if(ch=='/')
            {
                if(operand2!=0)
                {value=operand1/operand2;
                    aStack.push(value);}
                else
                {
                    divideByZero=true;
                }
            }
         
           
         }//end of else
        
       
    }//end of for loop
    
    if(aStack.empty()||aStack.size()>1)
        return false;
     else
     {answer=aStack.top();
         return true;}
}

void removeSpaces(string& in)
{
    string temp;
    for(int i = 0; i < in.size(); i++)
    {
        if(in[i] != ' ')
        {
            temp += in[i];
        }
    }
    in = temp;
}

