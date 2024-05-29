#include <iostream>
#include <locale.h>
#include <unordered_set>

using namespace std;

template <class T>
class Node 
{
public:
    T data;
    Node* next;
    Node* prev;

    Node() : next(nullptr), prev(nullptr) {}
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template <class T>
class DoublyLinkedList 
{
private:
    Node<T>* head;
    Node<T>* tail;

    // Функция для освобождения памяти, используемой для списка
    void clearList() 
    {
        Node<T>* current = head;
        while (current != nullptr) 
        {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Функция для клонирования списка
    Node<T>* clone() 
    {
        Node<T>* newHead = nullptr;
        Node<T>* newTail = nullptr;

        Node<T>* current = head;
        while (current != nullptr) 
        {
            Node<T>* newNode = new Node<T>(current->data);
            if (newHead == nullptr) 
            {
                newHead = newTail = newNode;
            }
            else 
            {
                newTail->next = newNode;
                newNode->prev = newTail;
                newTail = newNode;
            }
            current = current->next;
        }

        return newHead;
    }

    // Перегрузка оператора "+", объединение двух списков
    Node<T>* operator+(DoublyLinkedList& otherList) 
    {
        Node<T>* newHead = clone();
        Node<T>* newTail = nullptr;

        Node<T>* current = otherList.head;
        while (current != nullptr) 
        {
            Node<T>* newNode = new Node<T>(current->data);
            if (newHead == nullptr) 
            {
                newHead = newTail = newNode;
            }
            else {
                newTail->next = newNode;
                newNode->prev = newTail;
                newTail = newNode;
            }
            current = current->next;
        }

        return newHead;
    }

    // Перегрузка оператора "*", нахождение общих элементов в двух списках
    Node<T>* operator*(DoublyLinkedList& otherList) 
    {
        unordered_set<T> elements;
        Node<T>* newHead = nullptr;
        Node<T>* newTail = nullptr;

        Node<T>* current = head;
        while (current != nullptr) 
        {
            elements.insert(current->data);
            current = current->next;
        }

        current = otherList.head;
        while (current != nullptr) {
            if (elements.find(current->data) != elements.end()) 
            {
                Node<T>* newNode = new Node<T>(current->data);
                if (newHead == nullptr) 
                {
                    newHead = newTail = newNode;
                }
                else 
                {
                    newTail->next = newNode;
                    newNode->prev = newTail;
                    newTail = newNode;
                }
            }
            current = current->next;
        }

        return newHead;
    }

    // Перегрузка оператора присваивания для присвоения значений одного списка другому
    DoublyLinkedList& operator=(const DoublyLinkedList& other) 
    {
        if (this == &other) 
        {
            return *this;
        }

        clearList();

        Node<T>* current = other.head;
        while (current != nullptr) 
        {
            pushBack(current->data);
            current = current->next;
        }

        return *this;
    }

    // Функция для добавления элемента в конец списка
    void pushBack(T value) 
    {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) 
        {
            head = tail = newNode;
        }
        else 
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Функция для вывода списка
    void displayList() 
    {
        Node<T>* current = head;
        while (current != nullptr) 
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");

    DoublyLinkedList<int> list1;
    list1.pushBack(1);
    list1.pushBack(2);
    list1.pushBack(3);

    DoublyLinkedList<int> list2;
    list2.pushBack(2);
    list2.pushBack(4);
    list2.pushBack(6);

    Node<int>* clonedList = list1.clone();
    cout << "Клонированный список: ";
    while (clonedList != nullptr) 
    {
        cout << clonedList->data << " ";
        clonedList = clonedList->next;
    }
    cout << endl;

    Node<int>* combinedList = list1 + list2;
    cout << "Объединенный список: ";
    while (combinedList != nullptr) 
    {
        cout << combinedList->data << " ";
        combinedList = combinedList->next;
    }
    cout << endl;

    Node<int>* commonElementsList = list1 * list2;
    cout << "Список общих элементов: ";
    while (commonElementsList != nullptr) 
    {
        cout << commonElementsList->data << " ";
        commonElementsList = commonElementsList->next;
    }
    cout << endl;

    return 0;
}