//
// Created by Telephone on 2019/10/20 0020.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <stdexcept>
#include <cstdio>
#include <ArrayStorage.h>

namespace Telephone_DS::arrayBase::Stack    //Telephone写的Stack的命名空间
{
    template <typename T> class Stack : protected ArrayStorage::ArrayStorage<T>
    {
    public:
        explicit Stack(long scale)                                  //有参数构造
                : ArrayStorage::ArrayStorage<T>::ArrayStorage(scale)
        {}
        explicit Stack()                                            //无参数构造
                : ArrayStorage::ArrayStorage<T>::ArrayStorage()
        {}
        Stack(Stack<T> const &src)                                  //拷贝构造
        {
            if(this == &src)
                return;
            ArrayStorage::ArrayStorage<T>::ArrayStorage(src);
        }
        Stack(Stack<T> &&src) noexcept                              //移动构造
                : ArrayStorage::ArrayStorage<T>::ArrayStorage(std::move(src))
        {}
        Stack<T> &operator=(Stack<T> const &right)                  //拷贝赋值
        {
            if(this == &right)
                return *this;
            ArrayStorage::ArrayStorage<T>::operator=(right);
            return *this;
        }
        Stack<T> &operator=(Stack<T> &&right) noexcept              //移动赋值
        {
            ArrayStorage::ArrayStorage<T>::operator=(std::move(right));
            return *this;
        }
        virtual ~Stack() = default;                                 //析构    //虚以派生
        int isEmpty() override  //if empty , return 1(true)
        {
            return ArrayStorage::ArrayStorage<T>::isEmpty();
        }
        long len() override
        {
            return ArrayStorage::ArrayStorage<T>::len();
        }
        virtual void push(T x)
        {
            ArrayStorage::ArrayStorage<T>::addAfter(ArrayStorage::ArrayStorage<T>::len() - 1 , x);
        }
        virtual int pop()       //if empty , return -1 ; or else , return 0.
        {
            if(!ArrayStorage::ArrayStorage<T>::isEmpty())
            {
                ArrayStorage::ArrayStorage<T>::deleteFrom(ArrayStorage::ArrayStorage<T>::len() -
                                                          1 , 1);
                return 0;
            }
            return -1;
        }
        virtual T top()
        {
            if(!ArrayStorage::ArrayStorage<T>::isEmpty())
            {
                return ArrayStorage::ArrayStorage<T>::at(ArrayStorage::ArrayStorage<T>::len() - 1);
            }
            char exp[100];
            std::sprintf(exp , "[function top()] Stack is empty!");
            throw std::out_of_range(exp);
        }
    };
}

#endif //STACK_STACK_H
