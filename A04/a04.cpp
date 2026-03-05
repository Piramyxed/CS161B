/******************************************************************************
# Author:       Aiden Jungels
# Assignment:   A04
# Date:         3/4/26
# Description:  This program creates and manages both an Array Stack and a
#               linked list stack, then preforms a series of Push, Pop, and 
#               seek operations on both versions, displaying the results 
#               along the way.
# Input:        None
# Output:       Various displays of Stack operations
# Sources:      CS161B Github repo
******************************************************************************/
#include <iostream>
#include "arraystack.h"
#include "liststack.h"

using namespace std;

// Function prototypes
void welcome();
void testArrayStack(ArrayStack &stack);
void testListStack(ListStack* &stack);

// Main Function
int main() {

    // Setup stack structs
    ArrayStack arrayStack;
    ListStack* listStack = nullptr;

    welcome();

    // Test the array stack implimentation
    cout << endl << "=-=-=-= First, the Array Stack =-=-=-=" << endl;
    testArrayStack(arrayStack);

    // Test linked list stack implimentation
    cout << endl << "=-=-=-= Next, the Linked List Stack =-=-=-=" << endl;
    testListStack(listStack);

    cout << endl << "=-=-=-= Thank you for using the Array and "
         << "Linked List demonstrator! =-=-=-=" << endl;

    return 0;
}

// Name: welcome()
// Desc: Displays welcome message
// Input: none
// Output: Welcome message
// Return: none
void welcome() {
    cout << "Welcome to the Array and Linked List stack program!" << endl;
}

// Name: testArrayStack()
// Desc: Does all the tests on the array stack function
// Input: ArrayStack &stack
// Output: Results of all the operations
// Return: none
void testArrayStack(ArrayStack &stack) {
    initStack(stack);

    // Push 5 values
    cout << "=-=-= Pushing 5 values to the stack =-=-=" << endl;
    for (int i = 0; i < 5; ++i) {
        push(stack, i);
        cout << "Value at index " << i << ": " << stack.value[i] << endl;
    }

    // Peek a value
    cout << endl << "=-=-= Peek the current stack =-=-=" << endl;
    int peekVal = peek(stack);
    cout << "Expecting: 4 -- Got: " << peekVal << endl;

    // Attempt to push 6 values
    cout << endl << "=-=-= Attempting to push too many values =-=-=" << endl;
    for (int i = 5; i < 11; ++i) {
        push(stack, i);
        if (i < 10) {
            cout << "Value at index " << i << ": " << stack.value[i] << endl;
        }
        else {
            cout << "Unable to push further values" << endl;
        }
    }

    // Print out the array
    cout << endl << "=-=-= Printing out the current stack =-=-=" << endl;
    printValues(stack);

    // Pop some values
    cout << endl << "=--=-= Popping 3 values =-=-=" << endl;
    int poppedVal = 0;
    for (int i = 0; i < 3; ++i) {
        poppedVal = pop(stack);
        cout << "Value popped: " << poppedVal << endl;
    }

    // Add new values
    cout << endl << "=-=-= Adding new values to the end =-=-=" << endl;
    for (int i = 7; i < 10; ++i) {
        push(stack, i + 10);
        cout << "Value at index " << i << ": " << stack.value[i] << endl;
    }

    // Print final array
    cout << endl << "=-=-= Final Array Stack =-=-=" << endl;
    printValues(stack);
    
}

// Name: testListStack()
// Desc: Tests the linked list stack opetations
// Input: ListStack* &stack
// Output: Results of the various operations
// Return: none
void testListStack(ListStack* &stack) {

    // Push 5 values
    cout << endl << "=-=-= Pushing 5 values to the stack =-=-=" << endl;
    for (int i = 0; i < 5; ++i) {
        push(stack, i);
    }
    printStack(stack);

    // Peek a value
    cout << endl << "=-=-= Peek the current stack =-=-=" << endl;
    int peekedVal = peek(stack);
    cout << "Peeked Value: " << peekedVal << endl;
    
    // Push new values
    cout << endl << "=-=-= Pushing 5 more values to the stack =-=-=" << endl;
    for (int i = 10; i < 15; ++i) {
        push(stack, i);
    }
    printStack(stack);

    // Pop some values
    cout << endl << "=--=-= Popping 3 values =-=-=" << endl;
    int poppedVal = 0;
    for (int i = 0; i < 3; ++i) {
        poppedVal = pop(stack);
        cout << "Value popped: " << poppedVal << endl;
    }
    printStack(stack);

    // Add another value
    cout << endl << "=--=-= Adding a final Value =-=-=" << endl;
    push(stack, 20);
    printStack(stack);
}