#ifndef MinHeap_h
#define MinHeap_h

#include <iostream>
#include <vector>
#include <random>
#include "HeapNode.h"

using namespace std;

namespace GraphModule
{
    class Graph::MinHeap
    {
        public:
            MinHeap(vector<HeapNode*> heapNodes);

            void insert(Node* node, int priority);

            int* min();

            Node* popMin();

            int size();

            bool contains(Node* node);

            void updatePriority(Node* node, int priority);

            ~MinHeap();

        private:
            vector<HeapNode*> heapNodes;

            void heapifyUp(HeapNode* heapNode);
            void heapifyDown(HeapNode* heapNode);
            void swap(HeapNode* heapNode1, HeapNode* heapNode2);
    };
}

#endif
