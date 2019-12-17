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
        explicit Stack(long scale)  //有参数构造
                : ArrayStorage::ArrayStorage<T>(scale)
        {}
        explicit Stack()    //无参数构造
                : ArrayStorage::ArrayStorage<T>()
        {}
        virtual ~Stack() = default; //析构    //调用完派生类析构函数后会隐式调用基类析构函数    //虚以派生
        Stack(Stack<T> &src)  //拷贝构造函数
                : ArrayStorage::ArrayStorage<T>(src)
        {}
        Stack<T> &operator=(Stack<T> &right)
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
                ArrayStorage::ArrayStorage<T>::deleteFrom(ArrayStorage::ArrayStorage<T>::len() -
                                                          1);
            }
        }
        T top()
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
