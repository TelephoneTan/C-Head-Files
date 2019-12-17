//
// Created by Telephone on 2019/10/19 0019.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include <stdexcept>
#include <cstdio>
#include <ArrayStorage.h>

namespace Telephone_DS::arrayBase::Queue    //Telephone写的Queue的命名空间
{
    template <typename T> class Queue : protected ArrayStorage::ArrayStorage<T>
    {
    public:
        explicit Queue(long scale)  //有参数构造
                : ArrayStorage::ArrayStorage<T>(scale)
        {}
        explicit Queue()    //无参数构造
                : ArrayStorage::ArrayStorage<T>()
        {}
        virtual ~Queue() = default; //析构    //调用完派生类析构函数后会隐式调用基类析构函数    //虚以派生
        Queue(Queue<T> &src)  //拷贝构造函数
                : ArrayStorage::ArrayStorage<T>(src)
        {}
        Queue<T> &operator=(Queue<T> &right)
        {
            ArrayStorage::ArrayStorage<T>::operator=(right);
            return *this;
        }
        int isEmpty() override
        {
            return ArrayStorage::ArrayStorage<T>::isEmpty();
        }
        long len() override
        {
            return ArrayStorage::ArrayStorage<T>::len();
        }
        void push(T x)
        {
            ArrayStorage::ArrayStorage<T>::addAfter(ArrayStorage::ArrayStorage<T>::len() - 1 , x);
        }
        void pop()
        {
            if(!ArrayStorage::ArrayStorage<T>::isEmpty())
            {
                ArrayStorage::ArrayStorage<T>::deleteFrom(0);
            }
        }
        T front()
        {
            if(!ArrayStorage::ArrayStorage<T>::isEmpty())
            {
                return ArrayStorage::ArrayStorage<T>::at(0);
            }
            char exp[100];
            std::sprintf(exp , "[function front()] Queue is empty!");
            throw std::out_of_range(exp);
        }
        T back()
        {
            if(!ArrayStorage::ArrayStorage<T>::isEmpty())
            {
                return ArrayStorage::ArrayStorage<T>::at(ArrayStorage::ArrayStorage<T>::len() - 1);
            }
            char exp[100];
            std::sprintf(exp , "[function back()] Queue is empty!");
            throw std::out_of_range(exp);
        }
    };
}

#endif //QUEUE_QUEUE_H
