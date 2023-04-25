#include <iostream>
#include <vector>
#include <algorithm>

#include "MinHeap.h"
#include "HeapNode.h"
#include "Node.h"

#include <memory>
#include <cmath>

using namespace std;
using namespace GraphModule;

MinHeap::MinHeap()
{

}

void MinHeap::insert(shared_ptr<Node> node, int priority)
{
    int insertedNodeIndex = heapNodes.size();

    shared_ptr<HeapNode> heapNodeToInsert = make_shared<HeapNode>(insertedNodeIndex, node, priority);

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

shared_ptr<Node> MinHeap::popMin()
{
    if (heapNodes.size() == 0)
    {
        return NULL;
    }

    shared_ptr<HeapNode> minHeapNode = this->heapNodes[0];
    this->heapNodes.erase(this->heapNodes.begin());

    if (this->heapNodes.size() > 0)
    {
        shared_ptr<HeapNode> lastHeapNode = this->heapNodes.back();
        this->heapNodes.pop_back();

        lastHeapNode->key = 0;

        this->heapNodes.insert(this->heapNodes.begin(), lastHeapNode);

        this->heapifyDown(lastHeapNode);
    }

    return minHeapNode->node;
}

int MinHeap::size()
{
    return this->heapNodes.size();
}

bool MinHeap::contains(shared_ptr<Node> node)
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

void MinHeap::updatePriority(shared_ptr<Node> node, int priority)
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

void MinHeap::heapifyUp(shared_ptr<HeapNode> heapNode)
{
    while (heapNode->key > 0 && heapNode->priority < this->heapNodes[heapNode->getParent()]->priority)
    {
        shared_ptr<HeapNode> parentHeapNode = this->heapNodes[heapNode->getParent()];
        this->swap(heapNode, parentHeapNode);
    }
}

void MinHeap::heapifyDown(shared_ptr<HeapNode> heapNode)
{
    while (true)
    {
        if (heapNode->getLeft() >= this->heapNodes.size())
        {
            break;
        }

        if (heapNode->getRight() >= this->heapNodes.size())
        {
            shared_ptr<HeapNode> leftHeapNode = this->heapNodes[heapNode->getLeft()];
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
            shared_ptr<HeapNode> leftHeapNode = this->heapNodes[heapNode->getLeft()];
            shared_ptr<HeapNode> rightHeapNode = this->heapNodes[heapNode->getRight()];
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

void MinHeap::swap(shared_ptr<HeapNode> heapNode1, shared_ptr<HeapNode> heapNode2)
{
    //cout << "Swap" << endl;
    int heapNode1Key = heapNode1->key;
    // cout << heapNode1 << endl;
    // cout << "Heap node 1 key: " << heapNode1Key << endl;
    int heapNode2Key = heapNode2->key;
    // cout << heapNode2 << endl;
    // cout << "Heap node 2 key: " << heapNode2Key << endl;

    int heapNode1Index = getIndexOfHeapNode(heapNode1);
    //cout << "Heap node 1 index: " << heapNode1Index << endl;
    int heapNode2Index = getIndexOfHeapNode(heapNode2);
    //cout << "Heap node 2 index: " << heapNode2Index << endl;

    this->heapNodes[heapNode1Index] = heapNode2;
    //cout << "Heap node 1 index: " << heapNode1->key << endl;
    this->heapNodes[heapNode2Index] = heapNode1;
    //cout << "Heap node 2 index: " << heapNode2->key << endl;

    heapNode1->key = heapNode2Key;
    heapNode2->key = heapNode1Key;
}

int MinHeap::getIndexOfHeapNode(shared_ptr<HeapNode> heapNode)
{
    auto it = find_if(this->heapNodes.begin(), this->heapNodes.end(), [heapNode](const auto& p) {
        return p->key == heapNode->key;
    });

    if (it != this->heapNodes.end()) {
        auto index = distance(this->heapNodes.begin(), it);
        return index;
    } else {
        return -1;
    }
}

MinHeap::~MinHeap()
{

}
