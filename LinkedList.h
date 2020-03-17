//
// Created by Telephone on 2019/10/20 0020.
//

/// @file LinkedList.h

#ifndef POLYNOMIAL_LINKEDLIST_H
#define POLYNOMIAL_LINKEDLIST_H

#include <cstdlib>
#include <cstdio>
#include <stdexcept>

#include "telephone_ds_define.h"

namespace Telephone_DS::linkBase::LinkedList
{
    template <typename T> class LinkedList
    {   /* Do not create a LinkedList of reference type*/
    private:
        long length = 0L;   //链表当前元素个数
        long index = -1L;    //now指针当前指示的结点的序号
        struct Node
        {
            T data;
            Node* before;
            Node* next;
        }*now = nullptr;              //now指针
    public:
        explicit LinkedList() = default;                            //构造函数
        LinkedList(LinkedList<T>& src)                        //拷贝构造函数，不应改变被复制对象
        {
            if (this == &src)
                return;
            if (src.length == 0)
            {
                length = 0;
                now = nullptr;
                index = -1;
            }
            else
            {
                length = src.length;
                Node* beforeNode = nullptr;
                Node* zeroNode = nullptr;
                Node* tailNode = nullptr;
                for (long i = 0; i < src.length; ++i)
                {
                    Node* newNode = (Node*)std::malloc(sizeof(Node));
                    if (!newNode)
                    {
                        throw std::bad_alloc();
                    }
                    newNode->next = newNode->before = nullptr;
                    newNode->data = src.at(i);
                    if (beforeNode != nullptr)
                    {
                        beforeNode->next = newNode;
                        newNode->before = beforeNode;
                        newNode->next = nullptr;
                    }
                    else
                    {
                        zeroNode = newNode; //记录0号结点地址

                        newNode->before = nullptr;
                        newNode->next = nullptr;
                    }
                    if (i == src.length - 1)
                    {
                        tailNode = newNode; //记录尾结点地址
                    }
                    beforeNode = newNode;
                }
                if (!tailNode)throw std::exception("access member using NULL pointer");
                tailNode->next = zeroNode;
                if (!zeroNode)throw std::exception("access member using NULL pointer");
                zeroNode->before = tailNode;
                index = 0;
                now = zeroNode;
            }
        }
        LinkedList(LinkedList<T>&& src) noexcept                    //移动构造
        {
            if (this == &src)
                return;
            length = src.length;
            index = src.index;
            now = src.now;
            src.length = 0;
            src.index = -1;
            src.now = nullptr;
        }
        LinkedList<T>& operator=(LinkedList<T> const& right)        //拷贝赋值函数，不应改变被复制对象
        {
            if (this != &right)
            {
                /******释放******/
                Node* needFree = now;
                //如果需要释放结点,那么释放的第一个结点是now结点
                //如果不需要释放结点,那么now结点为nullptr
                for (long i = 0; i < length; ++i)//次数控制:次数与长度相等
                {
                    Node* temp = needFree->next;
                    std::free(needFree);//此处会出现野指针,但可以保证不会再使用野指针进行访问或操作内存
                    needFree = temp;
                    //推进
                }
                needFree = nullptr;
                /******释放******/

                /******重置******/
                length = 0;
                index = -1;
                now = nullptr;
                /******重置******/

                /*赋值与内存拷贝*/
                if (right.length == 0)
                {
                    length = 0;
                    now = nullptr;
                    index = -1;
                }
                else
                {
                    length = right.length;
                    Node* beforeNode = nullptr;
                    Node* zeroNode = nullptr;
                    Node* tailNode = nullptr;
                    for (long i = 0; i < right.length; ++i)
                    {
                        Node* newNode = (Node*)std::malloc(sizeof(Node));
                        if (!newNode)throw std::bad_alloc();
                        newNode->next = newNode->before = nullptr;
                        newNode->data = right.at(i);
                        if (beforeNode != nullptr)
                        {
                            beforeNode->next = newNode;
                            newNode->before = beforeNode;
                            newNode->next = nullptr;
                        }
                        else
                        {
                            zeroNode = newNode; //记录0号结点地址

                            newNode->before = nullptr;
                            newNode->next = nullptr;
                        }
                        if (i == right.length - 1)
                        {
                            tailNode = newNode; //记录尾结点地址
                        }
                        beforeNode = newNode;
                    }
                    tailNode->next = zeroNode;
                    zeroNode->before = tailNode;
                    index = 0;
                    now = zeroNode;
                }
                /*赋值与内存拷贝*/
            }
            return *this;
        }
        LinkedList<T>& operator=(LinkedList<T>&& right) noexcept    //移动赋值
        {
            if (this != &right)
            {
                /******释放******/
                Node* needFree = now;
                //如果需要释放结点,那么释放的第一个结点是now结点
                //如果不需要释放结点,那么now结点为nullptr
                for (long i = 0; i < length; ++i)//次数控制:次数与长度相等
                {
                    Node* temp = needFree->next;
                    std::free(needFree);//此处会出现野指针,但可以保证不会再使用野指针进行访问或操作内存
                    needFree = temp;
                    //推进
                }
                needFree = nullptr;
                /******释放******/

                /******重置******/
                length = 0;
                index = -1;
                now = nullptr;
                /******重置******/

                /*赋值与内存窃取*/
                if (right.length == 0)
                {
                    length = 0;
                    now = nullptr;
                    index = -1;
                }
                else
                {
                    length = right.length;
                    index = right.index;
                    now = right.now;
                    right.length = 0;
                    right.index = -1;
                    right.now = nullptr;
                }
                /*赋值与内存窃取*/
            }
            return *this;
        }
        virtual ~LinkedList()                                       //析构    //虚以派生
        {//1.递推地释放链式数据 2.链表属性重置
            Node* needFree = now;
            //如果需要释放结点,那么释放的第一个结点是now结点
            //如果不需要释放结点,那么now结点为nullptr
            for (long i = 0; i < length; ++i)//次数控制:次数与长度相等
            {
                Node* temp = needFree->next;
                std::free(needFree);//此处会出现野指针,但可以保证不会再使用野指针进行访问或操作内存
                needFree = temp;
                //推进
            }
            needFree = nullptr;
            length = 0;
            index = -1;
            now = nullptr;
        }
        virtual int addBefore(long Index, T const& x)
        {
            if (Index >= 0 && Index < length)
            {//如果序号合法
                if (Index == index)
                    ;
                else if (Index < index)
                {
                    long dis = index - Index;//往前走(按before走)的距离
                    if ((double)dis > length / (double)2)
                    {//按next走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                else if (Index > index)
                {
                    long dis = Index - index;//往后走(按next走)的距离
                    if ((double)dis < length / (double)2)
                    {//按next走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                Node* newBefore = now->before;
                Node* newNext = now;
                Node* newNode = (Node*)std::malloc(sizeof(Node));
                if (!newNode)
                {
                    throw std::bad_alloc();
                }
                newNode->next = newNode->before = nullptr;
                newNode->data = x;
                newNode->next = newNext;
                newNode->before = newBefore;
                newBefore->next = newNext->before = newNode;
                index++;
                length++;
                return 0;
            }
            else if (length == 0)
            {//或序号不合法但是当前长度为0
                now = (Node*)std::malloc(sizeof(Node));
                if (!now)
                {
                    throw std::bad_alloc();
                }
                now->before = now->next = nullptr;
                index = 0;
                length++;
                now->data = x;
                now->next = now;
                now->before = now;
                return 0;
            }
            return TELEPHONE_DS_BAD_INDEX;
        }
        virtual int addBefore(long Index, T&& x)
        {
            if (Index >= 0 && Index < length)
            {//如果序号合法
                if (Index == index)
                    ;
                else if (Index < index)
                {
                    long dis = index - Index;//往前走(按before走)的距离
                    if ((double)dis > length / (double)2)
                    {//按next走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                else if (Index > index)
                {
                    long dis = Index - index;//往后走(按next走)的距离
                    if ((double)dis < length / (double)2)
                    {//按next走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                Node* newBefore = now->before;
                Node* newNext = now;
                Node* newNode = (Node*)std::malloc(sizeof(Node));
                if (!newNode)
                {
                    throw std::bad_alloc();
                }
                newNode->next = newNode->before = nullptr;
                newNode->data = std::move(x);
                newNode->next = newNext;
                newNode->before = newBefore;
                newBefore->next = newNext->before = newNode;
                index++;
                length++;
                return 0;
            }
            else if (length == 0)
            {//或序号不合法但是当前长度为0
                now = (Node*)std::malloc(sizeof(Node));
                if (!now)
                {
                    throw std::bad_alloc();
                }
                now->before = now->next = nullptr;
                index = 0;
                length++;
                now->data = std::move(x);
                now->next = now;
                now->before = now;
                return 0;
            }
            return TELEPHONE_DS_BAD_INDEX;
            return 0;
        }
        virtual int addAfter(long Index, T const& x)
        {
            if (Index >= 0 && Index < length)
            {//如果序号合法
                if (Index == index)
                    ;
                else if (Index < index)
                {
                    long dis = index - Index;//往前走(按before走)的距离
                    if ((double)dis > length / (double)2)
                    {//按next走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                else if (Index > index)
                {
                    long dis = Index - index;//往后走(按next走)的距离
                    if ((double)dis < length / (double)2)
                    {//按next走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                Node* newBefore = now;
                Node* newNext = now->next;
                Node* newNode = (Node*)std::malloc(sizeof(Node));
                if (!newNode)
                {
                    throw std::bad_alloc();
                }
                newNode->next = newNode->before = nullptr;
                newNode->data = x;
                newNode->next = newNext;
                newNode->before = newBefore;
                newBefore->next = newNext->before = newNode;
                length++;
                return 0;
            }
            else if (length == 0)
            {//或序号不合法但是当前长度为0
                now = (Node*)std::malloc(sizeof(Node));
                if (!now)
                {
                    throw std::bad_alloc();
                }
                now->next = now->before = nullptr;
                index = 0;
                length++;
                now->data = x;
                now->next = now;
                now->before = now;
                return 0;
            }
            return TELEPHONE_DS_BAD_INDEX;
            return 0;
        }
        virtual int addAfter(long Index, T&& x)
        {
            if (Index >= 0 && Index < length)
            {//如果序号合法
                if (Index == index)
                    ;
                else if (Index < index)
                {
                    long dis = index - Index;//往前走(按before走)的距离
                    if ((double)dis > length / (double)2)
                    {//按next走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                else if (Index > index)
                {
                    long dis = Index - index;//往后走(按next走)的距离
                    if ((double)dis < length / (double)2)
                    {//按next走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                Node* newBefore = now->before;
                Node* newNext = now;
                Node* newNode = (Node*)std::malloc(sizeof(Node));
                if (!newNode)
                {
                    throw std::bad_alloc();
                }
                newNode->next = newNode->before = nullptr;
                newNode->data = std::move(x);
                newNode->next = newNext;
                newNode->before = newBefore;
                newBefore->next = newNext->before = newNode;
                index++;
                length++;
                return 0;
            }
            else if (length == 0)
            {//或序号不合法但是当前长度为0
                now = (Node*)std::malloc(sizeof(Node));
                if (!now)
                {
                    throw std::bad_alloc();
                }
                now->before = now->next = nullptr;
                index = 0;
                length++;
                now->data = std::move(x);
                now->next = now;
                now->before = now;
                return 0;
            }
            return TELEPHONE_DS_BAD_INDEX;
        }
        virtual T& at(long Index)
        {
            if (Index >= 0 && Index < length)
            {
                if (Index == index)
                    ;
                else if (Index < index)
                {
                    long dis = index - Index;//往前走(按before走)的距离
                    if ((double)dis > length / (double)2)
                    {//按next走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                else if (Index > index)
                {
                    long dis = Index - index;//往后走(按next走)的距离
                    if ((double)dis < length / (double)2)
                    {//按next走
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->next;
                            index++;
                            index %= length;
                        }
                    }
                    else
                    {//按before走
                        dis = length - dis;
                        for (long i = 0; i < dis; ++i)
                        {
                            now = now->before;
                            index--;
                            if (index == -1)
                                index = length - 1;
                        }
                    }
                }
                return now->data;
            }
            throw std::out_of_range("bad index");
        }
        virtual int deleteFrom(long Index, long num)  //删除的结点包括Index所代表的结点
        {
            if (Index >= 0 && Index < length)
            {//结点序号合法
                if (num <= length - index)
                {//删除的结点数不大于从当前结点开始到链表末尾所剩下的结点个数
                    if (num > 0)
                    {//至少删除1个结点
                        if (Index == index)
                            ;
                        else if (Index < index)
                        {
                            long dis = index - Index;//往前走(按before走)的距离
                            if ((double)dis > length / (double)2)
                            {//按next走
                                dis = length - dis;
                                for (long i = 0; i < dis; ++i)
                                {
                                    now = now->next;
                                    index++;
                                    index %= length;
                                }
                            }
                            else
                            {//按before走
                                for (long i = 0; i < dis; ++i)
                                {
                                    now = now->before;
                                    index--;
                                    if (index == -1)
                                        index = length - 1;
                                }
                            }
                        }
                        else if (Index > index)
                        {
                            long dis = Index - index;//往后走(按next走)的距离
                            if ((double)dis < length / (double)2)
                            {//按next走
                                for (long i = 0; i < dis; ++i)
                                {
                                    now = now->next;
                                    index++;
                                    index %= length;
                                }
                            }
                            else
                            {//按before走
                                dis = length - dis;
                                for (long i = 0; i < dis; ++i)
                                {
                                    now = now->before;
                                    index--;
                                    if (index == -1)
                                        index = length - 1;
                                }
                            }
                        }
                        now = now->before;
                        index--;
                        if (index == -1)
                            index = length - 1;
                        if (num == length)
                        {//1.递推地释放链式数据 2.链表属性重置
                            Node* needFree = now;
                            //如果需要释放结点,那么释放的第一个结点是now结点
                            //如果不需要释放结点,那么now结点为nullptr
                            for (long i = 0; i < length; ++i)//次数控制:次数与长度相等
                            {
                                Node* temp = needFree->next;
                                std::free(needFree);//此处会出现野指针,但可以保证不会再使用野指针进行访问或操作内存
                                needFree = temp;
                                //推进
                            }
                            needFree = nullptr;
                            length = 0;
                            index = -1;
                            now = nullptr;
                        }
                        else
                        {
                            Node* newNext = now->next;
                            for (long i = 0; i < num; ++i)
                            {
                                newNext = newNext->next;
                            }
                            Node* newBefore = now;
                            Node* tempNow = nullptr;
                            Node* tempNext = newBefore->next;
                            for (long j = 0; j < num; ++j)
                            {
                                tempNow = tempNext;
                                tempNext = tempNow->next;
                                std::free(tempNow);
                            }
                            newBefore->next = newNext;
                            newNext->before = newBefore;
                            length -= num;
                            if (index > (Index + num - 1))
                            {
                                index -= num;
                            }
                        }
                        return 0;
                    }
                    return TELEPHONE_DS_BAD_DEL_NUM;
                }
                return TELEPHONE_DS_BAD_DEL_NUM;
            }
            return TELEPHONE_DS_BAD_INDEX;
        }
        virtual long len()
        {
            return length;
        }
        virtual int isEmpty()   //如果是空的，返回 1(true)
        {
            return (length == 0) ? (1) : (0);
        }
    };
}

#endif //POLYNOMIAL_LINKEDLIST_H
