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

// class HeapNode {
// private:
//     Node node;
//     int index;
//     int priorityWeight;

// public:
//     HeapNode(int index, Node node, int priorityWeight) {
//         this->node = node;
//         this->index = index;
//         this->priorityWeight = priorityWeight;
//     }

//     Node getNode() const {
//         return node;
//     }

//     int getIndex() const {
//         return index;
//     }

//     int getPriorityWeight() const {
//         return priorityWeight;
//     }

//     int parent() const {
//         return (index - 1) / 2;
//     }

//     int left() const {
//         return index * 2 + 1;
//     }

//     int right() const {
//         return index * 2 + 2;
//     }

//     bool operator >(const HeapNode& other) const {
//         if (priorityWeight > other.priorityWeight) {
//             return true;
//         }
//         return false;
//     }

//     bool operator >(int x) const {
//         if (priorityWeight > x) {
//             return true;
//         }
//         return false;
//     }

//     bool operator <(const HeapNode& other) const {
//         if (priorityWeight < other.priorityWeight) {
//             return true;
//         }
//         return false;
//     }

//     bool operator <(int x) const {
//         if (priorityWeight < x) {
//             return true;
//         }
//         return false;
//     }

//     bool operator <=(const HeapNode& other) const {
//         if (priorityWeight <= other.priorityWeight) {
//             return true;
//         }
//         return false;
//     }

//     bool operator <=(int x) const {
//         if (priorityWeight <= x) {
//             return true;
//         }
//         return false;
//     }

//     bool operator >=(const HeapNode& other) const {
//         if (priorityWeight >= other.priorityWeight) {
//             return true;
//         }
//         return false;
//     }

//     bool operator >=(int x) const {
//         if (priorityWeight >= x) {
//             return true;
//         }
//         return false;
//     }

//     bool operator ==(const HeapNode& other) const {
//         if (priorityWeight == other.priorityWeight) {
//             return true;
//         }
//         return false;
//     }

//     bool operator !=(const HeapNode& other) const {
//         if (priorityWeight != other.priorityWeight) {
//             return true;
//         }
//         return false;
//     }
// };
