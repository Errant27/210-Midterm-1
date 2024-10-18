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

        delete temp;    // temp is deleted from the list
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
