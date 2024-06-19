#pragma once

template <typename T>
class QueueNode {
public:
    QueueNode(T* e) : data(e), next(nullptr), previous(nullptr) {}
    
    T* data;
    QueueNode* next;
    QueueNode* previous;
};

template <typename T>
class Queue {
public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}

    ~Queue() {
        while (head != nullptr) {
            QueueNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void enqueue(T* e);
    void erase(QueueNode<T>* node);
    
    T* dequeue();
    T* front();
    
    bool isEmpty() const;
    int size() const;
    
    QueueNode<T>* next(QueueNode<T>* node) const;
    QueueNode<T>* getHead() const;

private:
    QueueNode<T>* head;
    QueueNode<T>* tail;
    int count;
};

template <typename T>
void Queue<T>::enqueue(T* e) {
    QueueNode<T>* newNode = new QueueNode<T>(e);
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

template <typename T>
T* Queue<T>::dequeue() {
    if (isEmpty()) {
        return nullptr;
    }
        
    QueueNode<T>* temp = head;
    T* data = head->data;
    
    head = head->next;
    
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->previous = nullptr;
    }
    delete temp;
    count--;
    return data;
}

template <typename T>
T* Queue<T>::front() {
    if (isEmpty()) {
        return nullptr;
    }
    return head->data;
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
int Queue<T>::size() const {
    return count;
}

template <typename T>
QueueNode<T>* Queue<T>::next(QueueNode<T>* node) const {
    return node->next;
}

template <typename T>
QueueNode<T>* Queue<T>::getHead() const {
    return head;
}

template <typename T>
void Queue<T>::erase(QueueNode<T>* node) {
    if (node == nullptr) {
        return;
    }

    if (node == head) {
        head = node->next;
        if (head != nullptr) {
            head->previous = nullptr;
        }
    } else {
        node->previous->next = node->next;
    }

    if (node == tail) {
        tail = node->previous;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
    } else {
        if (node->next != nullptr) {
            node->next->previous = node->previous;
        }
    }

    if (head == nullptr) {
        tail = nullptr;
    }

    delete node;
    count--;
}