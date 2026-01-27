/******************************************************************************
# Author:       Aiden Jungels
# Assignment:   Coding Assignment 2
# Date:         1/26/26
# Description:  
# Input:        
# Output:       
******************************************************************************/
#include <iostream>

using namespace std;

// Function Protoypes
void getUserName(char arr[]);
void welcome(char name[]);
void printMap(char map[][10], const int r);
char getMovement();
bool movePlayer(char map[][10], const int r, char move, int& curRow, int& curCol);
void gameWinMessage(char userName[]);

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
    gameWinMessage(userName);
    welcome(userName);
    
    // Main Game Loop 
    while (!win) {
        printMap(map, ROW);
        userMove = getMovement();
        win = movePlayer(map, ROW, userMove, curRow, curCol);
        
    }

    gameWinMessage(userName);

    return 0;
}

void getUserName(char arr[]) {
    cout << "Please enter your name: ";
    cin.getline(arr, 20);
}

void welcome(char name[]) {
    // Display welcome Message
    cout << "Welcome " << name << ", Brave Adventurer, to:" << endl;
    cout << "====THE MINI TEXT DUNGEON!====" << endl;
    // Display Key
    cout << "\t==Map Key==" << endl;
    cout << "\t# : Walls" << endl;
    cout << "\t. : Open Spaces" << endl;
    cout << "\tS : Player Position" << endl;
    cout << "\tT : Treasure" << endl << endl;
    // Display Controls
    cout << "\t==Controls==" << endl;
    cout << "\tw : Move Up" << endl;
    cout << "\ta : Move Left" << endl;
    cout << "\ts : Move Down" << endl;
    cout << "\td : Move Right" << endl << endl;
}

void printMap(char map[][10], const int ROW) {
    cout << "----Current Map----" << endl;
    for (int r = 0; r < ROW; ++r) {
        for (int c = 0; c < 10; ++c) {
            cout << map[r][c] << " ";
        }
        cout << endl;
    }
}

char getMovement() {
    char input;
    
    // Get Input
    cout << endl << "How would you like to move?: ";
    cin >> input;
    tolower(input);
    
    // Check for valid option
    while (!cin || (
            (input != 'w') && 
            (input != 'a') && 
            (input != 's') && 
            (input != 'd')
    )) {
        cout << "Please only enter w, a, s, d! Try Again" << endl;
        cout << ">> ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> input;
        tolower(input);
        cout << "Input is: " << input << endl;
    }

    return input;
}

bool movePlayer(char map[][10], 
                const int r, 
                char move, 
                int& curRow, 
                int& curCol) 
{
    bool validMove = false;
    bool gameWon = false;
    char checkPos;
    cout << "Your Move is: " << move << endl;
    switch (move)
    {
    // Validate and move up
    case 'w':
        if (curRow > 1) {
            checkPos = map[curRow - 1][curCol];
            if (checkPos == '.') {
                map[curRow][curCol] = '.';
                curRow -= 1;
                map[curRow][curCol] = 'S';
                validMove = true;
            }
            else if (checkPos == 'T') {
                gameWon = true;
            }
        }
        break;
    // Validate and move left
    case 'a':
        if (curCol > 1) {
            checkPos = map[curRow][curCol - 1];
            if (checkPos == '.') {
                map[curRow][curCol] = '.';
                curCol -= 1;
                map[curRow][curCol] = 'S';
                validMove = true;
            }
            else if (checkPos == 'T') {
                gameWon = true;
            }
        }
        break;
    // Validate and move down
    case 's':
        if (curRow < r) {
            checkPos = map[curRow + 1][curCol];
            if (checkPos == '.') {
                map[curRow][curCol] = '.';
                curRow += 1;
                map[curRow][curCol] = 'S';
                validMove = true;
            }
            else if (checkPos == 'T') {
                gameWon = true;
            }
        }
        break;
    // Validate and move right
    case 'd':
        if (curCol < 10) {
            checkPos = map[curRow][curCol + 1];
            if (checkPos == '.') {
                map[curRow][curCol] = '.';
                curCol += 1;
                map[curRow][curCol] = 'S';
                validMove = true;
            }
            else if (checkPos == 'T') {
                gameWon = true;
            }
        }
        break;
    
    default:
        break;
    }

    if (!validMove && !gameWon) {
        cout << endl << "Sorry, that is not a valid move! Try again!" << endl;
    }

    return gameWon;
}

void gameWinMessage(char userName[]) {
    cout << endl;
    cout << "\t    ====Congratulations Brave Adventurer ";
    cout << userName << "!====" << endl;
    cout << R"(
                __   __           __        ___       _ 
                \ \ / /__  _   _  \ \      / (_)_ __ | | 
                 \ V / _ \| | | |  \ \ /\ / /| | '_ \| |  
                  | | (_) | |_| |   \ V  V / | | | | |_|  
                  |_|\___/ \__,_|    \_/\_/  |_|_| |_(_)
            )" << endl;

}