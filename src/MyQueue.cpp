#include "MyQueue.h"

void Queue::enqueue(Entity* e)
{
    QueueNode* newNode = new QueueNode(e);
    if (tail != nullptr) {
        tail->next = newNode;
        newNode->previous = tail;
    }
    tail = newNode;
    if (head == nullptr) {
        head = newNode;
    }
    count++;
}

Entity* Queue::dequeue()
{
    if (!isEmpty())
    {
        return nullptr;
    }
        
    QueueNode* temp = head;
    Entity* data = head->data;
    
    head = head->next;
    
    if (head == nullptr)
    {
        tail = nullptr;
    }
    delete temp;
    count--;
    return data;
}

Entity* Queue::front()
{
    if (isEmpty())
    {
        return nullptr;
    }
    return head->data;
}

bool Queue::isEmpty() const
{
    return head == nullptr;
}

int Queue::size() const
{
    return count;
}

QueueNode* Queue::next(QueueNode* node) const
{
    return node->next;
}

QueueNode* Queue::getHead() const
{
    return head;
}

void Queue::erase(QueueNode* node)
{
    if (node == nullptr) {
        return;
    }

    // if node is the head
    if (node == head)
        {
        head = node->next;
        if (head != nullptr)
        {
            head->previous = nullptr;
        }
    }
    else
    {
        node->previous->next = node->next;
    }

    // If node is the tail
    if (node == tail) {
        tail = node->previous;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
    }
    
    else
    {
        if (node->next != nullptr)
        {
            node->next->previous = node->previous;
        }
    }

    // If node was the only element in the queue
    if (head == nullptr)
    {
        tail = nullptr;
    }

    delete node;
    count--;
}