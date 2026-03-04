#include <iostream>
#include "liststack.h"

using namespace std;

void push(ListStack* &stack, int value) {
    // Create the new node for new value
    ListStack* newNode = new ListStack;

    // Setup the new node with its value and pointer
    newNode->value = value;
    newNode->next = stack;

    // Update the head to be the new node
    stack = newNode;
}

int pop(ListStack* &stack) {
    if (!isEmpty(stack)) {
        // Get node and value being popped
        ListStack* oldTop = stack;
        int poppedVal = oldTop->value;

        // Update stack head to be the next node
        stack = oldTop->next;

        // Delete the current node
        delete oldTop;

        return poppedVal;
    }
    else {
        cout << "Error: Stack is empty!" << endl;
        return -1;
    }


}

int peek(const ListStack* stack) {
    return stack->value;
}

bool isEmpty(const ListStack* stack) {
    return stack == nullptr;
}

void printStack(ListStack* stack) {
    ListStack* current = stack;

    int count = 1;
    cout << "Current Stack: " << endl;
    while (current != nullptr) {
        cout << "Value " << count << ": " << current->value << endl;
        current = current->next;
        ++count;
        
    }

}