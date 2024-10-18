#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {    // private member struct Node through which all nodes will be built
        int data;    // data varaible will store an in in each node
        Node* prev;    // prev pointer to point to the previous node in the doubly linked list
        Node* next;    // next pointer to point to the next node in the doubly linked list
        Node(int val, Node* p = nullptr, Node* n = nullptr) {    // Node constructor to be used when a new Node is created dynamically
            data = val;    // the Node's int data value will be assigned to the value inputted in the constructor argument
            prev = p;    // a new Node's prev pointer will intially point to nullptr
            next = n;    // a new Node's next pointer will intially point to nullptr
        }
    };

    Node* head;    // private head member which will point to the start of the list in the doubly linked list
    Node* tail;    // private tail member which will point to the start of the list in the doubly linked list

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }    // Default constrcutor for doubly linked list, assigns the head & tail pointer to nullptr

    void insert_after(int value, int position) {    // Insert after function definiton takes in the value and position to search for in th list
        if (position < 0) {    // if the position entered is less than 0, message returns
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);   // a new Node is dynamically allocated and used the Node constructor with value as arguemnt
        if (!head) {    // if there is no value stored in head, the list is currently empty
            head = tail = newNode;    // head & tail now point to newNode as the first/only Node in the list (the front & back)
            return;
        }

        Node* temp = head;    // if the list is not empty, a temp pointer ponits to the head of the list
        for (int i = 0; i < position && temp; ++i)    // for loop to get temp the proper position in the list based on the position arguemnt in the function call
            temp = temp->next;    // temp moves ahead a node on each loop iteration

        if (!temp) {    // if temp reaches the end of the list from the for loop, a message displays saying that the position entered exceeded the list size
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;    // Node is not added tot he list and deleted to avoid memory leaks
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}
