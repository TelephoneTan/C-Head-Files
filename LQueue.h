//
// Created by Telephone on 2019/10/20 0020.
//

#ifndef LQUEUE_LQUEUE_H
#define LQUEUE_LQUEUE_H

#include <cstdio>
#include <stdexcept>
#include <LinkedList.h>

namespace Telephone_DS::linkBase::Queue
{
    template <typename T> class Queue : protected LinkedList::LinkedList<T>
    {
    public:
        explicit Queue()    //无参数构造
                : LinkedList::LinkedList<T>()
        {}
        virtual ~Queue() = default; //析构    //调用完派生类析构函数后会隐式调用基类析构函数    //虚以派生
        Queue(Queue<T> &src)  //拷贝构造函数
                : LinkedList::LinkedList<T>(src)
        {}
        Queue<T> &operator=(Queue<T> &right)
        {
            LinkedList::LinkedList<T>::operator=(right);
            return *this;
        }
        Queue<T> &operator=(Queue<T> &&right)
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
                LinkedList::LinkedList<T>::deleteFrom(0);
            }
        }
        T front()
        {
            if(!LinkedList::LinkedList<T>::isEmpty())
            {
                return LinkedList::LinkedList<T>::at(0);
            }
            char exp[100];
            std::sprintf(exp , "[function front()] Queue is empty!");
            throw std::out_of_range(exp);
        }
        T back()
        {
            if(!LinkedList::LinkedList<T>::isEmpty())
            {
                return LinkedList::LinkedList<T>::at(LinkedList::LinkedList<T>::len() - 1);
            }
            char exp[100];
            std::sprintf(exp , "[function back()] Queue is empty!");
            throw std::out_of_range(exp);
        }
    };
}

#endif //LQUEUE_LQUEUE_H
