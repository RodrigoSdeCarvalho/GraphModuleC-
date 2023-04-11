#ifndef HeapNode_h
#define HeapNode_h

#include <iostream>
#include <vector>
#include <random>

using namespace std;

namespace GraphModule
{
    class Node;

    class HeapNode
    {
        public:
            int key; // All attributes are public because they can be both read and written.
            Node* node;
            int priority;

            HeapNode(int key, Node* node, int priority);
            
            int getParent();
            int getLeft();
            int getRight();

            bool operator >(const HeapNode& other);
            bool operator >(int x);
            bool operator <(const HeapNode& other);
            bool operator <(int x);
            bool operator <=(const HeapNode& other);
            bool operator <=(int x);
            bool operator >=(const HeapNode& other);
            bool operator >=(int x);
            bool operator ==(const HeapNode& other);
            bool operator !=(const HeapNode& other);

            ~HeapNode();
    };
}

#endif
