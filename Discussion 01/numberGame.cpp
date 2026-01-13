/******************************************************************************
# Author:       Aiden Jungels
# Assignment:   Discussion 01
# Date:         1/10/2026
# Description:  This is a number guessing game where the user enters their 
#               high and low bounds, then guesses a number until they guess 
#               the correct one. They will be toldif their guess is too high 
#               or too low, and thenumber of attempts will be kept track of 
#               and displayedat the end.
# Input:        int lowBound, int highBound, int guess
# Output:       int answer, int numTries
******************************************************************************/
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// Function prototypes
void welcome();
int getInput(string prompt);
int gameSetup(int& high, int& low);
int playGame(int answer, int high, int low);
void displayResults(int answer, int attempts);

// Main Function
int main() {
    int highBound = 0;
    int lowBound = 0;
    int answer = 0;
    int numTries = 0;

    // Welcome Message
    welcome();

    // Set up the game
    answer = gameSetup(highBound, lowBound);
    cout << endl << "The random number has been chosen!" << endl << endl;

    // Play the game
    numTries = playGame(answer, highBound, lowBound);

    // Display results
    displayResults(answer, numTries);

    return 0;
}

// Name: welcome()
// Desc: Displays welcome message
// Input: none
// Output: welcome message
// Return: none
void welcome() {
    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "You will enter a custom range for the random number" << endl;
    cout << "And then guess until you get the correct number!" << endl << endl;
}

// Name: getInput()
// Desc: Gets an integer input from the user and validates it
// Input: string prompt
// Output: prompt, error message
// Return: int input
int getInput(string prompt) {
    int input;
    
    // Prompt and get input
    cout << prompt;
    cin >> input;

    // Data validation
    while (!cin) {
        cout << "Invalid Input! Please try again." << endl;
        cout << ">> ";
        cin >> input;
    }

    return input;
}

// Name: gameSetup()
// Desc: Sets the low/high bounds, generates answer
// Input: int& high, int& low
// Output: none
// Return: int answer (as random number within bounds)
int gameSetup(int& high, int& low) {
    // Get bounds
    low = getInput("Enter the low bound (inclusive): ");
    high = getInput("Enter the high bound (inclusive): ");

    srand(time(NULL));
    
    // Generate the answer
    return rand() % (high - low + 1) + low;
}

// Name: playGame()
// Desc: Main loop to run the guessing game
// Input: int answer, int high, int low
// Output: Various guess info statements to aid guessing
// Return: int numTries
int playGame(int answer, int high, int low) {
    int guess;
    int numTries = 0;
    string guessPrompt;
    string highStr = to_string(high);
    string lowStr = to_string(low);

    guessPrompt = "Enter your guess (" + lowStr + " to " + highStr + "): ";

    // Initial Guess
    guess = getInput(guessPrompt);

    // Loop while guess is incorrect
    while (guess != answer) {
        // Only incrument tries if guess is within bounds
        if ((guess < low) || (guess > high)) {
            guess = getInput("Guess out of bounds! Guess again: ");
        }
        else {
            // Display if guess is to high or too low
            if (guess < answer) {
                cout << "Incorrect! The answer is greater than ";
                cout << guess << endl;
            }
            else if (guess > answer) {
                cout << "Incorrect! The answer is less than ";
                cout << guess << endl;
            }

            // Get next input and incriment tries
            guess = getInput(guessPrompt);
            numTries++;
        }
    }
    
    // Final incrimnent for correct guess
    numTries++;
    return numTries;
    
}

// Name: displayResults()
// Desc: Displays end game and how many tries it took
// Input: int answer, int attempts
// Output: Game statistics and goodbye message
// Return: none
void displayResults(int answer, int attempts) {
    cout << endl << "You got it right! ";
    cout << "The answer was " << answer << "!" << endl;

    // Altered output if guessed in one attempt
    if (attempts == 1) {
        cout << "You guessed the answer on the first try! Congratulations!";
    } else {
        cout << "It took you " << attempts;
        cout << " tries to get the answer!" << endl;
    }
    
    cout << endl << "Thank you for playing!" << endl;
}