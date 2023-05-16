#include "HeapNode.h"
#include <cmath>
#include <memory>
#include <utility>

#include "Node.h"

using namespace std;
using namespace GraphModule;

HeapNode::HeapNode(int key, shared_ptr<Node> node, int priority) 
{
    this->key = key;
    this->node = std::move(node);
    this->priority = priority;
}

int HeapNode::getParent()
{
    return floor((key - 1) / 2);
}

int HeapNode::getLeft() 
{
    return 2 * key + 1;
}

int HeapNode::getRight() 
{
    return 2 * key + 2;
}

bool HeapNode::operator >(const HeapNode& other) const
{
    return priority > other.priority;
}

bool HeapNode::operator >(int x) const
{
    return priority > x;
}

bool HeapNode::operator <(const HeapNode& other) const
{
    return priority < other.priority;
}

bool HeapNode::operator <(int x) const
{
    return priority < x;
}

bool HeapNode::operator <=(const HeapNode& other) const
{
    return priority <= other.priority;
}

bool HeapNode::operator <=(int x) const
{
    return priority <= x;
}

bool HeapNode::operator >=(const HeapNode& other) const
{
    return priority >= other.priority;
}

bool HeapNode::operator >=(int x) const
{
    return priority >= x;
}

bool HeapNode::operator ==(const HeapNode& other) const
{
    return priority == other.priority;
}

bool HeapNode::operator !=(const HeapNode& other) const
{
    return priority != other.priority;
}

HeapNode::~HeapNode() 
= default;
