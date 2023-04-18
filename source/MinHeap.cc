#include <iostream>
#include <vector>

#include "MinHeap.h"
#include "HeapNode.h"
#include "Node.h"
#include <cmath>

using namespace std;
using namespace GraphModule;

MinHeap::MinHeap(vector<HeapNode*> heapNodes)
{
    this->heapNodes = heapNodes;
}

void MinHeap::insert(Node* node, int priority)
{
    int insertedNodeIndex = heapNodes.size();

    HeapNode* heapNodeToInsert = new HeapNode(insertedNodeIndex, node, priority);

    this->heapNodes.push_back(heapNodeToInsert);

    this->heapifyUp(heapNodeToInsert);
}

int MinHeap::minPriority()
{
    if (heapNodes.size() == 0)
    {
        return -1;
    }
    else
    {
        return this->heapNodes[0]->priority;
    }
}

Node* MinHeap::popMin()
{
    if (heapNodes.size() == 0)
    {
        return NULL;
    }
    else
    {
        HeapNode* minHeapNode = this->heapNodes[0];
        this->heapNodes.erase(this->heapNodes.begin());

        if (this->heapNodes.size() > 0)
        {
            HeapNode* lastHeapNode = this->heapNodes.back();
            lastHeapNode->key = 0;
            this->heapNodes.insert(this->heapNodes.begin(), lastHeapNode);

            this->heapifyDown(lastHeapNode);
        }

        return minHeapNode->node;
    }
}

int MinHeap::size()
{
    return this->heapNodes.size();
}

bool MinHeap::contains(Node* node)
{
    for (int i = 0; i < this->heapNodes.size(); i++)
    {
        if (this->heapNodes[i]->node == node)
        {
            return true;
        }
    }

    return false;
}

void MinHeap::updatePriority(Node* node, int priority)
{
    for (int i = 0; i < this->heapNodes.size(); i++)
    {
        if (this->heapNodes[i]->node == node)
        {
            int previousPriority = this->heapNodes[i]->priority;

            this->heapNodes[i]->priority = priority;

            if (previousPriority == priority)
            {
                return;
            }

            if (previousPriority > priority)
            {
                this->heapifyUp(this->heapNodes[i]);
            }
            else
            {
                this->heapifyDown(this->heapNodes[i]);
            }

            return;
        }
    }
}

void MinHeap::heapifyUp(HeapNode* heapNode)
{
    while (heapNode->key > 0)
    {
        HeapNode* parentHeapNode = this->heapNodes[heapNode->getParent()];

        if (heapNode->priority < parentHeapNode->priority)
        {
            this->swap(heapNode, parentHeapNode);
        }
    }
}

void MinHeap::heapifyDown(HeapNode* heapNode)
{
    while (true)
    {
        if (heapNode->getLeft() >= this->heapNodes.size())
        {
            break;
        }

        if (heapNode->getRight() >= this->heapNodes.size())
        {
            HeapNode* leftHeapNode = this->heapNodes[heapNode->getLeft()];

            if (heapNode->priority > leftHeapNode->priority)
            {
                this->swap(leftHeapNode, heapNode);
            }
            else
            {
                break;
            }
        }
        else
        {
            HeapNode* leftHeapNode = this->heapNodes[heapNode->getLeft()];
            HeapNode* rightHeapNode = this->heapNodes[heapNode->getRight()];

            if (heapNode->priority < min(leftHeapNode->priority, rightHeapNode->priority))
            {
                break;
            }

            if (leftHeapNode->priority < rightHeapNode->priority)
            {
                this->swap(leftHeapNode, heapNode);
            }
            else
            {
                this->swap(rightHeapNode, heapNode);
            }
        }
    }
}

void MinHeap::swap(HeapNode* heapNode1, HeapNode* heapNode2)
{
    int heapNode1Key = heapNode1->key;
    int heapNode2Key = heapNode2->key;

    this->heapNodes[heapNode1Key] = heapNode2;
    this->heapNodes[heapNode2Key] = heapNode1;

    heapNode1->key = heapNode2Key;
    heapNode2->key = heapNode1Key;
}

MinHeap::~MinHeap() //CHECK FOR MEMORY LEAK, JUST IN CASE.
{
    for (int i = 0; i < this->heapNodes.size(); i++)
    {
        HeapNode* heapNode = this->heapNodes[i];
        delete heapNode;
    }
}
