#ifndef MYSTACK_H
#define MYSTACK_H

#include <string>

using namespace std;

// W³asny stos

class MyStack
{
    public:
        string toString();
        void push(int element);
        int pop();
        void ccopy(MyStack *dest);
        int getSize();
        MyStack();
        virtual ~MyStack();
        void cclear();

    protected:

    private:
        int *base=nullptr;
        int size=0;
};

#endif // MYSTACK_H

