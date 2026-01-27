/******************************************************************************
# Author:       Aiden Jungels
# Assignment:   Coding Assignment 2
# Date:         1/26/26
# Description:  This program is a text dungeon game where the user is
#               given a map and has to move through it via char input to reach
#               the treasure
# Input:        char userName[], char userMove
# Output:       map[][], char userMove, char userName[]
******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

// Function Protoypes
void getUserName(char arr[]);
void welcome(char name[]);
void printMap(char map[][10], const int r);
char getMovement();
bool movePlayer(char map[][10], const int r, char move, int& curRow, int& curCol);
void gameWinMessage(char userName[]);

// Main Function
int main() {
    // Map setup
    const int ROW = 10;
    const int COL = 10;
    char map[ROW][COL] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, 
        {'#', 'S', '.', '.', '.', '.', '#', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '.', '.', '.', '.', '#'},
        {'#', '.', '.', '.', '#', '.', '#', '#', '#', '#'},
        {'#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#'},
        {'#', '.', '.', '.', '.', '#', '.', '.', 'T', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

    // Variables Setup
    char userName[20];
    bool win = false;
    char userMove;
    int curRow = 1;
    int curCol = 1;

    // Get name and display intro
    getUserName(userName);
    welcome(userName);
    
    // Main Game Loop 
    while (!win) {
        printMap(map, ROW);
        userMove = getMovement();
        win = movePlayer(map, ROW, userMove, curRow, curCol);
        
    }

    // End the Game
    printMap(map, ROW);
    gameWinMessage(userName);

    return 0;
}

// Name: getUserName()
// Desc: Gets the users name 
// Input: char arr[]
// Output: Name Prompt
// Return: none
void getUserName(char arr[]) {
    cout << "Please enter your name: ";
    cin.getline(arr, 20);
}

// Name: welcome()
// Desc: Displays welcome message and game instructions
// Input: none
// Output: welcome message / instructions
// Return: none
void welcome(char name[]) {
    // Display welcome Message
    cout << "Welcome " << name << ", Brave Adventurer, to:" << endl;
    cout << "=-=-=THE MINI TEXT DUNGEON!=-=-=" << endl;
    // Display Key
    cout << "\t=-=Map Key=-=" << endl;
    cout << "\t# : Walls" << endl;
    cout << "\t. : Open Spaces" << endl;
    cout << "\tS : Player Position" << endl;
    cout << "\tT : Treasure" << endl << endl;
    // Display Controls
    cout << "\t=-=Controls=-=" << endl;
    cout << "\tw : Move Up" << endl;
    cout << "\ta : Move Left" << endl;
    cout << "\ts : Move Down" << endl;
    cout << "\td : Move Right" << endl << endl;
}

// Name: printMap()
// Desc: Displays the map in its current state
// Input: char map[][10], const int ROW
// Output: The map in its current state
// Return: none
void printMap(char map[][10], const int ROW) {
    cout << "----Current Map----" << endl;
    // Nested loop to print map row by row
    for (int r = 0; r < ROW; ++r) {
        for (int c = 0; c < 10; ++c) {
            cout << map[r][c] << " ";
        }
        cout << endl;
    }
}

// Name: getMovement()
// Desc: Gets and validates the players next movement choice
// Input: none
// Output: Input prompt, maybe error message
// Return: char input
char getMovement() {
    char input;
    
    // Get Input
    cout << endl << "How would you like to move?: ";
    cin >> input;
    input = tolower(input);
    
    // Check for valid option
    while (!cin || (
            (input != 'w') && 
            (input != 'a') && 
            (input != 's') && 
            (input != 'd')
    )) {
        // Display error message and get new input
        cout << "Please only enter w, a, s, d! Try Again" << endl;
        cout << ">> ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> input;
        input = tolower(input);
        cout << "Input is: " << input << endl;
    }

    return input;
}

// Name: movePlayer()
// Desc: Moves the player to a new position based on their move choice
// Input: char map[][10], const int r, char move, int& curRow, int& curCol
// Output: Players movement choice, maybe invalid move message
// Return: bool gameWon
bool movePlayer(char map[][10], 
                const int r, 
                char move, 
                int& curRow, 
                int& curCol) 
{
    bool validMove = false;
    bool gameWon = false;
    char checkPos;
    
    // Display players move
    cout << endl << "Your Move is: " << move << endl;
    
    // Check and move player - All cases function the same, just
    // change what index is being checked based on which
    // way the player is moving
    switch (move) {
    // Validate and move up
    case 'w':
        if (curRow > 1) {
            checkPos = map[curRow - 1][curCol]; // get the index to check
            if (checkPos == '.' || checkPos == 'T') { // Confirm valid move
                // Move player to the new spot (checkPos) and update 
                // player curRow/curCol control variable
                map[curRow][curCol] = '.';
                curRow -= 1;
                map[curRow][curCol] = 'S';
                validMove = true; // Confirm player has moved
            }
        }
        break;
    // Validate and move left
    case 'a':
        if (curCol > 1) {
            checkPos = map[curRow][curCol - 1];
            if (checkPos == '.' || checkPos == 'T') {
                map[curRow][curCol] = '.';
                curCol -= 1;
                map[curRow][curCol] = 'S';
                validMove = true;
            }
        }
        break;
    // Validate and move down
    case 's':
        if (curRow < r) {
            checkPos = map[curRow + 1][curCol];
            if (checkPos == '.' || checkPos == 'T') {
                map[curRow][curCol] = '.';
                curRow += 1;
                map[curRow][curCol] = 'S';
                validMove = true;
            }
        }
        break;
    // Validate and move right
    case 'd':
        if (curCol < 10) {
            checkPos = map[curRow][curCol + 1];
            if (checkPos == '.' || checkPos == 'T') {
                map[curRow][curCol] = '.';
                curCol += 1;
                map[curRow][curCol] = 'S';
                validMove = true;
            }
        }
        break;
    default:
        break;
    }

    // Check if the player has won the game
    if (checkPos == 'T') {
        gameWon = true;
    }

    // Display an invalid move message if wasd input but square is a wall
    if (!validMove && !gameWon) {
        cout << endl << "Sorry, that is not a valid move! Try again!" << endl;
    }

    return gameWon;
}

// Name: gameWinMessage()
// Desc: Displays the game win message
// Input: char userName[]
// Output: Game win line and ascii art
// Return: none
void gameWinMessage(char userName[]) {
    cout << endl;
    cout << "\t\t=-=-=Congratulations Brave Adventurer ";
    cout << userName << "!=-=-=" << endl;
    cout << R"(
                __   __             __        __ _         _ 
                \ \ / /___   _   _  \ \      / /(_) _ __  | | 
                 \ V // _ \ | | | |  \ \ /\ / / | || '_ \ | |  
                  | || (_) || |_| |   \ V  V /  | || | | ||_|  
                  |_| \___/  \__,_|    \_/\_/   |_||_| |_|(_)
            )" << endl;
    cout << endl << "Thank you for playing!" << endl;

}