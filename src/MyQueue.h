#pragma once

class Entity;

class QueueNode
{
public:
    QueueNode(Entity* e) : data(e), next(nullptr), previous(nullptr) {}
    
    Entity* data;
    QueueNode* next;
    QueueNode* previous;
};


class Queue {
public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}

    ~Queue() {
        while (head != nullptr) {
            QueueNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void enqueue(Entity* e);
    void erase(QueueNode* node);
    
    Entity* dequeue();
    Entity* front();
    
    bool isEmpty() const;
    int size() const;
    
    QueueNode* next(QueueNode* node) const;
    QueueNode* getHead() const;

private:
    QueueNode* head;
    QueueNode* tail;
    int count;

};