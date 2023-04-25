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
            MinHeap(vector<shared_ptr<HeapNode>> heapNodes);

            void insert(shared_ptr<Node> node, int priority);

            int minPriority();

            shared_ptr<Node> popMin();

            int size();

            bool contains(shared_ptr<Node> node);

            void updatePriority(shared_ptr<Node> node, int priority);

            int getIndexOfHeapNode(shared_ptr<HeapNode> heapNode);

            ~MinHeap();

        private:
            vector<shared_ptr<HeapNode>> heapNodes;

            void heapifyUp(shared_ptr<HeapNode> heapNode);
            void heapifyDown(shared_ptr<HeapNode> heapNode);
            void swap(shared_ptr<HeapNode> heapNode1, shared_ptr<HeapNode> heapNode2);
    };
}

#endif
