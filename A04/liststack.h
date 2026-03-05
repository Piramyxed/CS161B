#ifndef LISTSTACK_H
#define LISTSTACK_H

struct ListStack {
    int value;
    ListStack* next;
};

// Function Prototypes
void push(ListStack* &stack, int value);
int pop(ListStack* &stack);
int peek(const ListStack* stack);
bool isEmpty(const ListStack* stack);
void printStack(ListStack* stack);

#endif