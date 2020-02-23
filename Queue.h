//
// Created by Telephone on 2019/10/19 0019.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include <stdexcept>
#include <cstdio>
#include <utility>
#include <ArrayStorage.h>

namespace Telephone_DS::arrayBase::Queue    //Telephone写的Queue的命名空间
{
    template <typename T> class Queue : protected ArrayStorage::ArrayStorage<T>
    {
    public:
        explicit Queue(long scale)                                      //有参数构造
                : ArrayStorage::ArrayStorage<T>::ArrayStorage(scale)
        {}
        explicit Queue()                                                //无参数构造
                : ArrayStorage::ArrayStorage<T>::ArrayStorage()
        {}
        Queue(Queue<T> const &src)                                      //拷贝构造
                : ArrayStorage::ArrayStorage<T>::ArrayStorage(src)
        {}
        Queue(Queue<T> &&right) noexcept                                //移动构造
                : ArrayStorage::ArrayStorage<T>::ArrayStorage(std::move(right))
        {}
        Queue<T> &operator=(Queue<T> const &right)                      //拷贝赋值
        {
            if(this == &right)
                return *this;
            ArrayStorage::ArrayStorage<T>::operator=(right);
            return *this;
        }
        Queue<T> &operator=(Queue<T> &&right) noexcept                  //移动赋值
        {
            ArrayStorage::ArrayStorage<T>::operator=(std::move(right));
            return *this;
        }
        virtual ~Queue() = default;                                     //析构    //虚以派生
        int isEmpty() override      //if empty , return 1(true)
        {
            return ArrayStorage::ArrayStorage<T>::isEmpty();
        }
        long len() override
        {
            return ArrayStorage::ArrayStorage<T>::len();
        }
        virtual void push(T const &x)
        {
            ArrayStorage::ArrayStorage<T>::addAfter(ArrayStorage::ArrayStorage<T>::len() - 1 , x);
        }
        virtual void push(T &&x)
        {
            ArrayStorage::ArrayStorage<T>::addAfter(ArrayStorage::ArrayStorage<T>::len() - 1 ,
                    std::move(x));
        }
        virtual int pop()           //if empty , return -1 ; or else , return 0.
        {
            if(!ArrayStorage::ArrayStorage<T>::isEmpty())
            {
                ArrayStorage::ArrayStorage<T>::deleteFrom(0 , 1);
                return 0;
            }
            return -1;
        }
        virtual T front()
        {
            if(!ArrayStorage::ArrayStorage<T>::isEmpty())
            {
                return ArrayStorage::ArrayStorage<T>::at(0);
            }
            char exp[100];
            std::sprintf(exp , "[function front()] Queue is empty!");
            throw std::out_of_range(exp);
        }
        virtual T back()
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
