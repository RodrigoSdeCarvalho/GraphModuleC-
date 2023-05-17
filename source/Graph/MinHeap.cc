#include <vector>
#include <algorithm>

#include "Graph/MinHeap.h"
#include "Graph/HeapNode.h"
#include "Graph/Node.h"

#include <memory>

using namespace std;
using namespace GraphModule;

MinHeap::MinHeap()
= default;

void MinHeap::insert(const shared_ptr<Node>& node, int priority)
{
    int insertedNodeIndex = heapNodes.size();

    shared_ptr<HeapNode> heapNodeToInsert = make_shared<HeapNode>(insertedNodeIndex, node, priority);

    this->heapNodes.push_back(heapNodeToInsert);

    this->heapifyUp(heapNodeToInsert);
}

int MinHeap::minPriority()
{
    if (heapNodes.empty())
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
    if (heapNodes.empty())
    {
        return nullptr;
    }

    shared_ptr<HeapNode> minHeapNode = this->heapNodes[0];
    this->heapNodes.erase(this->heapNodes.begin());

    if (!this->heapNodes.empty())
    {
        shared_ptr<HeapNode> lastHeapNode = this->heapNodes.back();
        this->heapNodes.pop_back();

        lastHeapNode->key = 0;

        this->heapNodes.insert(this->heapNodes.begin(), lastHeapNode);

        this->heapifyDown(lastHeapNode);
    }

    return minHeapNode->node;
}

int MinHeap::size() const
{
    return this->heapNodes.size();
}

bool MinHeap::contains(const shared_ptr<Node>& node)
{
    for (auto &heapNode: this->heapNodes)
    {
        if (heapNode->node == node) {
            return true;
        }
    }


    return false;
}

void MinHeap::updatePriority(const shared_ptr<Node>& node, int priority)
{
    for (auto & heapNode : this->heapNodes)
    {
        if (heapNode->node == node)
        {
            int previousPriority = heapNode->priority;

            heapNode->priority = priority;

            if (previousPriority == priority)
            {
                return;
            }

            if (previousPriority > priority)
            {
                this->heapifyUp(heapNode);
            }
            else
            {
                this->heapifyDown(heapNode);
            }

            return;
        }
    }
}

void MinHeap::heapifyUp(const shared_ptr<HeapNode>& heapNode)
{
    while (heapNode->key > 0 && heapNode->priority < this->heapNodes[heapNode->getParent()]->priority)
    {
        shared_ptr<HeapNode> parentHeapNode = this->heapNodes[heapNode->getParent()];
        this->swap(heapNode, parentHeapNode);
    }
}

void MinHeap::heapifyDown(const shared_ptr<HeapNode>& heapNode)
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

void MinHeap::swap(const shared_ptr<HeapNode>& heapNode1, const shared_ptr<HeapNode>& heapNode2)
{
    int heapNode1Key = heapNode1->key;
    int heapNode2Key = heapNode2->key;

    int heapNode1Index = getIndexOfHeapNode(heapNode1);
    int heapNode2Index = getIndexOfHeapNode(heapNode2);

    this->heapNodes[heapNode1Index] = heapNode2;
    this->heapNodes[heapNode2Index] = heapNode1;

    heapNode1->key = heapNode2Key;
    heapNode2->key = heapNode1Key;
}

int MinHeap::getIndexOfHeapNode(const shared_ptr<HeapNode>& heapNode)
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

void MinHeap::updatePriority(int nodeKey, int priority)
{
    for (auto & heapNode : this->heapNodes)
    {
        if ((heapNode->node->getNumber()) -1  == nodeKey)
        {
            int previousPriority = heapNode->priority;

            heapNode->priority = priority;

            if (previousPriority == priority)
            {
                return;
            }

            if (previousPriority > priority)
            {
                this->heapifyUp(heapNode);
            }
            else
            {
                this->heapifyDown(heapNode);
            }

            return;
        }
    }
}

MinHeap::~MinHeap()
= default;
