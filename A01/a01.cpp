/******************************************************************************
# Author:       Aiden Jungels
# Assignment:   Coding Assignment 1
# Date:         1/13/26
# Description:  This program asks the user to enter 0-100 scores, then
#               provides a menu with various options to view data from the
#               scores input
# Input:        int numScores, int score, int menuChoice, int threshold
# Output:       int scores[], int maxScore, int minScore, int avgScore,
#               int numAboveThreshold
******************************************************************************/
#include <iostream>

using namespace std;

// Function prototypes
void welcome();
int getArrayInput(int (&arr)[100]);
void displayMenu();
int getMenuInput();
int getThreshold();
void printScores(int arr[], int size);
int findMax(int arr[], int size);
int findMin(int arr[], int size);
double calculateAverage(int arr[], int size);
int countAboveThreshold(int arr[], int size, int threshold);

int main() {

    // Variable setup
    int scores[100];
    int numScores = 0;
    int menuChoice = 0;
    int maxScore = 0;
    int minScore = 0;
    double avgScore = 0.0;
    int threshold = 0;
    int numAvoveThreshold = 0;

    // Welcome message
    welcome();

    // Get inputs from user
    numScores = getArrayInput(scores);

    // Loop main program
    do {
        // Display menu and get menu choice
        displayMenu();
        menuChoice = getMenuInput();
        cout << endl;

        switch (menuChoice)
        {
            case 1:
                printScores(scores, numScores);
                break;
            case 2:
                maxScore = findMax(scores, numScores);
                cout << "The maximum score is: " << maxScore << endl;
                break;
            case 3:
                minScore = findMin(scores, numScores);
                cout << "The minimum score is: " << minScore << endl;
                break;
            case 4:
                avgScore = calculateAverage(scores, numScores);
                cout << "The average of all scores is: " << avgScore << endl;
                break;
            case 5:
                threshold = getThreshold();
                numAvoveThreshold = countAboveThreshold(scores, numScores, threshold);
                cout << endl << "The number of scores above the threshold of ";
                cout << threshold << " is: " << numAvoveThreshold << endl;
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
        cout << "Please enter the next score (integer): ";
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
    cout << "===== Menu =====" << endl;
    cout << "1. Print all Scores" << endl;
    cout << "2. Find Maximum Score" << endl;
    cout << "3. Find Minimum Score" << endl;
    cout << "4. Calculate Average" << endl;
    cout << "5. Count scores above a certain threshhold" << endl;
    cout << "0. Quit" << endl;
}

// Name: getMenuInput()
// Desc: Gets the users menu choice
// Input: none
// Output: Input prompt, maybe error message
// Return: int menuChoice
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

// Name: printScores()
// Desc: Displays all the scores in a grid of 5 scores per row
// Input: int arr[], int size
// Output: Grid of all scores
// Return: none
void printScores(int arr[], int size) {
    cout << endl << "  --Table of all scores input--" << endl;
    
    // Outer loop to control what index is being printed
    for (int i = 0; i < size; i += 5) {
        // Inner loop to control num prints per row
        for (int j = 0; j < 5; ++j) {
            // Only print if value is in the array
            if (i + j < size) {
                cout << arr[i + j] << "\t";
            }
        }
        cout << endl;
    }
}

// Name: findMax()
// Desc: Returns the highest score in the array
// Input: int arr[], int size
// Output: No scores message if no scores
// Return: int maxScore
int findMax(int arr[], int size) {
    int maxScore = 0;

    // Loop if there are any scores, otherwise display no scores message
    if (size > 0) {
        for (int i = 0; i < size; ++i) {
            // Check if score is greater than max
            if ((arr[i] > maxScore) || (i == 0)) {
                maxScore = arr[i];
            }
        }
    }
    else {
        cout << "No scores were entered, so there is no max score." << endl;
    }

    return maxScore;
}

// Name: findMin()
// Desc: Returns the lowest score in the array
// Input: int arr[], int size
// Output: No scores message if no scores
// Return: int minScore
int findMin(int arr[], int size) {
    int minScore = 0;

    // Loop if there are any scores, otherwise display no scores message
    if (size > 0) {
        for (int i = 0; i < size; ++i) {
            // Check if score is smaller than min
            if ((arr[i] < minScore) || (i == 0)) {
                minScore = arr[i];
            }
        }
    }
    else {
        cout << "No scores were entered, so there is no min score." << endl;
    }

    return minScore;
}

// Name: calculateAverage()
// Desc: returns the average of all scores
// Input: int arr[], int size
// Output: none
double calculateAverage(int arr[], int size) {
    double avg = 0.0;
    int total = 0;

    // Loop through and add scores to total
    for (int i = 0; i < size; ++i) {
        total += arr[i];
    }

    avg = static_cast<double>(total) / size;

    return avg;
}

// Name: getThreshold()
// Desc: Gets the threshold value to search for later
// Input: none
// Output: threshold prompt, maybe error message
int getThreshold() {
    int threshold = 0;
    
    // Get and validate threshold input
    cout << "Enter the threshold in which scores must be above: ";
    cin >> threshold;
    
    while (!cin) {
        cout << "Please enter an integer!" << endl;
        cout << ">> ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> threshold;
    }

    return threshold;
}

// Name: countAboveThreshold
// Desc: Counts each score that is above a given threshold
// Input: int arr[], int size, int threshold
// Output: none
int countAboveThreshold(int arr[], int size, int threshold) {
    int numScoresAbove = 0;

    for (int i = 0; i < size; ++i) {
        if (arr[i] > threshold) {
            ++numScoresAbove;
        }
    }

    return numScoresAbove;
}