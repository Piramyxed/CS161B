#include <iostream>
#include "arraystack.cpp"

using namespace std;

struct ListStack {
    int value;
    ListStack* next;

    void push(ListStack* &stack, int value) {

    }

    int pop(ListStack* &stack) {

    }

    int peek(const ListStack* stack) {

    }

    bool isEmpty(const  ListStack* stack) {

    }

};

// Function prototypes
void welcome();
void testArrayStack(ArrayStack &stack);
void testListStack();

int main() {

    // Setup stack structs
    ArrayStack arrayStack;

    welcome();

    // test the array stack implimentation
    cout << endl << "=-=-=-= First, the Array Stack =-=-=-=" << endl;
    testArrayStack(arrayStack);

    return 0;
}

void welcome() {
    cout << "Welcome to the Array and Linked List stack program!" << endl;
}

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

void testListStack();