#include <iostream>

using namespace std;

struct ArrayStack {
    static const int MAX_SIZE = 10;
    int value[MAX_SIZE];
    int count;

    void push(ArrayStack &stack, int value) {
        // Check if stack is full
        if (!isFull(stack)) {
            // If not, shift elements right then add to front
            for (int i = MAX_SIZE - 2; i >= 0; --i) {
                stack.value[i + 1] = stack.value[i];
            }
            stack.value[0] = value;
            stack.count++;
        }
        else {
            cout << "Error: Stack is full!" << endl;
        }
        
    }

    int pop(ArrayStack &stack) {
        // Check if array is empty
        if (!isEmpty(stack)) {
            // Get first value
            int value = stack.value[0];

            // Update the array
            for (int i = 0; i < MAX_SIZE - 1; ++i) {
                stack.value[i] = stack.value[i + 1];
            }

            stack.count--;
            return value;

        }
        else {
            cout << "Error: Stack is empty!" << endl;
        }
    }

    int peek(ArrayStack stack) {
        if (!isEmpty(stack)) {
            return stack.value[0];
        }
        else {
            cout << "Error: Stack is empty!" << endl;
        }
    }

    bool isEmpty(const ArrayStack &stack) {
        return stack.count == -1;
    }

    bool isFull(const ArrayStack &stack) {
        return stack.count == stack.MAX_SIZE - 1;
    }

};

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

int main() {

    return 0;
}