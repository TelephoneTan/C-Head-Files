//
// Created by Telephone on 2019/12/29 0029.
//

#ifndef TREE_TREE_H
#define TREE_TREE_H

#include <LinkedList.h>
#include <cstring>
#include <utility>
#include <LQueue.h>
#include <LStack.h>
#include <cmath>

namespace Telephone_DS::treeBase::Tree
{
    template <typename T> class Tree
    {
    private:
        template <typename U> class TreeNode
        {
        public:
            U data;
        private:
            TreeNode<U> *parent = nullptr;
            linkBase::LinkedList::LinkedList<TreeNode<U>*> children;
        public:
            explicit TreeNode(U const &d)                                   //general constructor(copy)
                    : data(d)
            {}
            explicit TreeNode(U &&d)                                        //general constructor(move)
                    : data(std::move(d))
            {}
            TreeNode(TreeNode<U> const &src)                                //copy-constructor
                    : data(src.data),parent(src.parent),children(src.children)
            {}
            TreeNode(TreeNode<U> &&src) noexcept                            //move-constructor
                    : data(std::move(src.data)),parent(src.parent),children(std::move(src.children))
            {}
            TreeNode<U> &operator=(TreeNode<U> const &right)                //copy-assignment
            {
                if(this == &right)
                    return *this;
                data = right.data;
                parent = right.parent;
                children = right.children;
                return *this;
            }
            TreeNode<U> &operator=(TreeNode<U> &&right) noexcept            //move-assignment
            {
                data = std::move(right.data);
                parent = right.parent;
                children = std::move(right.children);
                return *this;
            }
            virtual ~TreeNode() = default;                                  //destructor
            virtual auto getChildren() -> linkBase::LinkedList::LinkedList<TreeNode<U>*>
            {   /* Tip:
                 * changing the returned value won't effect the tree node , but the tree node's child
                 * nodes can be effected if you use the pointers in the returned list
                 * */
                return children;
            }
            virtual auto getChildrenOfData(U const &value) ->
            linkBase::LinkedList::LinkedList<TreeNode<U>*>
            {   /* @return a list containing pointers to child nodes which have the same data , the
                 * order of return nodes is as same as the origin order of children-nodes
                 *
                 * how to compare:
                 * if the type of data is @floating-point(float , double , long double) number ,
                 * use floating-point error (1e-6);
                 * or else , use operator !=
                 *
                 * Tip:
                 * changing the returned value won't effect the tree node , but the tree node's child
                 * nodes can be effected if you use the pointers in the returned list
                 * */
                linkBase::LinkedList::LinkedList<TreeNode<U>*> res = children;
                int delIndex[res.len()];
                std::memset(delIndex , -1 , sizeof(int) * res.len());
                int delIndexP = 0;
                if(typeid(U) != typeid(double) && typeid(U) != typeid(float)
                   && typeid(U) != typeid(long double))
                {
                    for (int i = res.len() - 1; i >= 0; --i)
                    {
                        if(res.at(i)->data != value)
                        {
                            delIndex[delIndexP] = i;
                            delIndexP++;
                        }
                    }
                } else
                {
                    for (int i = res.len() - 1; i >= 0; --i)
                    {
                        
                        if(std::fabs(res.at(i)->data - value) > 1e-6)
                        {
                            delIndex[delIndexP] = i;
                            delIndexP++;
                        }
                    }
                }
                for (auto i : delIndex)
                {
                    if (i == -1)
                        break;
                    res.deleteFrom(i , 1);
                }
                return std::move(res);
            }
            virtual auto getParent() -> TreeNode<U>*
            {   /* Tip:
                 * changing the returned value won't effect the tree node , but the tree node's parent
                 * node can be effected if you use the returned pointer
                 * */
                return parent;
            }
            virtual auto getChildOfIndex(int index) -> TreeNode<U>*
            {   /* return a pointer to the child node of specified index in the children list
                 *
                 * Warning:
                 * the index must exist , or else this function will return a nullptr
                 *
                 * @return:
                 * return a nonnull pointer if the index exists;
                 * or else , return nullptr
                 * */
                TreeNode<U> *res = nullptr;
                if(index >= 0 && index < children.len())
                {
                    res = children.at(index);
                }
                return res;
            }
            virtual void addChild(TreeNode<U> const &node)
            {   /* add a child node to the end of the children list*/
                children.addAfter(children.len() - 1 , &node);
            }
            virtual void addChildWithData(U const &dat)
            {   /* add a new child node with specified data to the end of children list*/
                children.addAfter(children.len() - 1 , new TreeNode(dat));
                children.at(children.len() - 1)->setParent(*this);
            }
            virtual void addChildWithData(U &&dat)
            {   /* add a new child node with specified data to the end of children list*/
                children.addAfter(children.len() - 1 , new TreeNode(std::move(dat)));
                children.at(children.len() - 1)->setParent(*this);
            }
            virtual int insertChildBefore(int index , TreeNode<U> const &node)
            {   /* insert a child node before the child node of the specified index
                 *
                 * Warning:
                 * the index must exist , or else the insertion will fail
                 *
                 * @return:
                 * return -1 if the index doesn't exist;
                 * or else , return 0
                 * */
                if(index < 0 || index >= children.len())
                    return -1;
                children.addBefore(index , &node);
                return 0;
            }
            virtual int childNum()
            {   /* @return:
                 * return the number of child nodes
                 *
                 * Tip:
                 * changing the returned value won't effect the tree node
                 * */
                return children.len();
            }
            virtual int removeFirstChild()
            {   /* remove the first child node in the children list
                 *
                 * Warning:
                 * the children list must be not empty , or else the remove will fail
                 *
                 * @return:
                 * return -1 if the children list is empty;
                 * or else , return 0
                 * */
                if(children.isEmpty())
                    return -1;
                children.deleteFrom(0 , 1);
                return 0;
            }
            virtual int removeLastChild()
            {   /* remove the last child node in the children list
                 *
                 * Warning:
                 * the children list must be not empty , or else the remove will fail
                 *
                 * @return:
                 * return -1 if the children list is empty;
                 * or else , return 0
                 * */
                if(children.isEmpty())
                    return -1;
                children.deleteFrom(children.len() - 1 , 1);
                return 0;
            }
            virtual int removeChildOfIndex(int index)
            {   /* remove the child node of specified index in the children list
                 *
                 * Warning:
                 * the index must exist , or else the remove will fail
                 *
                 * @return:
                 * return -1 if the index doesn't exist;
                 * or else , return 0
                 * */
                if(index < 0 || index >= children.len())
                    return -1;
                children.deleteFrom(index , 1);
                return 0;
            }
            virtual void removeChildOfData(U const &value)
            {   /* remove the child nodes containing the specified data in the children list
                 *
                 * how to compare:
                 * if the type of data is @floating-point(float , double , long double) number , use
                 * floating-point error (1e-6);
                 * or else , use operator ==
                 * */
                int delIndex[children.len()];
                std::memset(delIndex , -1 , sizeof(int) * children.len());
                int delIndexP = 0;
                if(typeid(U) != typeid(double) && typeid(U) != typeid(float)
                   && typeid(U) != typeid(long double))
                {
                    for (int i = children.len() - 1; i >= 0; --i)
                    {
                        if(children.at(i)->data == value)
                        {
                            delIndex[delIndexP] = i;
                            delIndexP++;
                        }
                    }
                } else
                {
                    for (int i = children.len() - 1; i >= 0; --i)
                    {
                        
                        if(std::fabs(children.at(i)->data - value) <= 1e-6)
                        {
                            delIndex[delIndexP] = i;
                            delIndexP++;
                        }
                    }
                }
                for (auto i : delIndex)
                {
                    if (i == -1)
                        break;
                    children.deleteFrom(i , 1);
                }
            }
            virtual void removeAllChild()
            {   /* remove all child nodes in the children list*/
                if(children.isEmpty())
                    return;
                children.deleteFrom(0 , children.len());
            }
            virtual void setParent(TreeNode<U> const &node)
            {
                parent = &node;
            }
            virtual int setChildOfIndex(int index , TreeNode<U> const &node)
            {   /* change the child node of specified index(make the pointer point to a new node)
                 *
                 * Warning:
                 * the index must exist , or else the change will fail
                 *
                 * @return:
                 * return -1 if the index doesn't exist;
                 * or else , return 0
                 * */
                if(index < 0 || index >= children.len())
                    return -1;
                children.at(index) = &node;
                return 0;
            }
            virtual int setFirstChild(TreeNode<U> const &node)
            {   /* change the first child node in the children list
                 * (make the pointer point to a new node)
                 *
                 * Warning:
                 * the children list must be not empty , or else the change will fail
                 *
                 * @return:
                 * return -1 if the children list is empty;
                 * or else , return 0
                 * */
                if(children.isEmpty())
                    return -1;
                children.at(0) = &node;
                return 0;
            }
            virtual int setLastChild(TreeNode<U> const &node)
            {   /* change the last child node in the children list
                 * (make the pointer point to a new node)
                 *
                 * Warning:
                 * the children list must be not empty , or else the change will fail
                 *
                 * @return:
                 * return -1 if the children list is empty;
                 * or else , return 0
                 * */
                if(children.isEmpty())
                    return -1;
                children.at(children.len()) = &node;
                return 0;
            }
            virtual void setChildrenList(TreeNode<U> const &node)
            {   /* use another node's children list to replace tree node's children list*/
                children = node.children;
            }
            virtual void setChildrenList(TreeNode<U> &&node)
            {   /* use another node's children list to replace tree node's children list*/
                children = std::move(node.children);
            }
            virtual int depth()
            {   /* return the depth of the tree node , the root-depth is 0*/
                int depth = 0;
                TreeNode<U> *temp = this;
                while(temp->parent != nullptr)
                {
                    temp = temp->parent;
                    depth++;
                }
                return depth;
            }
            virtual int height()
            {   /* return the height of the tree node , every leaf-node has a height of 0*/
                linkBase::Queue::Queue <TreeNode<U>*> nodeQueue;
                nodeQueue.push(this);
                int height = 0;
                while(true)
                {
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
                    if(nodeQueue.isEmpty())
                        break;
                    height++;
                }
                return height;
            }
            virtual int isLeaf()
            {   /* @return:
                 * return 1(true) if the tree node is a leaf node;
                 * or else , return 0(false)
                 * */
                return children.isEmpty();
            }
            virtual auto getLeafNodes() -> linkBase::LinkedList::LinkedList <TreeNode<U>*>
            {   /* return a list containing all leaf nodes , the order of nodes in the list is:
                 * (place the tree root-up)
                 * up-to-down and left-to-right
                 * */
                linkBase::Queue::Queue <TreeNode<U>*> nodes;
                linkBase::LinkedList::LinkedList <TreeNode<U>*> leaves;
                nodes.push(this);
                while(!nodes.isEmpty())
                {
                    int times = nodes.len();
                    for (int i = 0; i < times; ++i)
                    {
                        if(nodes.front()->isLeaf())
                        {
                            leaves.addAfter(leaves.len() - 1 , std::move(nodes.front()));
                            nodes.pop();
                        } else
                        {
                            linkBase::LinkedList::LinkedList <TreeNode<U>*> childrenTemp
                                    = std::move(nodes.front()->getChildren());
                            for (int j = 0; j < childrenTemp.len(); ++j)
                            {
                                nodes.push(childrenTemp.at(j));
                            }
                            nodes.pop();
                        }
                    }
                }
                return std::move(leaves);
            }
            virtual auto getAllNodes() -> linkBase::LinkedList::LinkedList <TreeNode<U>*>
            {   /* return a list containing all nodes derived(both directly and indirectly) from
                 * the tree node
                 *
                 * Tip:
                 * 1. the tree node itself will be included in the list as well
                 * 2. the order of the returned list is:
                 *        (place the tree root-up)
                 *    row by row , up-to-down , left-to-right
                 * */
                linkBase::Stack::Stack <TreeNode<U>*> res;
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
                        res.push(f);
                        row.pop();
                    }
                }
                return std::move(res);
            }
        };
    
    private:
        TreeNode<T> root;
    public:
        explicit Tree(T const &data)
                : root(data)
        {}
        explicit Tree(T &&data)
                : root(std::move(data))
        {}
        Tree(Tree<T> const &src)
                : root(src.root)
        {
            linkBase::Queue::Queue <TreeNode<T>*> queue;
            queue.push(&root);
            while(!queue.isEmpty())
            {
                int times = queue.len();
                for (int i = 0; i < times; ++i)
                {
                    TreeNode<T> *f = queue.front();
                    if(!f->isLeaf())
                    {
                        linkBase::LinkedList::LinkedList <TreeNode<T>*> childrenList
                                = std::move(f->getChildren());
                        for (int j = 0; j < childrenList.len(); ++j)
                        {
                            f->setChildOfIndex(j , *(new TreeNode<T>(*(childrenList.at(j)))));
                            *(f->getChildOfIndex(j))->setParent(*f);
                            queue.push(f->getChildOfIndex(j));
                        }
                    }
                    queue.pop();
                }
            }
        }
        Tree(Tree<T> &&src) noexcept
                : root(std::move(src.root))
        {
            /* After using the move-constructor of TreeNode to construct the root node , the root
             * node of @src will have an empty children list and a null parent pointer , in which
             * case all pointers in @src have been set to nullptr and there is nothing to do
             * */
        }
        Tree<T> &operator=(Tree<T> const &right)
        {
            if(this != &right)
            {
                /* ==================================== destruct ==================================== */
                linkBase::LinkedList::LinkedList <TreeNode<T>*> freeList
                        = std::move(root.getAllNodes());
                for (int i = 1; i < freeList.len(); ++i)
                {
                    delete freeList.at(i);
                }
                /* ==================================== destruct ==================================== */
                root = right.root;
                linkBase::Queue::Queue <TreeNode<T>*> queue;
                queue.push(&root);
                while(!queue.isEmpty())
                {
                    int times = queue.len();
                    for (int i = 0; i < times; ++i)
                    {
                        TreeNode<T> *f = queue.front();
                        if(!f->isLeaf())
                        {
                            linkBase::LinkedList::LinkedList <TreeNode<T>*> childrenList
                                    = std::move(f->getChildren());
                            for (int j = 0; j < childrenList.len(); ++j)
                            {
                                f->setChildOfIndex(j , *(new TreeNode<T>(*(childrenList.at(j)))));
                                *(f->getChildOfIndex(j))->setParent(*f);
                                queue.push(f->getChildOfIndex(j));
                            }
                        }
                        queue.pop();
                    }
                }
            }
            return *this;
        }
        Tree<T> &operator=(Tree<T> &&right) noexcept
        {
            /* ==================================== destruct ==================================== */
            linkBase::LinkedList::LinkedList <TreeNode<T>*> freeList
                    = std::move(root.getAllNodes());
            for (int i = 1; i < freeList.len(); ++i)
            {
                delete freeList.at(i);
            }
            /* ==================================== destruct ==================================== */
            root = std::move(right.root);
            return *this;
        }
        virtual ~Tree()
        {
            linkBase::LinkedList::LinkedList <TreeNode<T>*> freeList
                    = std::move(root.getAllNodes());
            for (int i = 1; i < freeList.len(); ++i)
            {
                delete freeList.at(i);
            }
        }
        virtual int depthAndHeight()
        {   /* return the depth(also the height) of the tree
             *
             * Tip:
             * for a tree , its depth equals its height , that is the height of the root-node
             * */
            return root.height();
        }
        virtual auto leaves() -> linkBase::LinkedList::LinkedList <TreeNode<T>*>
        {
            return std::move(root.getLeafNodes());
        }
        virtual auto node(std::initializer_list <const T&> path) -> TreeNode<T>*
        {   /* find a node according to specified path
             *
             * @return:
             * if the path exist , return a pointer to the found node;
             * or else , return a null pointer
             *
             * @parameter:
             * from left to right , pass in the data of the nodes that make up the path
             * (including the sought node and the root-node)
             *
             * Warning:
             * the data of the nodes of the tree must not be duplicate
             *
             * how to compare:
             * if the type of data is @floating-point(float , double , long double) number , use
             * floating-point error (1e-6);
             * or else , use operator !=/==
             * */
            TreeNode<T> *res = nullptr;
            if(path.size() == 0)
                return res;
            if(typeid(T) == typeid(float) || typeid(T) == typeid(double)
               || typeid(T) == typeid(long double))
            {
                if(std::fabs(*path.begin() - root.data) > 1e-6)
                {
                    return res;
                }
            } else
            {
                if(*path.begin() != root.data)
                {
                    return res;
                }
            }
            res = &root;
            for (auto beg = path.begin() + 1 , end = path.end() ; beg != end ; beg++)
            {
                linkBase::LinkedList::LinkedList <TreeNode<T>*> found
                        = std::move(res->getChildrenOfData(*beg));
                if(found.isEmpty())
                    return nullptr;
                res = found.at(0);
            }
            return res;
        }
        virtual auto findNodes(T const &data) -> linkBase::LinkedList::LinkedList <TreeNode<T>*>
        {   /* return a list consisting of nodes containing specified data(including the root node)
             *
             * Tip:
             * the order of nodes in the returned list is:
             *  (place the tree root-up)
             * up-to-down , left-to-right
             *
             * how to compare:
             * if the type of data is @floating-point(float , double , long double) number , use
             * floating-point error (1e-6);
             * or else , use operator !=/==
             * */
            linkBase::Queue::Queue <TreeNode<T>*> row;
            linkBase::LinkedList::LinkedList <TreeNode<T>*> res;
            row.push(&root);
            while(!row.isEmpty())
            {
                int times = row.len();
                for (int i = 0; i < times; ++i)
                {
                    TreeNode<T> *f = row.front();
                    if(typeid(T) == typeid(float) || typeid(T) == typeid(double)
                       || typeid(T) == typeid(long double))
                    {
                        if(std::fabs(f->data - data) <= 1e-6)
                        {
                            res.addAfter(res.len() - 1 , f);
                        }
                    } else
                    {
                        if(f->data == data)
                        {
                            res.addAfter(res.len() - 1 , f);
                        }
                    }
                    if(!f->isLeaf())
                    {
                        linkBase::LinkedList::LinkedList <TreeNode<T>*> childrenList
                            = std::move(f->getChildren());
                        for (int j = 0; j < childrenList.len(); ++j)
                        {
                            row.push(childrenList.at(j));
                        }
                    }
                    row.pop();
                }
            }
            return std::move(res);
        }
        virtual auto findNode(T const &data) -> TreeNode<T>*
        {   /* return the first node containing specified data
             *
             * @return:
             * if the node found , return a pointer to it;
             * or else , return a null pointer
             *
             * Tip:
             * 1. the searching scope includes the root node
             * 2. the order of search is:
             *        (place the tree root-up)
             *    row by row , up-to-down , left-to-right
             *
             * how to compare:
             * if the type of data is @floating-point(float , double , long double) number , use
             * floating-point error (1e-6);
             * or else , use operator ==
             * */
            linkBase::LinkedList::LinkedList <TreeNode<T>*> allNodes
                = std::move(root.getAllNodes());
            for (int i = 0; i < allNodes.len(); ++i)
            {
                TreeNode<T> *node = allNodes.at(i);
                if(typeid(T) == typeid(float) || typeid(T) == typeid(double)
                   || typeid(T) == typeid(long double))
                {
                    if(std::fabs(node->data - data) <= 1e-6)
                    {
                        return node;
                    }
                } else
                {
                    if(node->data == data)
                    {
                        return node;
                    }
                }
            }
            return nullptr;
        }
    };
}

#endif //TREE_TREE_H
