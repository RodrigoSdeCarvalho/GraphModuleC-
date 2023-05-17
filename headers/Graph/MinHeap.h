#ifndef MinHeap_h
#define MinHeap_h

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

namespace GraphModule
{
    class HeapNode;
    class Node;

    class MinHeap
    {
        public:
            MinHeap();

            void insert(const shared_ptr<Node>& node, int priority);

            int minPriority();

            shared_ptr<Node> popMin();

            int size() const;

            bool contains(const shared_ptr<Node>& node);

            void updatePriority(const shared_ptr<Node>& node, int priority);

            int getIndexOfHeapNode(const shared_ptr<HeapNode>& heapNode);

            void updatePriority(int nodeKey, int priority);

            ~MinHeap();

            vector<shared_ptr<HeapNode>> heapNodes;
        private:

            void heapifyUp(const shared_ptr<HeapNode>& heapNode);
            void heapifyDown(const shared_ptr<HeapNode>& heapNode);
            void swap(const shared_ptr<HeapNode>& heapNode1, const shared_ptr<HeapNode>& heapNode2);
    };
}

#endif
