#include <iostream>
#include "liststack.h"

using namespace std;

// Name: push()
// Desc: pushes to the top item of the stack
// Input: ListStack* &stack, int value
// Output: none
// Return: none
void push(ListStack* &stack, int value) {
    // Create the new node for new value
    ListStack* newNode = new ListStack;

    // Setup the new node with its value and pointer
    newNode->value = value;
    newNode->next = stack;

    // Update the head to be the new node
    stack = newNode;
}

// Name: pop()
// Desc: Gets and removes the top value of the stack
// Input: ListStack* &stack
// Output: Maybe stack is empty warning
// Return: int value, or -1 if error
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

// Name: peek()
// Desc: Gets the top item without removing it
// Input: const ListStack* stack
// Output: Maybe stack is empty warning
// Return: value at the top of the stack
int peek(const ListStack* stack) {
    if (!isEmpty(stack)) {
        return stack->value;
    }
    else {
        cout << "Error: Stack is empty!" << endl;
        return -1;
    }
}

// Name: isEmpty()
// Desc: Checks if stack is empty
// Input: const ListStack* stack
// Output: None
// Return: bool true if empty
bool isEmpty(const ListStack* stack) {
    return stack == nullptr;
}

// Name: printStack()
// Desc: Prints all the values in the stack formatted
// Input: ListStack* stack
// Output: List of all values in the stack
// Return: none
void printStack(ListStack* stack) {
    ListStack* current = stack;

    int count = 1;
    cout << "Current Stack: " << endl;
    // Loop until end of stack
    while (current != nullptr) {
        cout << "Value " << count << ": " << current->value << endl;
        current = current->next;
        ++count;
        
    }

}