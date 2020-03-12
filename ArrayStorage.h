//
// Created by Telephone on 2019/10/19 0019.
//


#ifndef ARRAYSTORAGE_ARRAYSTORAGE_H
#define ARRAYSTORAGE_ARRAYSTORAGE_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>

namespace Telephone_DS::arrayBase::ArrayStorage //Telephone写的ArrayStorage的命名空间
{
    template <typename T> class ArrayStorage
    {   /* Do not create an ArrayStorage of reference type*/
    private:
        long scale = 100;           //每次增加空间时增加的可容纳元素个数
        T *memHead = nullptr;       //可用空间首地址
        long memLen = 0;            //当前能够存储的元素总个数
        long length = 0;            //当前实际存储的元素总个数
        T *head = nullptr;          //0号结点的首地址
        T *tail = nullptr;          //当前最大号数结点的地址 + 1
    protected:
        inline T *findNext(T *now , T *MemHead , T *MemTail)
        {
            now++;
            if(now == MemTail)
            {
                now = MemHead;
            }
            return now;
        }
        inline T *findBefore(T *now , T *MemHead , T *MemTail)
        {
            now--;
            if(now == MemHead - 1)
            {
                now = MemTail - 1;
            }
            return now;
        }
    public:
        explicit ArrayStorage(long scale)                               //有参数构造
        {
            this->scale = scale;
        }
        explicit ArrayStorage() = default;                              //无参数构造
        ArrayStorage(ArrayStorage<T> const &src)                        //拷贝构造函数，拷贝构造不改变被复制的对象
        {
            if(this == &src)
                return;
            scale = src.scale;
            if(src.memHead == nullptr)
            {
                memHead = nullptr;
                memLen = 0;
                length = 0;
                head = nullptr;
                tail = nullptr;
            }
            else
            {
                long headDis = src.head - src.memHead;
                long tailDis = src.tail - src.memHead;
                memHead = (T *)std::malloc(src.memLen * sizeof(T));
                std::memset(memHead , 0 , src.memLen * sizeof(T));
                memLen = src.memLen;
                length = src.length;
                head = memHead + headDis;
                tail = memHead + tailDis;
                std::memmove(memHead , src.memHead , src.memLen * sizeof(T)); //不重叠
            }
        }
        ArrayStorage(ArrayStorage<T> &&src) noexcept                    //移动构造函数
        {
            scale = src.scale;
            if (src.memHead == nullptr)
            {
                memHead = nullptr;
                memLen = 0;
                length = 0;
                head = nullptr;
                tail = nullptr;
            }
            else
            {
                memHead = src.memHead;
                memLen = src.memLen;
                length = src.length;
                head = src.head;
                tail = src.tail;
                src.memHead = src.head = src.tail = nullptr;
                src.memLen = src.length = 0;
            }
        }
        ArrayStorage<T> &operator=(ArrayStorage<T> const &right)        //拷贝赋值，拷贝赋值不改变被复制的对象
        {
            if(this != &right)
            {
                /******释放******/
                std::free(memHead);
                /******释放******/

                /******重置******/
                scale = 100;
                memHead = nullptr;
                memLen = 0;
                length = 0;
                head = nullptr;
                tail = nullptr;
                /******重置******/

                /*赋值与内存拷贝*/
                scale = right.scale;
                if(right.memHead == nullptr)
                {
                    memHead = nullptr;
                    memLen = 0;
                    length = 0;
                    head = nullptr;
                    tail = nullptr;
                }
                else
                {
                    long headDis = right.head - right.memHead;
                    long tailDis = right.tail - right.memHead;
                    memHead = (T *)std::malloc(right.memLen * sizeof(T));
                    std::memset(memHead, 0 , right.memLen * sizeof(T));
                    memLen = right.memLen;
                    length = right.length;
                    head = memHead + headDis;
                    tail = memHead + tailDis;
                    std::memmove(memHead , right.memHead , right.memLen * sizeof(T)); //不重叠
                }
                /*赋值与内存拷贝*/
            }
            return *this;
        }
        ArrayStorage<T> &operator=(ArrayStorage<T> &&right) noexcept    //移动赋值
        {
            if (this != &right)
            {
                /******释放******/
                std::free(memHead);
                /******释放******/

                /******重置******/
                scale = 100;
                memHead = nullptr;
                memLen = 0;
                length = 0;
                head = nullptr;
                tail = nullptr;
                /******重置******/

                /*赋值与内存窃取*/
                scale = right.scale;
                if (right.memHead == nullptr)
                {
                    memHead = nullptr;
                    memLen = 0;
                    length = 0;
                    head = nullptr;
                    tail = nullptr;
                }
                else
                {
                    memHead = right.memHead;
                    memLen = right.memLen;
                    length = right.length;
                    head = right.head;
                    tail = right.tail;
                    right.memHead = right.head = right.tail = nullptr;
                    right.memLen = right.length = 0;
                }
                /*赋值与内存窃取*/
            }
            return *this;
        }
        virtual ~ArrayStorage()                                         //析构 //虚以派生
        {
            std::free(memHead);
            memHead = nullptr;
            memLen = 0;
            length = 0;
            head = nullptr;
            tail = nullptr;
        }
        virtual void addBefore(long index , T const &x)
        {
            if(length == memLen)    //满了或尚未分配空间     //空间分配
            {
                if (memLen == 0)
                {//尚未分配空间
                    memHead = (T *)std::realloc(memHead,
                                                      (memLen + scale) * sizeof(T));
                    std::memset(memHead + memLen , 0 , scale * sizeof(T));
                    memLen += scale;
                } else
                {//满了
                    if (head == tail)
                    {/*首尾粘连 , 需要先分配空间并更新memHead指针和memLen值 , 再更新head和tail指针 ,
                    再迁移数据 , 最后更新head指针*/
                        long dis = head - memHead;
                        size_t moveSize = (length - dis) * sizeof(T);
                        memHead = (T *)std::realloc(memHead,
                                                          (memLen + scale) * sizeof(T));
                        std::memset(memHead + memLen, 0, scale * sizeof(T));
                        memLen += scale;
                        head = tail = memHead + dis;
                        std::memmove(head + scale, head, moveSize);
                        head += scale;
                    } else
                    {//首尾分离 , 需要先分配空间并更新memHead指针和memLen值 , 再更新head和tail指针
                        memHead = (T *)std::realloc(memHead,
                                                          (memLen + scale) * sizeof(T));
                        std::memset(memHead + memLen, 0, scale * sizeof(T));
                        memLen += scale;
                        head = memHead;
                        tail = head + length;
                    }
                }
            }

            //扩展空间后 , 长度不为0的情况下

            //需要判断下标是否合法
            //通过逻辑上的前后连续赋值 , 实现插入 , 最后更新length、head、tail
            //通过计算得出是移动前段数据还是移动后段数据

            //扩展空间后 , 长度为0的情况下

            //无需判断下标是否合法
            //直接在memHead后放置第一个结点 , 并更新length、head、tail

            if(length == 0)
            {//无需判断下标合法 , 将第一个结点设置为memHead指向的首个元素 , 设置好length、head和tail ,
                // 设置好新结点的值
                *(memHead) = x;
                length++;
                head = memHead;
                tail = memHead + 1;
            } else
            {//需要判断下标合法
                if(index >= 0 && index < length)
                {
                    T *MemTail = memHead + memLen;
                    T *MemHead = memHead;
                    if(index < length / 2)
                    {//移动前段
                        T *w = findBefore(head , MemHead , MemTail);//逻辑上头结点的前一个结点
                        T *n = w;
                        long times = index;
                        for (long i = 0; i < times; ++i)
                        {
                            T *temp = findNext(w , MemHead , MemTail);
                            *w = *temp;
                            w = temp;
                        }
                        *w = x;
                        head = n;
                        length++;
                    } else
                    {//移动后段
                        T *w = tail;
                        T *n = w + 1;
                        long times = length - 1 - index + 1;
                        for (long i = 0; i < times; ++i)
                        {
                            T *temp = findBefore(w , MemHead , MemTail);
                            *w = *temp;
                            w = temp;
                        }
                        *w = x;
                        tail = n;
                        length++;
                    }
                    return;
                }
                //抛出异常
                char exp[100];
                std::sprintf(exp , "[function addBefore()] Do not have such node : index(%ld)" ,
                             index);
                throw std::out_of_range(exp);
            }
        }
        virtual void addBefore(long index , T &&x)
        {
            if(length == memLen)    //满了或尚未分配空间     //空间分配
            {
                if (memLen == 0)
                {//尚未分配空间
                    memHead = (T *)std::realloc(memHead,
                                                (memLen + scale) * sizeof(T));
                    std::memset(memHead + memLen , 0 , scale * sizeof(T));
                    memLen += scale;
                } else
                {//满了
                    if (head == tail)
                    {/*首尾粘连 , 需要先分配空间并更新memHead指针和memLen值 , 再更新head和tail指针 ,
                    再迁移数据 , 最后更新head指针*/
                        long dis = head - memHead;
                        size_t moveSize = (length - dis) * sizeof(T);
                        memHead = (T *)std::realloc(memHead,
                                                    (memLen + scale) * sizeof(T));
                        std::memset(memHead + memLen, 0, scale * sizeof(T));
                        memLen += scale;
                        head = tail = memHead + dis;
                        std::memmove(head + scale, head, moveSize);
                        head += scale;
                    } else
                    {//首尾分离 , 需要先分配空间并更新memHead指针和memLen值 , 再更新head和tail指针
                        memHead = (T *)std::realloc(memHead,
                                                    (memLen + scale) * sizeof(T));
                        std::memset(memHead + memLen, 0, scale * sizeof(T));
                        memLen += scale;
                        head = memHead;
                        tail = head + length;
                    }
                }
            }

            //扩展空间后 , 长度不为0的情况下

            //需要判断下标是否合法
            //通过逻辑上的前后连续赋值 , 实现插入 , 最后更新length、head、tail
            //通过计算得出是移动前段数据还是移动后段数据

            //扩展空间后 , 长度为0的情况下

            //无需判断下标是否合法
            //直接在memHead后放置第一个结点 , 并更新length、head、tail

            if(length == 0)
            {//无需判断下标合法 , 将第一个结点设置为memHead指向的首个元素 , 设置好length、head和tail ,
                // 设置好新结点的值
                *(memHead) = std::move(x);
                length++;
                head = memHead;
                tail = memHead + 1;
            } else
            {//需要判断下标合法
                if(index >= 0 && index < length)
                {
                    T *MemTail = memHead + memLen;
                    T *MemHead = memHead;
                    if(index < length / 2)
                    {//移动前段
                        T *w = findBefore(head , MemHead , MemTail);//逻辑上头结点的前一个结点
                        T *n = w;
                        long times = index;
                        for (long i = 0; i < times; ++i)
                        {
                            T *temp = findNext(w , MemHead , MemTail);
                            *w = *temp;
                            w = temp;
                        }
                        *w = std::move(x);
                        head = n;
                        length++;
                    } else
                    {//移动后段
                        T *w = tail;
                        T *n = w + 1;
                        long times = length - 1 - index + 1;
                        for (long i = 0; i < times; ++i)
                        {
                            T *temp = findBefore(w , MemHead , MemTail);
                            *w = *temp;
                            w = temp;
                        }
                        *w = std::move(x);
                        tail = n;
                        length++;
                    }
                    return;
                }
                //抛出异常
                char exp[100];
                std::sprintf(exp , "[function addBefore()] Do not have such node : index(%ld)" ,
                             index);
                throw std::out_of_range(exp);
            }
        }
        virtual void addAfter(long index , T const &x)
        {
            if(length == memLen)    //满了或尚未分配空间     //空间分配
            {
                if (memLen == 0)
                {//尚未分配空间
                    memHead = (T *)std::realloc(memHead,
                                                      (memLen + scale) * sizeof(T));
                    std::memset(memHead + memLen, 0, scale * sizeof(T));
                    memLen += scale;
                } else
                {//满了
                    if (head == tail)
                    {/*首尾粘连 , 需要先分配空间并更新memHead指针和memLen值 , 再更新head和tail指针 ,
                    再迁移数据 , 最后更新head指针*/
                        long dis = head - memHead;
                        size_t moveSize = (length - dis) * sizeof(T);
                        memHead = (T *)std::realloc(memHead,
                                                          (memLen + scale) * sizeof(T));
                        std::memset(memHead + memLen, 0, scale * sizeof(T));
                        memLen += scale;
                        head = tail = memHead + dis;
                        std::memmove(head + scale, head, moveSize);
                        head += scale;
                    } else
                    {//首尾分离 , 需要先分配空间并更新memHead指针和memLen值 , 再更新head和tail指针
                        memHead = (T *)std::realloc(memHead,
                                                          (memLen + scale) * sizeof(T));
                        std::memset(memHead + memLen, 0, scale * sizeof(T));
                        memLen += scale;
                        head = memHead;
                        tail = head + length;
                    }
                }
            }

            //扩展空间后 , 长度不为0的情况下

            //需要判断下标是否合法
            //通过逻辑上的前后连续赋值 , 实现插入 , 最后更新length、head、tail
            //通过计算得出是移动前段数据还是移动后段数据

            //扩展空间后 , 长度为0的情况下

            //无需判断下标是否合法
            //直接在memHead后放置第一个结点 , 并更新length、head、tail

            if(length == 0)
            {//无需判断下标合法 , 将第一个结点设置为memHead指向的首个元素 , 设置好length、head和tail ,
                // 设置好新结点的值
                *(memHead) = x;
                length++;
                head = memHead;
                tail = memHead + 1;
            } else
            {//需要判断下标合法
                if(index >= 0 && index < length)
                {
                    T *MemTail = memHead + memLen;
                    T *MemHead = memHead;
                    if(index < length / 2)
                    {//移动前段
                        T *w = findBefore(head , MemHead , MemTail);//逻辑上头结点的前一个结点
                        T *n = w;
                        long times = index + 1;
                        for (long i = 0; i < times; ++i)
                        {
                            T *temp = findNext(w , MemHead , MemTail);
                            *w = *temp;
                            w = temp;
                        }
                        *w = x;
                        head = n;
                        length++;
                    } else
                    {//移动后段
                        T *w = tail;
                        T *n = w + 1;
                        long times = length - 1 - index;
                        for (long i = 0; i < times; ++i)
                        {
                            T *temp = findBefore(w , MemHead , MemTail);
                            *w = *temp;
                            w = temp;
                        }
                        *w = x;
                        tail = n;
                        length++;
                    }
                    return;
                }
                //抛出异常
                char exp[100];
                std::sprintf(exp , "[function addAfter()] Do not have such node : index(%ld)" ,
                             index);
                throw std::out_of_range(exp);
            }
        }
        virtual void addAfter(long index , T &&x)
        {
            if(length == memLen)    //满了或尚未分配空间     //空间分配
            {
                if (memLen == 0)
                {//尚未分配空间
                    memHead = (T *)std::realloc(memHead,
                                                (memLen + scale) * sizeof(T));
                    std::memset(memHead + memLen, 0, scale * sizeof(T));
                    memLen += scale;
                } else
                {//满了
                    if (head == tail)
                    {/*首尾粘连 , 需要先分配空间并更新memHead指针和memLen值 , 再更新head和tail指针 ,
                    再迁移数据 , 最后更新head指针*/
                        long dis = head - memHead;
                        size_t moveSize = (length - dis) * sizeof(T);
                        memHead = (T *)std::realloc(memHead,
                                                    (memLen + scale) * sizeof(T));
                        std::memset(memHead + memLen, 0, scale * sizeof(T));
                        memLen += scale;
                        head = tail = memHead + dis;
                        std::memmove(head + scale, head, moveSize);
                        head += scale;
                    } else
                    {//首尾分离 , 需要先分配空间并更新memHead指针和memLen值 , 再更新head和tail指针
                        memHead = (T *)std::realloc(memHead,
                                                    (memLen + scale) * sizeof(T));
                        std::memset(memHead + memLen, 0, scale * sizeof(T));
                        memLen += scale;
                        head = memHead;
                        tail = head + length;
                    }
                }
            }

            //扩展空间后 , 长度不为0的情况下

            //需要判断下标是否合法
            //通过逻辑上的前后连续赋值 , 实现插入 , 最后更新length、head、tail
            //通过计算得出是移动前段数据还是移动后段数据

            //扩展空间后 , 长度为0的情况下

            //无需判断下标是否合法
            //直接在memHead后放置第一个结点 , 并更新length、head、tail

            if(length == 0)
            {//无需判断下标合法 , 将第一个结点设置为memHead指向的首个元素 , 设置好length、head和tail ,
                // 设置好新结点的值
                *(memHead) = std::move(x);
                length++;
                head = memHead;
                tail = memHead + 1;
            } else
            {//需要判断下标合法
                if(index >= 0 && index < length)
                {
                    T *MemTail = memHead + memLen;
                    T *MemHead = memHead;
                    if(index < length / 2)
                    {//移动前段
                        T *w = findBefore(head , MemHead , MemTail);//逻辑上头结点的前一个结点
                        T *n = w;
                        long times = index + 1;
                        for (long i = 0; i < times; ++i)
                        {
                            T *temp = findNext(w , MemHead , MemTail);
                            *w = *temp;
                            w = temp;
                        }
                        *w = std::move(x);
                        head = n;
                        length++;
                    } else
                    {//移动后段
                        T *w = tail;
                        T *n = w + 1;
                        long times = length - 1 - index;
                        for (long i = 0; i < times; ++i)
                        {
                            T *temp = findBefore(w , MemHead , MemTail);
                            *w = *temp;
                            w = temp;
                        }
                        *w = std::move(x);
                        tail = n;
                        length++;
                    }
                    return;
                }
                //抛出异常
                char exp[100];
                std::sprintf(exp , "[function addAfter()] Do not have such node : index(%ld)" ,
                             index);
                throw std::out_of_range(exp);
            }
        }
        virtual T &at(long index)
        {
            if(index >= 0 && index < length)
            {
                long memIndex = head - memHead;
                memIndex += index;
                return *(memHead + (memIndex % memLen));
            }
            char exp[100];
            std::sprintf(exp , "[function at()] Do not have such node : index(%ld)" , index);
            throw std::out_of_range(exp);
        }
        virtual void deleteFrom(long index , long num)      // the index node itself will be deleted
        // too（include）
        {
            char exp[100];
            if(index >= 0 && index < length)
            {
                if(num <= length - index)
                {
                    if(num > 0)
                    {
                        if(index < length / 2)
                        {//移动前段
                            T *MemHead = memHead;
                            T *MemTail = MemHead + memLen;

                            long memIndex = head - memHead;
                            memIndex += index;
                            T *delNode = memHead + (memIndex % memLen); //要删除的结点的地址

                            if (index == 0)
                            {//无数据迁移
                                for (long i = 0; i < num; ++i)
                                {
                                    delNode = findNext(delNode , MemHead , MemTail);
                                }
                                head = delNode;
                                length -= num;
                            }
                            else
                            {//先迁移数据 , 再更新head和length
                                T *newNode = delNode;
                                for (long j = 0; j < num - 1; ++j)
                                {//newNode是要删除的最后一个结点的地址
                                    newNode = findNext(newNode , MemHead , MemTail);
                                }
                                T *oldNode = findBefore(delNode , MemHead , MemTail);
                                    //oldNode是要删除的结点的前一个结点的地址
                                for (long k = 0; k < index; ++k)
                                {
                                    *newNode = *oldNode;
                                    newNode = findBefore(newNode , MemHead , MemTail);
                                    oldNode = findBefore(oldNode , MemHead , MemTail);
                                }
                                head = findNext(newNode , MemHead , MemTail);
                                length -= num;
                            }
                        } else
                        {//移动后段
                            T *MemHead = memHead;
                            T *MemTail = MemHead + memLen;

                            long memIndex = head - memHead;
                            memIndex += index;
                            T *delNode = memHead + (memIndex % memLen); //要删除的结点的地址

                            if (num == length - index)
                            {//无数据迁移
                                tail = delNode;
                                length -= num;
                            }
                            else
                            {//先迁移数据 , 再更新tail和length
                                T *newNode = delNode;
                                T *oldNode = delNode;
                                for (long m = 0; m < num; ++m)
                                {
                                    oldNode = findNext(oldNode , MemHead , MemTail);
                                }
                                for (long n = 0; n < length - index - num; ++n)
                                {
                                    *newNode = *oldNode;
                                    newNode = findNext(newNode , MemHead , MemTail);
                                    oldNode = findNext(oldNode , MemHead , MemTail);
                                }
                                tail = findBefore(newNode , MemHead , MemTail) + 1;
                                length -= num;
                            }
                        }
                        return;
                    }
                    std::sprintf(exp ,
                                 "[function deleteFrom()] Delete num is too small : num(%ld) from index"
                                 "(%ld)" ,
                                 num , index);
                    throw std::length_error(exp);
                }
                std::sprintf(exp ,
                             "[function deleteFrom()] Delete num is too large : num(%ld) from index(%ld)" ,
                             num , index);
                throw std::length_error(exp);
            }
            std::sprintf(exp , "[function deleteFrom()] Do not have such node : index(%ld)" ,
                         index);
            throw std::out_of_range(exp);
        }
        virtual long len()
        {
            return length;
        }
        virtual int isEmpty()   // if empty , return 1(true)
        {
            return (length == 0)?(1):(0);
        }
    };
}

#endif //ARRAYSTORAGE_ARRAYSTORAGE_H
