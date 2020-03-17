#include <ArrayStorage.h>
#include <LinkedList.h>
#include <LQueue.h>
#include <LStack.h>
#include <Stack.h>
#include <Queue.h>
#include <Tree.h>
#include <cstdio>

int main()
{
    Telephone_DS::treeBase::Tree::Tree <int> tree(0);
    Telephone_DS::linkBase::LinkedList::LinkedList <int> list;
    Telephone_DS::linkBase::Stack::Stack <int> stack;
    Telephone_DS::linkBase::Queue::Queue <int> queue;
    Telephone_DS::arrayBase::ArrayStorage::ArrayStorage <int> arrayList;
    Telephone_DS::arrayBase::Stack::Stack <int> arrayStack;
    Telephone_DS::arrayBase::Queue::Queue <int> arrayQueue;

    std::printf("\nWelcome to Telephone's Data Structure\n\n");
    return 0;
}