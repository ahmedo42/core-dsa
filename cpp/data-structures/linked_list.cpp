#include <memory>
#include <iostream>
#include <stdexcept> // for exception handling

template <typename T>
class Node {
public:
    T data;
    std::unique_ptr<Node<T>> next;

    Node(const T& val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    std::unique_ptr<Node<T>> dummyHead;
    Node<T>* tail;
    int n_elements;

public:
    LinkedList() : n_elements(0) {
        dummyHead = std::make_unique<Node<T>>(T());
        tail = dummyHead.get();
    }
    
    int size(){
        return this->n_elements;
    }

    void push_back(const T& val) {
        tail->next = std::make_unique<Node<T>>(val);
        tail = tail->next.get();
        n_elements++;
    }

    void push_front(const T& val) {
        auto newNode = std::make_unique<Node<T>>(val);
        newNode->next = std::move(dummyHead->next);
        dummyHead->next = std::move(newNode);
        if (n_elements == 0) {
            tail = dummyHead->next.get();
        }
        n_elements++;
    }

    void pop_back() {
        if (n_elements == 0) return;
        auto current = dummyHead.get();
        while (current->next->next != nullptr) {
            current = current->next.get();
        }
        current->next = nullptr;
        tail = current;
        n_elements--;
    }

    void pop_front() {
        if (n_elements == 0) return;
        dummyHead->next = std::move(dummyHead->next->next);
        if (n_elements == 1) {
            tail = dummyHead.get();
        }
        n_elements--;
    }

    void insert(int index, const T& val) {
        if (index < 0 || index > n_elements) return;
        auto newNode = std::make_unique<Node<T>>(val);
        auto current = dummyHead.get();
        for (int i = 0; i < index; ++i) {
            current = current->next.get();
        }
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
        if (index == n_elements) {
            tail = current->next.get();
        }
        n_elements++;
    }

    void erase(int index) {
        if (index < 0 || index >= n_elements) return;
        auto current = dummyHead.get();
        for (int i = 0; i < index; ++i) {
            current = current->next.get();
        }
        current->next = std::move(current->next->next);
        if (index == n_elements - 1) {
            tail = current;
        }
        n_elements--;
    }

    T& front() {
        if (n_elements == 0) throw std::out_of_range("List is empty");
        return dummyHead->next->data;
    }

    T& back() {
        if (n_elements == 0) throw std::out_of_range("List is empty");
        return tail->data;
    }

    void print() {
        auto current = dummyHead->next.get();
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList<int> list;
    
    // Test push_back and push_front
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    list.push_back(3);
    list.print(); // Output: 0 1 2 3
    
    // Test pop_back and pop_front
    list.pop_back();
    list.pop_front();
    list.print(); // Output: 1 2
    
    // Test insert
    list.insert(1, 4);
    list.print(); // Output: 1 4 2
    
    // Test erase
    list.erase(1);
    list.print(); // Output: 1 2
    
    // Test front and back
    std::cout << "Front: " << list.front() << std::endl; // Output: Front: 1
    std::cout << "Back: " << list.back() << std::endl; // Output: Back: 2
    
    // Test exceptions for empty list
    try {
        LinkedList<int> emptyList;
        emptyList.front(); // Should throw exception
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl; // Output: Exception: List is empty
    }

    return 0;
}