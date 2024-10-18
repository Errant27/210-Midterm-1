// 210 | Midterm #1 | Neil Orton
// IDE used: Xcode
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

    // Insert after function definiton takes in the value and position to search for in the list
    // function will insert a node 1 positon after the on sent in as and arguemnt
    void insert_after(int value, int position) {
        if (position < 0) {    // if the position entered is less than 0, message returns
            cout << "Position must be >= 0." << endl;
            return;    // return 'breaks away' from function under these condiitions
        }

        Node* newNode = new Node(value);   // a new Node is dynamically allocated and used the Node constructor with value as arguemnt
        if (!head) {    // if there is no value stored in head, the list is currently empty
            head = tail = newNode;    // head & tail now point to newNode as the first/only Node in the list (the front & back)
            return;    // return 'breaks away' from function under these condiitions
        }

        Node* temp = head;    // if the list is not empty, a temp pointer ponits to the head of the list
        for (int i = 0; i < position && temp; ++i)    // for loop to get temp the proper position in the list based on the position arguemnt in the function call
            temp = temp->next;    // temp moves ahead a node on each loop iteration

        if (!temp) {    // if temp reaches the end of the list from the for loop, a message displays saying that the position entered exceeded the list size
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;    // Node is not added to the list and deleted to avoid memory leaks
            return;    // return 'breaks away' from function under these condiitions
        }

        newNode->next = temp->next;    // newNode's next points to the next node based on temp's position
        newNode->prev = temp;    // newNode's prev pointer points to temp's current position
        if (temp->next)
            temp->next->prev = newNode;    // if temp's next pointer is not pointing to nullptr,
        else                               // the node ahead of next will point to the new Node with it's prev pointer
            tail = newNode;
        temp->next = newNode;    // else, tail now points to newNode as the end (tail) of the list
    }                            // and temp assign's newNode as the the Node after it

    void delete_val(int value) {    // delete val function takes in a value as an argument to delete the node which holds that value
        if (!head) return;    // if head does not hold a value, list is empty, and nothing is done

        Node* temp = head;    // temp pointer poniter points to start of the list
        
        while (temp && temp->data != value)
            temp = temp->next;    // while temp is not at the end of the list and is not pointing at the node with the value, temp moves ahead in the list

        if (!temp) return;    // if temp goes beyond the bounds of of the list, nothing occurs

        if (temp->prev)
            temp->prev->next = temp->next;    // if temp has a node 'behind' it, that node's next pointer now points to the node aftet temp
        else
            head = temp->next;    // if temp has no node 'behind' it, head now points to the node after it as the new 'head' of the list

        if (temp->next)
            temp->next->prev = temp->prev;    // if temp has a node 'ahead' it, that node's previous pointer now points to the node before temp
        else
            tail = temp->prev;    // if temp has no node 'ahead' it, head now points to the node after it as the new 'tail' of the list

        delete temp;    // contents of temp are deleted
    }

    void delete_pos(int pos) {    // delete pos function takes in a postion as an argument to delete the node which is in that position
        if (!head) {
            cout << "List is empty." << endl;    // if head is empty, the list is empty and a message is printed
            return;    // return 'breaks away' from function under these condiitions
        }
    
        if (pos == 1) {
            pop_front();    // if the postition entered is the first position, the pop_front function is called
            return;    // return 'breaks away' from function under these condiitions
        }
    
        Node* temp = head;    // if the position entered is greater than 1, temp points to the heead of the list
    
        for (int i = 1; i < pos; i++){    // for loop to get the temp pointer in the right postition in the list
            if (!temp) {    // if temp exceeded past the end of the list, a message is printed notifying that tha position is invalid
                cout << "Position doesn't exist." << endl;
                return;    // return 'breaks away' from function under these condiitions
            }
            else
                temp = temp->next;    // temp moves through the list on each loop iteration
        }
        if (!temp) {   // same code as he temp went beyond the bounds of the list in the for loop
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();    // if temp has reached the end (tail) of the lsit, the pop_back function is called
            return;
        }
    
        Node* tempPrev = temp->prev;    // tempPrev pointer points to the previous node relative to temp's location
        tempPrev->next = temp->next;    // tempPrev's next pointer points to the node after temp's curent location
        temp->next->prev = tempPrev;    // the prev poniter for the node ahead of temp points to tempPrev (node 'behind' temp)
        delete temp;    // contents of temp are deleted
    }

    void push_back(int v) {    // function to push a node to the back the doubly linked list
        Node* newNode = new Node(v);    // newNode is constructed using the Nod constructor with v passed as the data
        if (!tail)    // if the tail pointer stores no value (nothing is at the end of te list)
            head = tail = newNode;    // head & tail point to the newNode as first (current only) node in the lsit
        else {
            tail->next = newNode;    // else, the current end of the list points to the newNode as the node after it
            newNode->prev = tail;    // newNode points to current tail as its previous node
            tail = newNode;    // tail points to the new node as the new 'tail' of the list
        }
    }
    
    void push_front(int v) {    // function to push front a node to the front in the doubly linked list
        Node* newNode = new Node(v);    // newNode is constructed using the Nod constructor with v passed as the data
        if (!head)    // if the head pointer stores no value (nothing is at the front of te list)
            head = tail = newNode;   // head & tail point to the newNode as first (current only) node in the lsit
        else {
            newNode->next = head;    // else, the current front of the list points to the newNode as the node after it
            head->prev = newNode;    // newNode points to current head as its previous node
            head = newNode;    // head points to the new node as the new 'tail' of the list
        }
    }
    
    void pop_front() {    // function to pop a node to the front in the doubly linked list

        if (!head) {    // if the head pointer stores no value, list is empty and message is outputted
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;    //if the list is not empty, temp points to head of the list

        if (head->next) {    // if the head has a node after it
            head = head->next;    // head pointer assigns the node ahead of it as the new head
            head->prev = nullptr;    // head assigns it prev pointer to point to nullptr
        }
        else
            head = tail = nullptr;    // if head has no node after it (only one node in the list), head & tail point to nullptr
        delete temp;    // contents of temp are deleted
    }

    void pop_back() {    // function to pop a node to the end in the doubly linked list
        if (!tail) {    // if the tail pointer stores no value, list is empty and message is outputted
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;    // if the list is not empty, temp points to head of the list

        if (tail->prev) {    // if the tail has a node before it
            tail = tail->prev;   // tail pointer assigns the node behind of it as the new tail
            tail->next = nullptr;    // tail assigns its next pointer to point to nullptr
        }
        else
            head = tail = nullptr;    // if head has no node after it (only one node in the list), head & tail point to nullptr
        delete temp;    // contents of temp are deleted
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
