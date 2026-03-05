#include <iostream>
#include "arraystack.h"

using namespace std;

// Name: initStack()
// Desc: Sets the stack count to -1 to signify its empty
// Input: ArrayStack &stack
// Output: none
// Return: none
void initStack(ArrayStack &stack) {
    stack.count = -1;
}

// Name: push()
// Desc: pushes to the top item of the stack
// Input: ArrayStack &stack, int value
// Output: Maybe stack full warning
// Return: none
void push(ArrayStack &stack, int value) {
        // Check if stack is full
        if (!isFull(stack)) {
            // Make sure current index is being set
            if (isEmpty(stack)) {
                stack.count++;
            }
            stack.value[stack.count] = value;
            stack.count++;
        }
        else {
            cout << "Error: Stack is full!" << endl;
        }
        
    }

// Name: pop()
// Desc: Gets and removes the top value of the stack
// Input: ArrayStack &stack
// Output: Maybe stack is empty warning
// Return: int value, or -1 if error
int pop(ArrayStack &stack) {
    // Check if array is empty
    if (!isEmpty(stack)) {
        // Get first value
        int value = stack.value[stack.count - 1];

        stack.value[stack.count - 1] = 0;

        stack.count--;
        return value;

    }
    else {
        cout << "Error: Stack is empty!" << endl;
        return -1;
    }
}

// Name: peek()
// Desc: Gets the top item without removing it
// Input: ArrayStack stack
// Output: Maybe stack is empty warning
// Return: value at the top of the stack
int peek(ArrayStack stack) {
    if (!isEmpty(stack)) {
        return stack.value[stack.count - 1];
    }
    else {
        cout << "Error: Stack is empty!" << endl;
        return -1;
    }
}

// Name: isEmpty()
// Desc: Checks if stack is empty
// Input: const ArrayStack &stack
// Output: None
// Return: bool true if empty
bool isEmpty(const ArrayStack &stack) {
    return stack.count == -1;
}

// Name: isFull()
// Desc: Checks if the stack is full
// Input: const ArrayStack &stack
// Output: none
// Return: true if full
bool isFull(const ArrayStack &stack) {
    return stack.count == MAX_SIZE;
}

// Name: printvalues()
// Desc: Prints all the values in the stack formatted
// Input: const ArrayStack &stack
// Output: List of all values
// Return: none
void printValues(const ArrayStack &stack) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        cout << "Value at index " << i << ": " << stack.value[i] << endl;
    }
}