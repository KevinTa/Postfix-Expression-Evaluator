#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>

using namespace std;

class Stack{
private:
    double *_data;
    int _top;
    int _max;
    int _count;
public:
    Stack(int max);
    ~Stack();
    void push(double n);
    double pop();
    double top();
    void showStack();
    Stack(const Stack &);
    Stack & operator= (const Stack &);
    double eval(string);
    void resetStack();

};

int main()
{
    string input;
    for(;;)
    {
        cout<<"Enter postfix expression. To exit program enter ! in your input."<<endl;
        getline(cin, input);
        for(int l = 0; l<input.length();l++)
        {
            if(input[l] == '!')
            {
                return 0;
            }
        }
        Stack s(input.length()-1);
        cout<<"result: "<<s.eval(input)<<endl;
        s.~Stack();
        s.resetStack();
    }
}
//main to test the functions.
Stack::Stack(int max)
{
    _max = max;
    _data = new double[max];
    _top = -1;
    _count = 0;
}
//initializes _top, _max, _count, and _data.

Stack::~Stack()
{
    if(_top!=-1)
    {
        delete [] _data;
    }
}

Stack::Stack(const Stack& rhs)
{
    *this = rhs;
}
//copy constructor

Stack & Stack::operator= (const Stack & rhs)
{
    _top=rhs._top;
    while(_count != rhs._count)
    {
        _data[_count]=rhs._data[_count];
        _count++;
    }
    return *this;
}
//operator to return *this.

void Stack::resetStack(){
    _top = -1;
    _count = 0;
}
//function to return stack to initial state to enter in more inputs.

void Stack::push(double n)
{
    if(_count<_max)
    {
        _top = _top + 1;
        _data[_top] = n;
        _count++;
    }
}
//inserts a new double into the current _top position in the data array then increments the _top value and _count forward.

double Stack::pop()
{
    double tmp;
    if(_count>=0)
    {
        tmp = _data[_top];
       _top = _top - 1;
       _count--;
    }
    return tmp;

}
//In the case that Stack is not empty,removes value at the top of Stack, then deincrements _top.

void Stack::showStack()
{
    if(_top>=0)
    {
        for(int i = 0; i<=_top; i++)
        {
            cout <<"Stack: "<< _data[i]<<endl;
        }
    }
}

//displays all values in Stack.

double Stack::top()
{
    return _data[_top];
}

/*double Stack::eval(string expn)
{
    string str;
    double operand1, operand2, result;
    char ptr[10];
    for (int i =0; i<10; i++)
            ptr[i]='0';
    int k=0;
    int tmpcount = 1;
    int j;
    do
    {
        if(isdigit(expn[k]))
        {
            j = k;
            while(!isspace(expn[k+1]) && expn[k+1] !='+' && expn[k+1] !='-' && expn[k+1] !='*' && expn[k+1] !='/' )
            {
                tmpcount++;
                k++;
            }
            str = expn.substr(j,tmpcount);
            strcpy(ptr,str.c_str());
            push(atof(ptr));

        }
        else
        {
            operand2 = pop();
            operand1 = pop();
            switch(expn[k])
            {
            case '+': result = operand1 + operand2;
                push(result);
                break;
            case '-': result = operand1 - operand2;
                push(result);
                break;
            case '*': result = operand1 * operand2;
                push(result);
                break;
            case '/': result = operand1/operand2;
                push(result);
                break;
            }
        }
        k++;
    }while(k<str.length());
    result = pop();
    return result;

}*/
//attempted to use pseudocode from textbook to implement using a do-while loop. Did not work so used a for loop instead.
double Stack::eval(string expn)
{
    string str;
    double operand1,operand2;
    double result = 0;
    char ptr[10];
    for (int i =0; i<10; i++)
        ptr[i]='0';
    int tmpcount = 1;
    int j;
    for(int k = 0; k<expn.length(); k++)
    {

        if(isspace(expn[k]))
            continue;
        if (isdigit(expn[k]))
        {
            tmpcount = 1;
            j = k;
            while(!isspace(expn[k+1]) && expn[k+1] !='+' && expn[k+1] !='-' && expn[k+1] !='*' && expn[k+1] !='/' )
            {
                tmpcount++;
                k++;
            }
            str = expn.substr(j,tmpcount);
            strcpy(ptr,str.c_str());
            push(atof(ptr));
            //The while loop accounts for the possible points in a decimal by starting from a digit to a blank space, then copying it to a string.
            //Afterwards, the number contained in the string is converted to a double then pushed into the stack.
        }
        else
        {
            operand2 = pop();
            operand1 = pop();
            switch(expn[k])
            {
            case '+': result = operand1+operand2;
                push (result);
                break;
            case '-': result = operand1-operand2;
                push (result);
                break;
            case '*': result = (double)operand1 * operand2;
                push (result);
                break;
            case '/': result = (double)operand1/operand2;
                push (result);
                break;
             // Two numbers are popped from the stack.
            //Then result is based on the case in the input and pushed back into the stack.
            }
         }
    }
    result = pop();
    return result;
}
//The lab assignment was the same as this, so I figured it was fair game to use it in this problem.


