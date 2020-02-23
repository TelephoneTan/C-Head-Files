//
// Created by Telephone on 2019/12/29 0029.
//

/// @file Tree.h

#ifndef TREE_TREE_H
#define TREE_TREE_H

#include <LinkedList.h>
#include <cstring>
#include <utility>
#include <LQueue.h>
#include <LStack.h>
#include <cmath>
#include <functional>

/// namespace of common tree
namespace Telephone_DS::treeBase::Tree
{
    /**
     * @brief common tree
     * @tparam T type of data in tree-node
     */
    template <typename T> class Tree
    {
    private:
        /**
         * @brief tree-node of common tree
         * @tparam U type of data in tree-node
         * @warning this is a private class defined in class Tree
         */
        template <typename U> class TreeNode
        {
        public:
            /// data of tree-node
            U data;
        private:
            /// pointer to parent node
            TreeNode<U> *parent = nullptr;
            /**
             * a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of pointers to
             * child nodes
             */
            linkBase::LinkedList::LinkedList<TreeNode<U>*> children;
        public:
            /**
             * @brief general constructor(copy)
             * @param d data of the new node
             * @note use copy-constructor of type U to copy the data to the new node
             * @par init
             * - parent = nullptr
             * - data = specified data
             * - child-nodes list = empty
             */
            explicit TreeNode(U const &d)
                    : data(d)
            {}
            /**
             * @brief general constructor(move)
             * @param d data of the new node
             * @note use move-constructor of type U to move the data to the new node
             * @par init
             * - parent = nullptr
             * - data = specified data
             * - child-nodes list = empty
             */
            explicit TreeNode(U &&d)
                    : data(std::move(d))
            {}
            /**
             * @brief copy-constructor
             * @param src
             * @note use copy-constructor of type U and child-nodes @link
             * Telephone_DS::linkBase::LinkedList::LinkedList list @endlink to copy data and
             * child-nodes list from the node passed in by parameter
             * @par Result:
             * current node will have the same data, parent pointer and child-nodes list as the
             * node passed in by parameter
             */
            TreeNode(TreeNode<U> const &src)
                    : data(src.data),parent(src.parent),children(src.children)
            {}
            /**
             * @brief move-constructor
             * @param src
             * @note use move-constructor of type U and child-nodes @link
             * Telephone_DS::linkBase::LinkedList::LinkedList list @endlink to move data and
             * child-nodes list from the node passed in by parameter
             * @par Result:
             * current node will have the same data, parent pointer and child-nodes list as the
             * node passed in by parameter
             */
            TreeNode(TreeNode<U> &&src) noexcept
                    : data(std::move(src.data)),parent(src.parent),children(std::move(src.children))
            {}
            /**
             * @brief copy-assignment
             * @param right
             * @return left reference of the node being assigned
             * @note use copy-assignment of type U and child-nodes @link
             * Telephone_DS::linkBase::LinkedList::LinkedList list @endlink to copy data and
             * child-nodes list from the node passed in by parameter
             * @par Result:
             * current node will have the same data, parent pointer and child-nodes list as the
             * node passed in by parameter
             */
            TreeNode<U> &operator=(TreeNode<U> const &right)
            {
                if(this == &right)
                    return *this;
                data = right.data;
                parent = right.parent;
                children = right.children;
                return *this;
            }
            /**
             * @brief move-assignment
             * @param right
             * @return left reference of the node being assigned
             * @note use move-assignment of type U and child-nodes @link
             * Telephone_DS::linkBase::LinkedList::LinkedList list @endlink to move data and
             * child-nodes list from the node passed in by parameter
             * @par Result:
             * current node will have the same data, parent pointer and child-nodes list as the
             * node passed in by parameter
             */
            TreeNode<U> &operator=(TreeNode<U> &&right) noexcept
            {
                data = std::move(right.data);
                parent = right.parent;
                children = std::move(right.children);
                return *this;
            }
            /**
             * @brief destructor
             * @note this function will only do two things:
             * -# call the destructor of data
             * -# call the destructor of child-nodes list
             */
            virtual ~TreeNode() = default;
            /**
             * @brief get child nodes
             * @return a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of pointers
             * to child nodes
             * @note changing the returned list won't actually effect the child-nodes list in
             * current node , but the child nodes of current node can be effected through the
             * pointers in the returned list
             * @par Order:
             * the returned list is tha same as the child-nodes list
             */
            virtual auto getChildren() -> linkBase::LinkedList::LinkedList<TreeNode<U>*>
            {
                return children;
            }
            /**
             * @brief get the first child node in the child-nodes list
             * @return
             * - if the child-nodes list is not empty , return a pointer to the first child node
             * in the child-nodes list;
             * - or else , return nullptr
             */
            virtual auto getFirstChild() -> TreeNode<U>*
            {
                if(children.isEmpty())
                {
                    return nullptr;
                }
                return children.at(0);
            }
            /**
             * @brief get the last child node in the child-nodes list
             * @return
             * - if the child-nodes list is not empty , return a pointer to the last child node
             * in the child-nodes list;
             * - or else , return nullptr
             */
            virtual auto getLastChild() -> TreeNode<U>*
            {
                if(children.isEmpty())
                {
                    return nullptr;
                }
                return children.at(children.len() - 1);
            }
            /**
             * @brief traverse current node's child-nodes list and then get child nodes containing
             * the specified data
             * @param value the specified data
             * @return a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of pointers
             * to child nodes containing the specified data
             * @par How to compare:
             * - if the type of node's data part is floating-point(float , double , long double)
             * number , use floating-point error (1e-6);
             * - or else , use operator ==
             * @par Order:
             * the returned list is consistent with the child-nodes list in sequential order of
             * nodes
             */
            virtual auto getChildrenOfData(U const &value) ->
            linkBase::LinkedList::LinkedList<TreeNode<U>*>
            {
                linkBase::LinkedList::LinkedList<TreeNode<U>*> res;
                if(typeid(U) != typeid(double) && typeid(U) != typeid(float) && typeid(U) !=
                    typeid(long double))
                {
                    for (int i = 0; i < children.len(); ++i)
                    {
                        TreeNode<U> *temp = children.at(i);
                        if(temp->data == value)
                        {
                            res.addAfter(res.len() - 1 , temp);
                        }
                    }
                } else
                {
                    for (int i = 0; i < children.len(); ++i)
                    {
                        TreeNode<U> *temp = children.at(i);
                        if(std::fabs(temp->data - value) <= 1e-6)
                        {
                            res.addAfter(res.len() - 1 , temp);
                        }
                    }
                }
                return std::move(res);
            }
            /**
             * @brief traverse current node's child-nodes list and then get indexes of child
             * nodes containing the specified data
             * @param value the specified data
             * @return a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of indexes
             * of child nodes containing the specified data
             * @par How to compare:
             * - if the type of node's data part is floating-point(float , double , long double)
             * number , use floating-point error (1e-6);
             * - or else , use operator ==
             * @par Order:
             * the returned list is consistent with the child-nodes list in sequential order of
             * nodes
             */
            virtual auto getChildrenIndexOfData(U const &value) ->
            linkBase::LinkedList::LinkedList<int>
            {
                linkBase::LinkedList::LinkedList<int> res;
                if(typeid(U) != typeid(double) && typeid(U) != typeid(float) && typeid(U) !=
                                                                                typeid(long double))
                {
                    for (int i = 0; i < children.len(); ++i)
                    {
                        if(children.at(i)->data == value)
                        {
                            res.addAfter(res.len() - 1 , i);
                        }
                    }
                } else
                {
                    for (int i = 0; i < children.len(); ++i)
                    {
                        if(std::fabs(children.at(i)->data - value) <= 1e-6)
                        {
                            res.addAfter(res.len() - 1 , i);
                        }
                    }
                }
                return std::move(res);
            }
            /**
             * @brief traverse current node's child-nodes list and then get child nodes
             * containing the specified data
             * @param value the specified data
             * @param equal function to judge whether one data is equal to another , which won't
             * change the data objects to be compared
             * @return a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of pointers
             * to child nodes containing the specified data
             * @par How to compare:
             * call a function using the callable object passed in by the parameter to compare
             * whether the data part of each child node is equal to the specified data:
             * - if equal , the function should return 1
             * - if not equal , the function should return 0
             * - the function should have two formal parameters , the first one is a const lvalue
             * reference bound to type U which means one data object , the second one is a const
             * lvalue reference bound to type U which means another data object
             * @par Order:
             * the returned list is consistent with the child-nodes list in sequential order of
             * nodes
             */
            virtual auto getChildrenOfData(U const &value , std::function<int(U const & , U const
            &)> equal)
            -> linkBase::LinkedList::LinkedList<TreeNode<U>*>
            {
                linkBase::LinkedList::LinkedList<TreeNode<U>*> res;
                for (int i = 0; i < children.len(); ++i)
                {
                    TreeNode<U> *temp = children.at(i);
                    if(equal(value , temp->data))
                    {
                        res.addAfter(res.len() - 1 , temp);
                    }
                }
                return std::move(res);
            }
            /**
             * @brief traverse current node's child-nodes list and then get indexes of child
             * nodes containing the specified data
             * @param value the specified data
             * @param equal function to judge whether one data is equal to another , which won't
             * change the data objects to be compared
             * @return a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of indexes
             * of child nodes containing the specified data
             * @par How to compare:
             * call a function using the callable object passed in by the parameter to compare
             * whether the data part of each child node is equal to the specified data:
             * - if equal , the function should return 1
             * - if not equal , the function should return 0
             * - the function should have two formal parameters , the first one is a const lvalue
             * reference bound to type U which means one data object , the second one is a const
             * lvalue reference bound to type U which means another data object
             * @par Order:
             * the returned list is consistent with the child-nodes list in sequential order of
             * nodes
             */
            virtual auto getChildrenIndexOfData(U const &value , std::function<int(U const & , U
            const &)> equal)
            -> linkBase::LinkedList::LinkedList<int>
            {
                linkBase::LinkedList::LinkedList<int> res;
                for (int i = 0; i < children.len(); ++i)
                {
                    if(equal(value , children.at(i)->data))
                    {
                        res.addAfter(res.len() - 1 , i);
                    }
                }
                return std::move(res);
            }
            /**
             * @brief traverse current node's child-nodes list and then get child nodes
             * containing the specified data
             * @param value the specified data
             * @param equal function to judge whether one data is equal to another , which will
             * change the data objects to be compared
             * @return a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of pointers
             * to child nodes containing the specified data
             * @par How to compare:
             * call a function using the callable object passed in by the parameter to compare
             * whether the data part of each child node is equal to the specified data:
             * - if equal , the function should return 1
             * - if not equal , the function should return 0
             * - the function should have two formal parameters , the first one is a lvalue
             * reference bound to type U which means one data object , the second one is a lvalue
             * reference bound to type U which means another data object
             * @par Order:
             * the returned list is consistent with the child-nodes list in sequential order of
             * nodes
             */
            virtual auto getChildrenOfData(U &value , std::function<int(U & , U &)> equal) ->
            linkBase::LinkedList::LinkedList<TreeNode<U>*>
            {
                linkBase::LinkedList::LinkedList<TreeNode<U>*> res;
                for (int i = 0; i < children.len(); ++i)
                {
                    TreeNode<U> *temp = children.at(i);
                    if(equal(value , temp->data))
                    {
                        res.addAfter(res.len() - 1 , temp);
                    }
                }
                return std::move(res);
            }
            /**
             * @brief traverse current node's child-nodes list and then get indexes of child
             * nodes containing the specified data
             * @param value the specified data
             * @param equal function to judge whether one data is equal to another , which will
             * change the data objects to be compared
             * @return a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of indexes
             * of child nodes containing the specified data
             * @par How to compare:
             * call a function using the callable object passed in by the parameter to compare
             * whether the data part of each child node is equal to the specified data:
             * - if equal , the function should return 1
             * - if not equal , the function should return 0
             * - the function should have two formal parameters , the first one is a lvalue
             * reference bound to type U which means one data object , the second one is a lvalue
             * reference bound to type U which means another data object
             * @par Order:
             * the returned list is consistent with the child-nodes list in sequential order of
             * nodes
             */
            virtual auto getChildrenIndexOfData(U &value , std::function<int(U & , U &)> equal) ->
            linkBase::LinkedList::LinkedList<int>
            {
                linkBase::LinkedList::LinkedList<int> res;
                for (int i = 0; i < children.len(); ++i)
                {
                    if(equal(value , children.at(i)->data))
                    {
                        res.addAfter(res.len() - 1 , i);
                    }
                }
                return std::move(res);
            }
            /**
             * @brief get parent node
             * @return a pointer to parent node
             * @note changing the returned value won't actually effect the parent pointer in
             * current node , but the parent node of current node can be effected through the
             * returned pointer
             */
            virtual auto getParent() -> TreeNode<U>*
            {
                return parent;
            }
            /**
             * @brief get the child node of specified index in the child-nodes list
             * @param index
             * @return
             * - if the index exists , return a nonnull pointer to the specified node;
             * - or else , return nullptr
             */
            virtual auto getChildOfIndex(int index) -> TreeNode<U>*
            {
                TreeNode<U> *res = nullptr;
                if(index >= 0 && index < children.len())
                {
                    res = children.at(index);
                }
                return res;
            }
            /**
             * @brief get the number of child nodes
             * @return the number of child nodes
             */
            virtual int childNum()
            {
                return children.len();
            }
            /**
             * @brief whether current node is a leaf-node
             * @return
             * - if current node is a leaf-node , return 1;
             * - or else , return 0
             */
            virtual int isLeaf()
            {
                return children.isEmpty();
            }
            /**
             * @brief get all leaf-nodes of current node
             * @return a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of pointers
             * to each leaf-node
             * @note if current node is a leaf-node , the function will return an empty list
             * @par Order:
             * take current node as a tree-root-node , and then place this tree in this way:
             * <ol>
             * <li>root-up
             * <li>among all the child nodes of a node , the child node with least index in the
             * child-nodes list placed in the far left
             * </ol>
             * in this case , the order of the leaf-nodes in the returned list is:
             * up-to-down and left-to-right
             */
            virtual auto getLeafNodes() -> linkBase::LinkedList::LinkedList <TreeNode<U>*>
            {
                linkBase::Queue::Queue <TreeNode<U>*> nodes;
                linkBase::LinkedList::LinkedList <TreeNode<U>*> leaves;
                if(this->isLeaf())
                {
                    return std::move(leaves);
                }
                nodes.push(this);
                while(!nodes.isEmpty())
                {
                    int times = nodes.len();
                    for (int i = 0; i < times; ++i)
                    {
                        if(nodes.front()->isLeaf())
                        {
                            leaves.addAfter(leaves.len() - 1 , nodes.front());
                        } else
                        {
                            linkBase::LinkedList::LinkedList <TreeNode<U>*> childrenTemp
                                    = std::move(nodes.front()->getChildren());
                            for (int j = 0; j < childrenTemp.len(); ++j)
                            {
                                nodes.push(childrenTemp.at(j));
                            }
                        }
                        nodes.pop();
                    }
                }
                return std::move(leaves);
            }
            /**
             * @brief get current node and all recursive child nodes of current node
             * @return a [list](@ref Telephone_DS::linkBase::LinkedList::LinkedList) of pointers
             * to current node and each recursive child nodes of current node
             * @par Order:
             * take current node as a tree-root-node , and then place this tree in this way:
             * <ol>
             * <li>root-up
             * <li>among all the child nodes of a node , the child node with least index in the
             * child-nodes list placed in the far left
             * </ol>
             * in this case , the order of the nodes in the returned list is:
             * up-to-down and left-to-right
             */
            virtual auto getAllNodes() -> linkBase::LinkedList::LinkedList <TreeNode<U>*>
            {
                linkBase::LinkedList::LinkedList <TreeNode<U>*> res;
                linkBase::Queue::Queue <TreeNode<U>*> row;
                row.push(this);
                while(!row.isEmpty())
                {
                    int times = row.len();
                    for (int i = 0; i < times; ++i)
                    {
                        TreeNode<U> *f = row.front();
                        linkBase::LinkedList::LinkedList <TreeNode<U>*> childrenList
                                = std::move(f->getChildren());
                        for (int j = 0; j < childrenList.len(); ++j)
                        {
                            row.push(childrenList.at(j));
                        }
                        res.addAfter(res.len() - 1 , f);
                        row.pop();
                    }
                }
                return std::move(res);
            }
            /**
             * @brief create a new node with specified data and then add a pointer to the new node
             * to the end of the child-nodes list
             * @param dat specified data
             * @note use copy-constructor of type T to copy the data to the new node
             */
            virtual void addChildWithData(U const &dat)
            {
                children.addAfter(children.len() - 1 , new TreeNode<U>(dat));
                children.at(children.len() - 1)->setParent(*this);
            }
            /**
             * @brief create a new node with specified data and then add a pointer to the new node
             * to the end of the child-nodes list
             * @param dat specified data
             * @note use move-constructor of type T to move the data to the new node
             */
            virtual void addChildWithData(U &&dat)
            {
                children.addAfter(children.len() - 1 , new TreeNode<U>(std::move(dat)));
                children.at(children.len() - 1)->setParent(*this);
            }
            /**
             * @brief create a new node with specified data and then insert a pointer to it
             * before the node of specified index in the child-nodes list
             * @param index
             * @param dat specified data
             * @return
             * - if the index doesn't exist , return -1;
             * - or else , return 0
             * @warning the index must exist , or else the insertion will fail
             * @par After inserting:
             * the new child node's parent will be set to current node
             * @note use copy-constructor of type T to copy the data to the new node
             */
            virtual int insertChildBeforeWithData(int index , U const &dat)
            {
                if(index < 0 || index >= children.len())
                    return -1;
                children.addBefore(index , new TreeNode<U>(dat));
                children.at(index)->setParent(*this);
                return 0;
            }
            /**
             * @brief create a new node with specified data and then insert a pointer to it
             * before the node of specified index in the child-nodes list
             * @param index
             * @param dat specified data
             * @return
             * - if the index doesn't exist , return -1;
             * - or else , return 0
             * @warning the index must exist , or else the insertion will fail
             * @par After inserting:
             * the new child node's parent will be set to current node
             * @note use move-constructor of type T to move the data to the new node
             */
            virtual int insertChildBeforeWithData(int index , U &&dat)
            {
                if(index < 0 || index >= children.len())
                    return -1;
                children.addBefore(index , new TreeNode<U>(std::move(dat)));
                children.at(index)->setParent(*this);
                return 0;
            }
            /**
             * @brief create a new node with specified data and then insert a pointer to it
             * after the node of specified index in the child-nodes list
             * @param index
             * @param dat specified data
             * @return
             * - if the index doesn't exist , return -1;
             * - or else , return 0
             * @warning the index must exist , or else the insertion will fail
             * @par After inserting:
             * the new child node's parent will be set to current node
             * @note use copy-constructor of type T to copy the data to the new node
             */
            virtual int insertChildAfterWithData(int index , U const &dat)
            {
                if(index < 0 || index >= children.len())
                    return -1;
                children.addAfter(index , new TreeNode<U>(dat));
                children.at(index + 1)->setParent(*this);
                return 0;
            }
            /**
             * @brief create a new node with specified data and then insert a pointer to it
             * after the node of specified index in the child-nodes list
             * @param index
             * @param dat specified data
             * @return
             * - if the index doesn't exist , return -1;
             * - or else , return 0
             * @warning the index must exist , or else the insertion will fail
             * @par After inserting:
             * the new child node's parent will be set to current node
             * @note use move-constructor of type T to move the data to the new node
             */
            virtual int insertChildAfterWithData(int index , U &&dat)
            {
                if(index < 0 || index >= children.len())
                    return -1;
                children.addAfter(index , new TreeNode<U>(std::move(dat)));
                children.at(index + 1)->setParent(*this);
                return 0;
            }
            /**
             * @brief remove the first node in the child-nodes list , just like calling the @link
             * ~TreeNode() destructor @endlink of the first child-node
             * @return
             * - if the child-nodes list is empty , return -1;
             * - or else , return 0
             * @warning the child-nodes list must not be empty , or else the remove will fail
             * @par After removing:
             * as for the child nodes of the node being removed:
             * - pointers to them will be added to the end of current node's child-nodes list
             * - their parent will be set to current node
             */
            virtual int removeFirstChild()
            {
                if(children.isEmpty())
                    return -1;
                linkBase::LinkedList::LinkedList <TreeNode<U>*> xChildren
                    = std::move(children.at(0)->getChildren());
                delete children.at(0);
                children.deleteFrom(0 , 1);
                for (int i = 0; i < xChildren.len(); ++i)
                {
                    xChildren.at(i)->setParent(*this);
                    children.addAfter(children.len() - 1 , xChildren.at(i));
                }
                return 0;
            }
            /**
             * @brief remove the last node in the child-nodes list , just like calling the @link
             * ~TreeNode() destructor @endlink of the last child-node
             * @return
             * - if the child-nodes list is empty , return -1;
             * - or else , return 0
             * @warning the child-nodes list must not be empty , or else the remove will fail
             * @par After removing:
             * as for the child nodes of the node being removed:
             * - pointers to them will be added to the end of current node's child-nodes list
             * - their parent will be set to current node
             */
            virtual int removeLastChild()
            {
                if(children.isEmpty())
                    return -1;
                linkBase::LinkedList::LinkedList <TreeNode<U>*> xChildren
                        = std::move(children.at(children.len() - 1)->getChildren());
                delete children.at(children.len() - 1);
                children.deleteFrom(children.len() - 1 , 1);
                for (int i = 0; i < xChildren.len(); ++i)
                {
                    xChildren.at(i)->setParent(*this);
                    children.addAfter(children.len() - 1 , xChildren.at(i));
                }
                return 0;
            }
            /**
             * @brief remove the node of specified index in the child-nodes list , just like
             * calling the @link ~TreeNode() destructor @endlink of the specified child-node
             * @param index the specified index
             * @return
             * - if the index doesn't exist , return -1;
             * - or else , return 0
             * @warning the index must exist , or else the remove will fail
             * @par After removing:
             * as for the child nodes of the node being removed:
             * - pointers to them will be added to the end of current node's child-nodes list
             * - their parent will be set to current node
             */
            virtual int removeChildOfIndex(int index)
            {
                if(index < 0 || index >= children.len())
                    return -1;
                linkBase::LinkedList::LinkedList <TreeNode<U>*> xChildren
                        = std::move(children.at(index)->getChildren());
                delete children.at(index);
                children.deleteFrom(index , 1);
                for (int i = 0; i < xChildren.len(); ++i)
                {
                    xChildren.at(i)->setParent(*this);
                    children.addAfter(children.len() - 1 , xChildren.at(i));
                }
                return 0;
            }
            /**
             * @brief remove those child nodes containing the specified data , just like calling
             * the @link ~TreeNode() destructor @endlink of them
             * @param value the specified data
             * @return the number of removed nodes
             * @note if there is no node containing the specified data , this function will do
             * nothing and return 0
             * @par How to compare:
             * - if the type of node's data part is floating-point(float , double , long double)
             * number , use floating-point error (1e-6);
             * - or else , use operator ==
             * @par After removing:
             * as for the child nodes of the node being removed:
             * - pointers to them will be added to the end of current node's child-nodes list
             * - their parent will be set to current node
             */
            virtual int removeChildrenOfData(U const &value)
            {
                int removedNum = 0;
                linkBase::LinkedList::LinkedList <int> rmNodeIndexes =
                        std::move(getChildrenIndexOfData(value));
                for (int i = rmNodeIndexes.len() - 1; i >= 0; --i)
                {
                    removeChildOfIndex(rmNodeIndexes.at(i));
                    removedNum++;
                }
                return removedNum;
            }
            /**
             * @brief remove those child nodes containing the specified data , just like calling
             * the @link ~TreeNode() destructor @endlink of them
             * @param value the specified data
             * @param equal function to judge whether one data is equal to another , which won't
             * change the data objects to be compared
             * @return the number of removed nodes
             * @note if there is no node containing the specified data , this function will do
             * nothing and return 0
             * @par How to compare:
             * call a function using the callable object passed in by the parameter to compare
             * whether the data part of each child node is equal to the specified data:
             * - if equal , the function should return 1
             * - if not equal , the function should return 0
             * - the function should have two formal parameters , the first one is a const lvalue
             * reference bound to type U which means one data object , the second one is a const
             * lvalue reference bound to type U which means another data object
             * @par After removing:
             * as for the child nodes of the node being removed:
             * - pointers to them will be added to the end of current node's child-nodes list
             * - their parent will be set to current node
             */
            virtual int removeChildrenOfData(U const &value , std::function<int(U const & , U
            const &)> equal)
            {
                int removedNum = 0;
                linkBase::LinkedList::LinkedList <int> rmNodeIndexes =
                        std::move(getChildrenIndexOfData(value , equal));
                for (int i = rmNodeIndexes.len() - 1; i >= 0; --i)
                {
                    removeChildOfIndex(rmNodeIndexes.at(i));
                    removedNum++;
                }
                return removedNum;
            }
            /**
             * @brief remove those child nodes containing the specified data , just like calling
             * the @link ~TreeNode() destructor @endlink of them
             * @param value the specified data
             * @param equal function to judge whether one data is equal to another , which will
             * change the data objects to be compared
             * @return the number of removed nodes
             * @note if there is no node containing the specified data , this function will do
             * nothing and return 0
             * @par How to compare:
             * call a function using the callable object passed in by the parameter to compare
             * whether the data part of each child node is equal to the specified data:
             * - if equal , the function should return 1
             * - if not equal , the function should return 0
             * - the function should have two formal parameters , the first one is a lvalue
             * reference bound to type U which means one data object , the second one is a lvalue
             * reference bound to type U which means another data object
             * @par After removing:
             * as for the child nodes of the node being removed:
             * - pointers to them will be added to the end of current node's child-nodes list
             * - their parent will be set to current node
             */
            virtual int removeChildrenOfData(U &value , std::function<int(U & , U &)> equal)
            {
                int removedNum = 0;
                linkBase::LinkedList::LinkedList <int> rmNodeIndexes =
                        std::move(getChildrenIndexOfData(value , equal));
                for (int i = rmNodeIndexes.len() - 1; i >= 0; --i)
                {
                    removeChildOfIndex(rmNodeIndexes.at(i));
                    removedNum++;
                }
                return removedNum;
            }
            /**
             * @brief remove all child nodes , just like calling the @link ~TreeNode() destructor
             * @endlink of them
             * @return the number of removed nodes
             * @note if the child-nodes list is empty , this function will do nothing and return 0
             * @par After removing:
             * as for the child nodes of the node being removed:
             * - pointers to them will be added to the end of current node's child-nodes list
             * - their parent will be set to current node
             */
            virtual int removeAllChild()
            {
                int removedNum = 0;
                for (int i = children.len() - 1; i >= 0; --i)
                {
                    removeChildOfIndex(i);
                    removedNum++;
                }
                return removedNum;
            }
            /**
             * @brief take current node as a tree-root-node , traverse the tree by rows(include
             * the root-node)
             * @param doSomething a function to call when this function traverses each node
             * @par Order:
             * take current node as a tree-root-node , and then place this tree in this way:
             * <ol>
             * <li>root-up
             * <li>among all the child nodes of a node , the child node with least index in the
             * child-nodes list placed in the far left
             * </ol>
             * in that case , this function will traverse all nodes of the tree row by row from
             * up to down while traversing from left to right in a row
             * @par Action:
             * As the function traverses each node , each time it will call the callable object
             * passed in by the parameter. For the callable object passed in by the parameter ,
             * there are the following requirements:
             * -# return void
             * -# the <B>first</B> formal parameter is an lvalue reference bound to a
             * TreeNode&lt;U&gt; , which means the node being traversed currently
             * -# the <B>second</B> formal parameter is a int , which means the index of the row
             * being traversed currently(place the tree as described above , assume that the
             * index of the top row is 0 , and row-index increases downward)
             * -# the <B>third</B> formal parameter is a int , which means the index of the node
             * in the current traversed row(place the tree as described above , number each node
             * in the current traversed row , assume that the node-index of the most-left node is
             * 0 , and node-index increases rightward)
             * - the formal parameter list can be like this:
             * (TreeNode&lt;U&gt; &nowNode , int rowIndex , int nodeIndex)
             */
            virtual void traverseAsTree(std::function<void(TreeNode<U> & , int , int)> doSomething)
            {
                linkBase::Queue::Queue <TreeNode<U>*> row;
                row.push(this);
                int rIndex = -1;
                while(!row.isEmpty())
                {
                    rIndex++;
                    int times = row.len();
                    for (int i = 0; i < times; ++i)
                    {
                        TreeNode<U> *f = row.front();
                        linkBase::LinkedList::LinkedList <TreeNode<U>*> childrenList
                                = std::move(f->getChildren());
                        for (int j = 0; j < childrenList.len(); ++j)
                        {
                            row.push(childrenList.at(j));
                        }
                        doSomething(*f , rIndex , i);
                        row.pop();
                    }
                }
            }
            /**
             * @brief get the depth of current node(the root-depth is 0)
             * @return the depth of current node(the root-depth is 0)
             */
            virtual int depth()
            {
                int depth = 0;
                TreeNode<U> *temp = this;
                while(temp->parent != nullptr)
                {
                    temp = temp->parent;
                    depth++;
                }
                return depth;
            }
            /**
             * @brief get the height of current node(every leaf-node has a height of 0)
             * @return the height of current node(every leaf-node has a height of 0)
             * @note the height of current node is the longest path length between a leaf-node
             * and current node among all leaf-nodes
             */
            virtual int height()
            {
                linkBase::Queue::Queue <TreeNode<U>*> nodeQueue;
                nodeQueue.push(this);
                int height = -1;
                while(!nodeQueue.isEmpty())
                {
                    height++;
                    int times = nodeQueue.len();
                    for (int i = 0; i < times; ++i)
                    {
                        linkBase::LinkedList::LinkedList <TreeNode<U>*> childrenList =
                                std::move(nodeQueue.front()->getChildren());
                        for (int j = 0; j < childrenList.len(); ++j)
                        {
                            nodeQueue.push(childrenList.at(j));
                        }
                        nodeQueue.pop();
                    }
                }
                return height;
            }

        private:
            /**
             * @brief set the parent node of current node to the specified node
             * @param node the specified node
             * @note this function won't add the pointer of current node to the specified node's
             * child-nodes list. Actually, this function will do nothing besides setting current
             * node's parent node to the specified node
             */
            virtual void setParent(TreeNode<U> &node)
            {
                parent = &node;
            }

            /**
             * @brief you can access the private member function of class @link
             * Telephone_DS::treeBase::Tree::Tree::TreeNode TreeNode @endlink in class @link
             * Telephone_DS::treeBase::Tree::Tree Tree @endlink
             * @note this is to prevent users from calling some member functions of @link
             * Telephone_DS::treeBase::Tree::Tree::TreeNode TreeNode @endlink
             */
            friend class Tree;
        };

    public:
        TreeNode<T> root;
    public:
        /**
         * @brief general constructor(copy)
         * @param data data of the root-node
         * @note use copy-constructor of type T to copy the data to the root-node
         * @par init
         * - root = a new node containing specified data with null parent-pointer and empty
         * child-nodes list
         */
        explicit Tree(T const &data)
                : root(data)
        {}
        /**
         * @brief general constructor(move)
         * @param data data of the root-node
         * @note use move-constructor of type T to move the data to the root-node
         * @par init
         * - root = a new node containing specified data with null parent-pointer and empty
         * child-nodes list
         */
        explicit Tree(T &&data)
                : root(std::move(data))
        {}
        /**
         * @brief copy-constructor
         * @param src
         * @note use copy-constructor of type T to copy data of all nodes from the tree passed in
         * by parameter to current tree
         * @par Result:
         * current tree will have a same struct of nodes as the tree passed in by parameter , and
         * the nodes of current tree will contain the same data as the nodes of the tree passed
         * in by parameter
         */
        Tree(Tree<T> const &src)
                : root(src.root.data)
        {
            linkBase::Queue::Queue<TreeNode<T>*> row;
            row.push(&root);
            src.root.traverseAsTree(
                    [&]
                            (TreeNode<T> &nowNode, int rowIndex, int nodeIndex)
                    {
                        if (nowNode.isLeaf())
                        {
                            row.pop();
                            return;
                        }
                        linkBase::LinkedList::LinkedList<TreeNode<T> *> childrenList =
                                std::move(nowNode.getChildren());
                        TreeNode<T> *t = row.front();
                        for (int i = 0; i < childrenList.len(); ++i)
                        {
                            t->addChildWithData(childrenList.at(i)->data);
                            row.push(t->getLastChild());
                        }
                        row.pop();
                    });
        }
        /**
         * @brief move-constructor
         * @param src
         * @par To Do List:
         * this function will do the following things:
         * -# use move-constructor of type T to move the data from the root-node of the tree
         * passed in by parameter to current tree's root-node
         * -# set the parent pointer of current tree's root-node to nullptr
         * -# use move-assignment of type @link Telephone_DS::linkBase::LinkedList::LinkedList
         * list @endlink to move the child-nodes list of root-node from the tree passed in by
         * parameter to current tree
         * -# set the parent of all child nodes in current root-node's child-nodes list to null
         * @par Result:
         * current tree will have a same struct of nodes as the tree passed in by parameter , and
         * the nodes of current tree will contain the same data as the nodes of the tree passed
         * in by parameter
         */
        Tree(Tree<T> &&src) noexcept
                : root(std::move(src.root.data))
        {
            root.children = std::move(src.root.children);
            for (int i = 0; i < root.children.len(); ++i)
            {
                root.children.at(i)->setParent(root);
            }
        }
        /**
         * @brief copy-assignment
         * @param right
         * @return left reference of the tree being assigned
         * @par To Do List:
         * -# call @link Telephone_DS::treeBase::Tree::Tree::TreeNode::~TreeNode destructor
         * @endlink of each node of current tree except the root-node
         * -# reset the child-nodes list of current tree's root-node to empty @link
         * Telephone_DS::linkBase::LinkedList::LinkedList list @endlink
         * -# use copy-assignment of type T to copy data from the root-node of the tree passed in
         * by parameter to current tree's root-node
         * -# build the current tree according to the tree passed in by parameter<B>(</B>use
         * copy-constructor of type T to copy data from the nodes of the tree passed in by
         * parameter to current tree's nodes<B>)</B>
         * @par Result:
         * current tree will have a same struct of nodes as the tree passed in by parameter , and
         * the nodes of current tree will contain the same data as the nodes of the tree passed
         * in by parameter
         */
        Tree<T> &operator=(Tree<T> const &right)
        {
            if(this == &right)
                return *this;
            /* ==================================== destruct ==================================== */
            linkBase::LinkedList::LinkedList <TreeNode<T>*> freeList =
                    std::move(root.getAllNodes());
            for (int i = 1; i < freeList.len(); ++i)
            {
                delete freeList.at(i);
            }
            /* ==================================== destruct ==================================== */
            root.children.deleteFrom(0 , root.children.len());
            root.data = right.root.data;
            linkBase::Queue::Queue<TreeNode<T>*> row;
            row.push(&root);
            right.root.traverseAsTree(
                    [&]
                            (TreeNode<T> &nowNode, int rowIndex, int nodeIndex)
                    {
                        if (nowNode.isLeaf())
                        {
                            row.pop();
                            return;
                        }
                        linkBase::LinkedList::LinkedList<TreeNode<T> *> childrenList =
                                std::move(nowNode.getChildren());
                        TreeNode<T> *t = row.front();
                        for (int i = 0; i < childrenList.len(); ++i)
                        {
                            t->addChildWithData(childrenList.at(i)->data);
                            row.push(t->getLastChild());
                        }
                        row.pop();
                    });
            return *this;
        }
        /**
         * @brief move-assignment
         * @param right
         * @return left reference of the tree being assigned
         * @par To Do List:
         * -# call @link Telephone_DS::treeBase::Tree::Tree::TreeNode::~TreeNode destructor
         * @endlink of each node of current tree except the root-node
         * -# reset the child-nodes list of current tree's root-node to empty @link
         * Telephone_DS::linkBase::LinkedList::LinkedList list @endlink
         * -# use move-assignment of type T to move data from the root-node of the tree passed in
         * by parameter to current tree's root-node
         * -# use move-assignment of type @link Telephone_DS::linkBase::LinkedList::LinkedList
         * list @endlink to move the child-nodes list of root-node from the tree passed in by
         * parameter to current tree
         * -# set the parent of all child nodes in current root-node's child-nodes list to null
         * @par Result:
         * current tree will have a same struct of nodes as the tree passed in by parameter , and
         * the nodes of current tree will contain the same data as the nodes of the tree passed
         * in by parameter
         */
        Tree<T> &operator=(Tree<T> &&right) noexcept
        {
            /* ==================================== destruct ==================================== */
            linkBase::LinkedList::LinkedList <TreeNode<T>*> freeList =
                    std::move(root.getAllNodes());
            for (int i = 1; i < freeList.len(); ++i)
            {
                delete freeList.at(i);
            }
            /* ==================================== destruct ==================================== */
            root.children.deleteFrom(0 , root.children.len());
            root.data = std::move(right.root.data);
            root.children = std::move(right.root.children);
            for (int j = 0; j < root.children.len(); ++j)
            {
                root.children.at(j)->setParent(root);
            }
            return *this;
        }
        /**
         * @brief destructor
         * @par To Do List:
         * call @link Telephone_DS::treeBase::Tree::Tree::TreeNode::~TreeNode destructor
         * @endlink of each node of current tree
         */
        virtual ~Tree()
        {
            linkBase::LinkedList::LinkedList <TreeNode<T>*> freeList
                    = std::move(root.getAllNodes());
            for (int i = 1; i < freeList.len(); ++i)
            {
                delete freeList.at(i);
            }
        }
        /**
         * @brief get the depth as well as the height of current tree
         * @return the depth as well as the height of current tree
         * @note for a tree , its depth equals its height , which is also the height of its
         * root-node
         */
        virtual int depthAndHeight()
        {
            return root.height();
        }
        /**
         * @brief get all leaf-nodes of current tree
         * @return a @link Telephone_DS::linkBase::LinkedList::LinkedList list @endlink of
         * pointers to each leaf-node
         * @par Order:
         * place current tree in this way:
         * <ol>
         * <li>root-up
         * <li>among all the child nodes of a node , the child node with least index in the
         * child-nodes list placed in the far left
         * </ol>
         * in this case , the order of the leaf-nodes in the returned list is: up-to-down and
         * left-to-right
         */
        virtual auto getLeaves() -> linkBase::LinkedList::LinkedList <TreeNode<T>*>
        {
            return std::move(root.getLeafNodes());
        }
        /**
         * @brief traverse current tree and then find the nodes of current tree containing
         * specified data(include the root-node)
         * @param data the specified data
         * @return a @link Telephone_DS::linkBase::LinkedList::LinkedList list @endlink of
         * pointers to nodes of current tree containing the specified data
         * @par How to compare:
         * - if type T is floating-point(float , double , long double) number , use
         * floating-point error (1e-6);
         * - or else , use operator ==
         * @par Order:
         * place current tree in this way:
         * <ol>
         * <li>root-up
         * <li>among all the child nodes of a node , the child node with least index in the
         * child-nodes list placed in the far left
         * </ol>
         * in this case , the order of the nodes in the returned list is: up-to-down and
         * left-to-right
         */
        virtual auto findNodes(T const &data) -> linkBase::LinkedList::LinkedList <TreeNode<T>*>
        {
            linkBase::LinkedList::LinkedList <TreeNode<T>*> res;
            if(typeid(T) == typeid(float) || typeid(T) == typeid(double)
               || typeid(T) == typeid(long double))
            {
                root.traverseAsTree(
                        [&]
                                (TreeNode<T> &nowNode, int rowIndex, int nodeIndex)
                        {
                            if (std::fabs(nowNode.data - data) <= 1e-6)
                            {
                                res.addAfter(res.len() - 1, &nowNode);
                            }
                        });
            } else
            {
                root.traverseAsTree(
                        [&]
                                (TreeNode<T> &nowNode, int rowIndex, int nodeIndex)
                        {
                            if (nowNode.data == data)
                            {
                                res.addAfter(res.len() - 1, &nowNode);
                            }
                        });
            }
            return std::move(res);
        }
        /**
         * @brief traverse current tree and then find the nodes of current tree containing
         * specified data(include the root-node)
         * @param data the specified data
         * @param equal function to judge whether one data is equal to another , which won't
         * change the data objects to be compared
         * @return a @link Telephone_DS::linkBase::LinkedList::LinkedList list @endlink of
         * pointers to nodes of current tree containing the specified data
         * @par How to compare:
         * call a function using the callable object passed in by the parameter to compare
         * whether the data part of each node is equal to the specified data:
         * - if equal , the function should return 1
         * - if not equal , the function should return 0
         * - the function should have two formal parameters , the first one is a const lvalue
         * reference bound to type T which means one data object , the second one is a const
         * lvalue reference bound to type T which means another data object
         * @par Order:
         * place current tree in this way:
         * <ol>
         * <li>root-up
         * <li>among all the child nodes of a node , the child node with least index in the
         * child-nodes list placed in the far left
         * </ol>
         * in this case , the order of the nodes in the returned list is: up-to-down and
         * left-to-right
         */
        virtual auto findNodes(T const &data , std::function<int(T const & , T const &)> equal)
        -> linkBase::LinkedList::LinkedList <TreeNode<T>*>
        {
            linkBase::LinkedList::LinkedList <TreeNode<T>*> res;
            root.traverseAsTree(
                    [&]
                            (TreeNode<T> &nowNode, int rowIndex, int nodeIndex)
                    {
                        if (equal(data, nowNode.data))
                        {
                            res.addAfter(res.len() - 1, &nowNode);
                        }
                    });
            return std::move(res);
        }
        /**
         * @brief traverse current tree and then find the nodes of current tree containing
         * specified data(include the root-node)
         * @param data the specified data
         * @param equal function to judge whether one data is equal to another , which will
         * change the data objects to be compared
         * @return a @link Telephone_DS::linkBase::LinkedList::LinkedList list @endlink of
         * pointers to nodes of current tree containing the specified data
         * @par How to compare:
         * call a function using the callable object passed in by the parameter to compare
         * whether the data part of each node is equal to the specified data:
         * - if equal , the function should return 1
         * - if not equal , the function should return 0
         * - the function should have two formal parameters , the first one is a lvalue reference
         * bound to type T which means one data object , the second one is a lvalue reference
         * bound to type T which means another data object
         * @par Order:
         * place current tree in this way:
         * <ol>
         * <li>root-up
         * <li>among all the child nodes of a node , the child node with least index in the
         * child-nodes list placed in the far left
         * </ol>
         * in this case , the order of the nodes in the returned list is: up-to-down and
         * left-to-right
         */
        virtual auto findNodes(T &data , std::function<int(T & , T &)> equal) ->
        linkBase::LinkedList::LinkedList <TreeNode<T>*>
        {
            linkBase::LinkedList::LinkedList <TreeNode<T>*> res;
            root.traverseAsTree(
                    [&]
                            (TreeNode<T> &nowNode, int rowIndex, int nodeIndex)
                    {
                        if (equal(data, nowNode.data))
                        {
                            res.addAfter(res.len() - 1, &nowNode);
                        }
                    });
            return std::move(res);
        }
        /**
         * @brief call the findNodes() function and get the first node in its returned @link
         * Telephone_DS::linkBase::LinkedList::LinkedList list @endlink
         * @param data the specified data
         * @return
         * - if the returned @link Telephone_DS::linkBase::LinkedList::LinkedList list @endlink
         * is not empty , return a pointer which is actually the item of index 0 in the list
         * - or else , return nullptr
         */
        virtual auto findNode(T const &data) -> TreeNode<T>*
        {
            linkBase::LinkedList::LinkedList<TreeNode<T>*> res = std::move(findNodes(data));
            if(res.isEmpty())
                return nullptr;
            return res.at(0);
        }
        /**
         * @brief call the findNodes() function and get the first node in its returned @link
         * Telephone_DS::linkBase::LinkedList::LinkedList list @endlink
         * @param data the specified data
         * @param equal function to judge whether one data is equal to another , which won't
         * change the data objects to be compared
         * @return
         * - if the returned @link Telephone_DS::linkBase::LinkedList::LinkedList list @endlink
         * is not empty , return a pointer which is actually the item of index 0 in the list
         * - or else , return nullptr
         */
        virtual auto findNode(T const &data , std::function<int(T const & , T const &)> equal) ->
        TreeNode<T>*
        {
            linkBase::LinkedList::LinkedList<TreeNode<T>*> res = std::move(findNodes(data , equal));
            if(res.isEmpty())
                return nullptr;
            return res.at(0);
        }
        /**
         * @brief call the findNodes() function and get the first node in its returned @link
         * Telephone_DS::linkBase::LinkedList::LinkedList list @endlink
         * @param data the specified data
         * @param equal function to judge whether one data is equal to another , which will
         * change the data objects to be compared
         * @return
         * - if the returned @link Telephone_DS::linkBase::LinkedList::LinkedList list @endlink
         * is not empty , return a pointer which is actually the item of index 0 in the list
         * - or else , return nullptr
         */
        virtual auto findNode(T &data , std::function<int(T & , T &)> equal) -> TreeNode<T>*
        {
            linkBase::LinkedList::LinkedList<TreeNode<T>*> res = std::move(findNodes(data , equal));
            if(res.isEmpty())
                return nullptr;
            return res.at(0);
        }
    };
}

#endif //TREE_TREE_H
