/******************************************************************************
# Author:       Aiden Jungels
# Assignment:   
# Date:         
# Description:  
# Input:        
# Output:       
******************************************************************************/
#include <iostream>

using namespace std;

// Function prototypes
void welcome();
int getArrayInput(int (&arr)[100]);
void displayMenu();
int getMenuInput();
// Calculation Functions
void printScores(int arr[], int size);
int findMax(int arr[], int size);
int findMin(int arr[], int size);
double calculateAverage(int arr[], int size);
int countAboveThreshhold(int arr[], int size, int thresholdd);

int main() {

    // Variable setup
    int scores[100];
    int numScores = 0;
    int menuChoice = 0;

    // Welcome message
    welcome();

    // Get inputs from user
    numScores = getArrayInput(scores);

    // Loop main program
    do {
        // Display menu and get menu choice
        displayMenu();
        menuChoice = getMenuInput();

        switch (menuChoice)
        {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            default:
                break;
        }

    } while (menuChoice != 0);

    cout << endl << "Thank you for using the Score Manager!" << endl;


    return 0;
}

// Name: welcome()
// Desc: Displays welcome message
// Input: none
// Output: welcome message
// Return: none
void welcome() {
    cout << "Welcome to the Score Manager!" << endl;
    cout << "Once you enter scores, you can preform calculations!" << endl;
    cout << endl;
}

// Name: getArrayInput()
// Desc: Gets the number of scores and adds each score value to the array
// Input: int &arr[100]
// Output: Input prompt, maybe error message
// Return: none
int getArrayInput(int (&arr)[100]) {
    int numInputs = 0;
    int nextScore = 0;

    cout << "Please enter the number of scores you would like to enter";
    cout << " (0-100): ";
    cin >> numInputs;

    // Input data vailidation
    while (!cin || (numInputs < 0) || (numInputs > 100)) {
        cout << "Please enter a number between 0-100!" << endl;
        cout << ">> ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> numInputs;
    }

    // Loop and add inputs
    for (int i = 0; i < numInputs; ++i) {
        // Get score input and validate
        cout << "Please enter a score (integer): ";
        cin >> nextScore;

        while (!cin) {
            cout << "Please enter an integer!" << endl;
            cout << ">> ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> nextScore;
        }
        
        // Add score input to array
        arr[i] = nextScore;
    }

    return numInputs;
}

// Name: displayMenu()
// Desc: Displays the program menu
// Input: none
// Output: program menu
// Return: none
void displayMenu() {
    cout << endl;
    cout << "1. Print all Scores" << endl;
    cout << "2. Find Maximum Score" << endl;
    cout << "3. Find Minimum Score" << endl;
    cout << "4. Calculate Average" << endl;
    cout << "5. Count scores above a certain threshhold" << endl;
    cout << "0. Quit" << endl;
}

int getMenuInput() {
    int menuChoice = 0;
    
    // Get and validate menu input
    cout << endl << "Enter your choice: ";
    cin >> menuChoice;

    while (!cin || (menuChoice < 0) || (menuChoice > 5)) {
        cout << "Please enter a valid choice (0-5)" << endl;
        cout << ">> ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> menuChoice;
    }

    return menuChoice;
}