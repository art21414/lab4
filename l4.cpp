#include <iostream>
#include <new>

template <typename T>
class StackBasedOnUnidirectionalCyclicLinkedList {
private:
    template <typename T>
    class Node {
    public:
        T data;
        Node* next;

        Node(T data = T(), Node* next = nullptr) {
            this->data = data;
            this->next = next;
        }
    };

    Node<T>* top;
    int size;

public:

    int GetSize() const {
        return size;
    };
    void clear();
    bool Push(const T& element);
    bool Pop(T& element);
    bool Peek(T& element) const;
    StackBasedOnUnidirectionalCyclicLinkedList();
    StackBasedOnUnidirectionalCyclicLinkedList(const StackBasedOnUnidirectionalCyclicLinkedList<T>& other);
    StackBasedOnUnidirectionalCyclicLinkedList(StackBasedOnUnidirectionalCyclicLinkedList<T>&& other);
    StackBasedOnUnidirectionalCyclicLinkedList(std::initializer_list<T> ilist);
    ~StackBasedOnUnidirectionalCyclicLinkedList();
    StackBasedOnUnidirectionalCyclicLinkedList<T>& operator=(const StackBasedOnUnidirectionalCyclicLinkedList<T>& other);
    StackBasedOnUnidirectionalCyclicLinkedList<T>& operator=(StackBasedOnUnidirectionalCyclicLinkedList<T>&& other);
    StackBasedOnUnidirectionalCyclicLinkedList<T>& operator=(std::initializer_list<T> ilist);
};

template<typename T>
StackBasedOnUnidirectionalCyclicLinkedList<T>::StackBasedOnUnidirectionalCyclicLinkedList()
{
    size = 0;
    top = nullptr;
}

template<typename T>
StackBasedOnUnidirectionalCyclicLinkedList<T>::~StackBasedOnUnidirectionalCyclicLinkedList() {
    clear();
}


template <typename T>
StackBasedOnUnidirectionalCyclicLinkedList<T>::StackBasedOnUnidirectionalCyclicLinkedList(const StackBasedOnUnidirectionalCyclicLinkedList<T>& other) : top(nullptr), size(0) {
    *this = other;
}

template <typename T>
StackBasedOnUnidirectionalCyclicLinkedList<T>::StackBasedOnUnidirectionalCyclicLinkedList(StackBasedOnUnidirectionalCyclicLinkedList<T>&& other) : top(nullptr), size(0) {
    *this = std::move(other);
}

template <typename T>
StackBasedOnUnidirectionalCyclicLinkedList<T>::StackBasedOnUnidirectionalCyclicLinkedList(std::initializer_list<T> ilist) : top(nullptr), size(0) {
    *this = ilist;
}


template <typename T>
StackBasedOnUnidirectionalCyclicLinkedList<T>& StackBasedOnUnidirectionalCyclicLinkedList<T>::operator=(const StackBasedOnUnidirectionalCyclicLinkedList<T>& other) {
    if (this != &other) {
        clear();
        if (other.top != nullptr) {
            Node<T>* currentOther = other.top->next;
            do {
                if (!Push(currentOther->data)) {
                    clear();
                    throw std::bad_alloc();
                }
                currentOther = currentOther->next;
            } while (currentOther != other.top->next);
        }
    }

    return *this;
}

template <typename T>
StackBasedOnUnidirectionalCyclicLinkedList<T>& StackBasedOnUnidirectionalCyclicLinkedList<T>::operator=(StackBasedOnUnidirectionalCyclicLinkedList<T>&& other) {
    if (this != &other) {
        clear();
        top = other.top;
        size = other.size;
        other.top = nullptr;
        other.size = 0;
    }

    return *this;
}


template <typename T>
StackBasedOnUnidirectionalCyclicLinkedList<T>& StackBasedOnUnidirectionalCyclicLinkedList<T>::operator=(std::initializer_list<T> ilist) {
    clear();
    for (const T& item : ilist) {
        Push(item);
    }
    return *this;
}

template<typename T>
void StackBasedOnUnidirectionalCyclicLinkedList<T>::clear() {
    Node<T>* nextNode;
    while (size > 0) {
        nextNode = top->next;
        delete top;
        top = nextNode;
        --size;
    }
    top = nullptr;
}

template<typename T>
bool StackBasedOnUnidirectionalCyclicLinkedList<T>::Push(const T& element) {
    Node<T>* newNode = new(std::nothrow) Node<T>(element);
    if (newNode == nullptr) {
        return false;
    }
    if (top == nullptr) {
        newNode->next = newNode;
    }
    else {
        newNode->next = top->next;
        top->next = newNode;
    }
    top = newNode;
    size++;
    return true;
}

template<typename T>
bool StackBasedOnUnidirectionalCyclicLinkedList<T>::Pop(T& element) {
    if (top == nullptr) {
        return false;
    }
    element = top->data;
    Node<T>* toDelete = top;
    Node<T>* temp = top->next;
    if (top == top->next) {
        top = nullptr;
    }
    else {
        while (top != temp->next)
        {
            temp = temp->next;
        }
        temp->next = top->next;
        top = temp;
    }
    delete toDelete;
    --size;
    return true;
}

template<typename T>
bool StackBasedOnUnidirectionalCyclicLinkedList<T>::Peek(T& element) const {
    if (top == nullptr) {
        return false;
    }
    element = top->data;
    return true;
}

int main() {
    StackBasedOnUnidirectionalCyclicLinkedList<int> x;
    x.Push(2);
    x.Push(8);
    x.Push(131);
    int e;
    x.Peek(e);
    std::cout << e;
    x.Pop(e);
    x.Push(27);
    return 0;
}