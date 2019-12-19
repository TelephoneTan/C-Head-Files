//
// Created by Telephone on 2019/10/20 0020.
//

#ifndef LQUEUE_LQUEUE_H
#define LQUEUE_LQUEUE_H

#include <cstdio>
#include <utility>
#include <stdexcept>
#include <LinkedList.h>

namespace Telephone_DS::linkBase::Queue
{
    template <typename T> class Queue : protected LinkedList::LinkedList<T>
    {
    public:
        explicit Queue()                                                //无参数构造
                : LinkedList::LinkedList<T>::LinkedList()
        {}
        Queue(Queue<T> const &src)                                      //拷贝构造
                : LinkedList::LinkedList<T>::LinkedList(src)
        {}
        Queue(Queue<T> &&src) noexcept                                  //移动构造
            : LinkedList::LinkedList<T>::LinkedList(std::move(src))
        {}
        Queue<T> &operator=(Queue<T> const &right)                      //拷贝赋值
        {
            if(this == &right)
                return *this;
            LinkedList::LinkedList<T>::operator=(right);
            return *this;
        }
        Queue<T> &operator=(Queue<T> &&right) noexcept                  //移动赋值
        {
            LinkedList::LinkedList<T>::operator=(std::move(right));
            return *this;
        }
        virtual ~Queue() = default;                                     //析构   //虚以派生
        int isEmpty() override     //if empty , return 1(true)
        {
            return LinkedList::LinkedList<T>::isEmpty();
        }
        long len() override
        {
            return LinkedList::LinkedList<T>::len();
        }
        virtual void push(T &x)
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
                LinkedList::LinkedList<T>::deleteFrom(0 , 1);
                return 0;
            }
            return -1;
        }
        virtual T front()
        {
            if(!LinkedList::LinkedList<T>::isEmpty())
            {
                return LinkedList::LinkedList<T>::at(0);
            }
            char exp[100];
            std::sprintf(exp , "[function front()] Queue is empty!");
            throw std::out_of_range(exp);
        }
        virtual T back()
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
