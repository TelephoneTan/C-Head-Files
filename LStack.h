//
// Created by Telephone on 2019/10/20 0020.
//

#ifndef LSTACK_LSTACK_H
#define LSTACK_LSTACK_H

#include <stdexcept>
#include <utility>
#include <cstdio>
#include <LinkedList.h>

namespace Telephone_DS::linkBase::Stack    //Telephone写的Stack的命名空间
{
    template <typename T> class Stack : protected LinkedList::LinkedList<T>
    {
    public:
        explicit Stack()                                            //无参数构造
                : LinkedList::LinkedList<T>::LinkedList()
        {}
        Stack(Stack<T> const &src)                                  //拷贝构造
                : LinkedList::LinkedList<T>::LinkedList(src)
        {}
        Stack(Stack<T> &&src) noexcept                              //移动构造
                : LinkedList::LinkedList<T>::LinkedList(std::move(src))
        {}
        Stack<T> &operator=(Stack<T> const &right)                  //拷贝赋值
        {
            if(this == &right)
                return *this;
            LinkedList::LinkedList<T>::operator=(right);
            return *this;
        }
        Stack<T> &operator=(Stack<T> &&right) noexcept              //移动赋值
        {
            LinkedList::LinkedList<T>::operator=(std::move(right));
            return *this;
        }
        virtual ~Stack() = default;                                 //析构    //虚以派生
        int isEmpty() override  //if empty , return 1(true)
        {
            return LinkedList::LinkedList<T>::isEmpty();
        }
        long len() override
        {
            return LinkedList::LinkedList<T>::len();
        }
        virtual void push(T const &x)
        {
            LinkedList::LinkedList<T>::addAfter(LinkedList::LinkedList<T>::len() - 1 , x);
        }
        virtual void push(T &&x)
        {
            LinkedList::LinkedList<T>::addAfter(LinkedList::LinkedList<T>::len() - 1 ,
                    std::move(x));
        }
        virtual int pop()   //if empty , return -1 ; or else , return 0.
        {
            if(!LinkedList::LinkedList<T>::isEmpty())
            {
                LinkedList::LinkedList<T>::deleteFrom(LinkedList::LinkedList<T>::len() - 1 , 1);
                return 0;
            }
            return -1;
        }
        virtual int clear()
        {
            if(!LinkedList::LinkedList<T>::isEmpty())
            {
                LinkedList::LinkedList<T>::deleteFrom(0 , LinkedList::LinkedList<T>::len());
                return 0;
            }
            return -1;
        }
        virtual T top()
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
