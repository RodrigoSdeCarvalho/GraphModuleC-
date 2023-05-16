#ifndef HeapNode_h
#define HeapNode_h

#include <iostream>
#include <vector>
#include <random>
#include <memory>

using namespace std;

namespace GraphModule
{
    class Node;

    class HeapNode
    {
        public:
            int key; // All attributes are public because they can be both read and written.
            shared_ptr<Node> node;
            int priority;

            HeapNode(int key, shared_ptr<Node> node, int priority);
            
            int getParent();
            int getLeft();
            int getRight();

            bool operator >(const HeapNode& other) const;
            bool operator >(int x) const;
            bool operator <(const HeapNode& other) const;
            bool operator <(int x) const;
            bool operator <=(const HeapNode& other) const;
            bool operator <=(int x) const;
            bool operator >=(const HeapNode& other) const;
            bool operator >=(int x) const;
            bool operator ==(const HeapNode& other) const;
            bool operator !=(const HeapNode& other) const;

            ~HeapNode();
    };
}

#endif
