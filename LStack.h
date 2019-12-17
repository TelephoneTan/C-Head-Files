//
// Created by Telephone on 2019/10/20 0020.
//

#ifndef LSTACK_LSTACK_H
#define LSTACK_LSTACK_H

#include <stdexcept>
#include <cstdio>
#include <LinkedList.h>

namespace Telephone_DS::linkBase::Stack    //Telephone写的Stack的命名空间
{
    template <typename T> class Stack : protected LinkedList::LinkedList<T>
    {
    public:
        explicit Stack()    //无参数构造
                : LinkedList::LinkedList<T>()
        {}
        virtual ~Stack() = default; //析构    //调用完派生类析构函数后会隐式调用基类析构函数    //虚以派生
        Stack(Stack<T> &src)  //拷贝构造函数
                : LinkedList::LinkedList<T>(src)
        {}
        Stack<T> &operator=(Stack<T> &right)
        {
            LinkedList::LinkedList<T>::operator=(right);
            return *this;
        }
        int isEmpty() override
        {
            return LinkedList::LinkedList<T>::isEmpty();
        }
        long len() override
        {
            return LinkedList::LinkedList<T>::len();
        }
        void push(T x)
        {
            LinkedList::LinkedList<T>::addAfter(LinkedList::LinkedList<T>::len() - 1 , x);
        }
        void pop()
        {
            if(!LinkedList::LinkedList<T>::isEmpty())
            {
                LinkedList::LinkedList<T>::deleteFrom(LinkedList::LinkedList<T>::len() - 1);
            }
        }
        T top()
        {
            if(!LinkedList::LinkedList<T>::isEmpty())
            {
                return LinkedList::LinkedList<T>::at(LinkedList::LinkedList<T>::len() - 1);
            }
            char exp[100];
            std::sprintf(exp , "[function top()] Stack is empty!");
            throw std::out_of_range(exp);
        }
    };
}

#endif //LSTACK_LSTACK_H
