/******************************************************************************
# Author:       Aiden Jungels
# Assignment:   Coding Assignment 5
# Date:         3/13/26
# Description:  A dungeon crawler game with 5 levels where the player must
#               move through all the levels one square at a time, collecting
#               treasure and avoiding the enmies
# Input:        char userName[], char userMove
# Output:       Each map as the player moves through it, a win screen with
#               point, death, and move statistics
******************************************************************************/
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int ROW = 10;
const int COL = 10;

struct Maps {
    char maps[5][ROW][COL];
    int curLevelIndex;
};

// Function Protoypes
void getUserName(char arr[]);
void welcome(char name[]);
void initializeMaps(Maps &levels);
void printMap(Maps &level, const int r);
char getMovement();
bool movePlayer(Maps &level, const int r, char move, int& curRow, int& curCol, int& score, int& numMoves, int& numDeaths);
void updateMapPos(Maps &level, int& curRow, int& curCol, int row, int col);
void resetMap(Maps &level, int& curRow, int& curCol);
void gameWinMessage(char userName[], int numPoints, int numMoves, int numDeaths);

// Main Function
int main() {
    // Map setup
    Maps levels;
    initializeMaps(levels);    

    // Variables Setup
    char userName[20];
    bool levelFinished = false;
    char userMove;
    int curRow = 1;
    int curCol = 1;
    // Statistics
    int numPoints = 0;
    int numMoves = 0;
    int numDeaths = 0;

    // Get name and display intro
    getUserName(userName);
    welcome(userName);
    
    // Main Game Loop 
    while (levels.curLevelIndex < 5) {
        levelFinished = false;
        while (!levelFinished) {
            printMap(levels, ROW);
            userMove = getMovement();
            levelFinished = movePlayer(levels, ROW, userMove, curRow, curCol, numPoints, numMoves, numDeaths);
        }
        cout << "=-=-= Level " << levels.curLevelIndex << " Completed! =-=-=" << endl << endl;
    }

    // End the Game
    gameWinMessage(userName, numPoints, numMoves, numDeaths);

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
    cout << "\tX : Enemy" << endl;
    cout << "\tT : Treasure" << endl << endl;
    cout << "\tO : Door to Next Level" << endl;
    // Display Controls
    cout << "\t=-=Controls=-=" << endl;
    cout << "\tw : Move Up" << endl;
    cout << "\ta : Move Left" << endl;
    cout << "\ts : Move Down" << endl;
    cout << "\td : Move Right" << endl << endl;
    // Display instructions
    cout << endl << "Your Goal is to get through all levels without touching enemies";
    cout << endl << "Collect as much treasure as you can along the way!" << endl;
}

void initializeMaps(Maps &levels) {
    levels.curLevelIndex = 0;
    
    // Create level arrays
    char level1[ROW][COL] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, 
        {'#', 'S', '.', '.', '.', '.', '#', 'X', 'T', '#'},
        {'#', '#', '#', '#', '#', '.', '.', '.', '.', '#'},
        {'#', '.', '.', '.', '#', '.', '#', '#', '#', '#'},
        {'#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
        {'#', 'T', '.', '.', '.', '.', '.', '#', 'T', '#'},
        {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#'},
        {'#', '.', '.', 'T', 'X', '#', '.', '.', 'O', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    char level2[ROW][COL] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, 
        {'#', 'S', '.', '.', 'X', 'T', '.', '.', 'T', '#'},
        {'#', '#', 'T', '.', '.', '.', 'X', '.', 'X', '#'},
        {'#', 'O', '#', '#', '#', '#', '#', '.', '#', '#'},
        {'#', '.', 'T', 'X', '.', 'T', '#', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '.', 'X', '#', '.', '#'},
        {'#', '.', 'X', 'T', '#', '.', 'T', 'X', '.', '#'},
        {'#', '.', '#', '.', '#', '.', '#', '.', 'T', '#'},
        {'#', '.', '.', '.', '#', '.', '.', 'T', 'X', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    char level3[ROW][COL] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, 
        {'#', 'S', 'T', '.', '.', '.', '.', 'X', 'O', '#'},
        {'#', '.', '#', '#', '.', 'X', 'T', '#', '.', '#'},
        {'#', '.', '#', 'T', '.', '#', '#', '#', '.', '#'},
        {'#', '.', '#', 'X', 'T', '#', 'T', '.', '.', '#'},
        {'#', '.', '.', 'T', 'X', '#', '.', '#', '#', '#'},
        {'#', '#', '.', '#', '#', '#', '.', '#', 'T', '#'},
        {'#', 'X', '.', '.', 'T', '#', '.', 'X', '.', '#'},
        {'#', 'T', '.', 'X', '.', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    char level4[ROW][COL] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, 
        {'#', 'S', '.', '.', 'T', '.', '.', '.', 'T', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
        {'#', 'T', '.', '.', '.', 'T', '.', '#', '.', '#'},
        {'#', '.', '#', '#', '#', '#', '.', '#', '.', '#'},
        {'#', '.', '#', 'O', 'X', '.', 'T', '#', '.', '#'},
        {'#', '.', '#', '.', 'T', '.', 'X', '#', '.', '#'},
        {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
        {'#', 'T', '.', '.', 'T', '.', '.', '.', 'T', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    char level5[ROW][COL] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, 
        {'#', 'S', '.', '.', '.', '.', 'T', '.', 'X', '#'},
        {'#', '.', 'T', 'X', 'T', '.', 'X', '.', 'T', '#'},
        {'#', '.', 'X', '.', 'X', 'T', '.', 'X', '.', '#'},
        {'#', 'T', '.', 'T', '.', 'X', '.', '.', 'T', '#'},
        {'#', 'X', '.', '.', '.', 'T', 'X', '.', '.', '#'},
        {'#', '.', 'T', 'X', '.', 'X', 'T', 'X', 'T', '#'},
        {'#', '.', 'X', '.', 'T', '.', '.', '.', 'X', '#'},
        {'#', 'T', '.', '.', 'X', 'T', 'X', '.', 'O', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };


    // Add to the maps struct
    for (int m = 0; m < 5; ++m) {
        for (int r = 0; r < ROW; ++r) {
            for (int c = 0; c < COL; ++c) {
                switch (m) {
                case 0:
                    levels.maps[m][r][c] = level1[r][c];
                    break;
                case 1:
                    levels.maps[m][r][c] = level2[r][c];
                    break;
                case 2:
                    levels.maps[m][r][c] = level3[r][c];
                    break;
                case 3:
                    levels.maps[m][r][c] = level4[r][c];
                    break;
                case 4:
                    levels.maps[m][r][c] = level5[r][c];
                    break;
                default:
                    break;
                }
            }
        }
    }
}

// Name: printMap()
// Desc: Displays the map in its current state
// Input: char map[][10], const int ROW
// Output: The map in its current state
// Return: none
void printMap(Maps &level, const int ROW) {
    cout << "----Current Map----" << endl;
    // Nested loop to print map row by row
    for (int r = 0; r < ROW; ++r) {
        for (int c = 0; c < 10; ++c) {
            cout << level.maps[level.curLevelIndex][r][c] << " ";
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
    }

    return input;
}

// Name: movePlayer()
// Desc: Moves the player to a new position based on their move choice
// Input: char map[][10], const int r, char move, int& curRow, int& curCol
// Output: Players movement choice, maybe invalid move message
// Return: bool levelFinished
bool movePlayer(Maps &level, 
                const int r, 
                char move, 
                int& curRow, 
                int& curCol, 
                int& score, 
                int& numMoves,
                int& numDeaths) 
{
    bool validMove = false;
    bool levelFinished = false;
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
            checkPos = level.maps[level.curLevelIndex][curRow - 1][curCol]; // get the index to check
            if (checkPos == '.' || checkPos == 'T') { // Confirm valid move
                updateMapPos(level, curRow, curCol,  -1, 0);
                validMove = true; // Confirm player has moved
            }
        }
        break;
    // Validate and move left
    case 'a':
        if (curCol > 1) {
            checkPos = level.maps[level.curLevelIndex][curRow][curCol - 1];
            if (checkPos == '.' || checkPos == 'T') {
                updateMapPos(level, curRow, curCol,  0, -1);
                validMove = true;
            }
        }
        break;
    // Validate and move down
    case 's':
        if (curRow < r) {
            checkPos = level.maps[level.curLevelIndex][curRow + 1][curCol];
            if (checkPos == '.' || checkPos == 'T') {
                updateMapPos(level, curRow, curCol,  1, 0);
                validMove = true;
            }
        }
        break;
    // Validate and move right
    case 'd':
        if (curCol < 10) {
            checkPos = level.maps[level.curLevelIndex][curRow][curCol + 1];
            if (checkPos == '.' || checkPos == 'T') {
                updateMapPos(level, curRow, curCol,  0, 1);
                validMove = true;
            }
        }
        break;
    default:
        break;
    }

    // Check if the player has won the game
    if (checkPos == 'O') {
        levelFinished = true;
        level.curLevelIndex += 1;
        curRow = 1;
        curCol = 1;
    }
    else if (checkPos == 'T') {
        // Update points
        ++score;
    }
    else if (checkPos == 'X') {
        // Reset level
        resetMap(level, curRow, curCol);
        ++numDeaths;
        validMove = true;
    }

    // Display an invalid move message if wasd input but square is a wall
    if (!validMove && !levelFinished) {
        cout << endl << "Sorry, that is not a valid move! Try again!" << endl;
    }

    // Update numMoves, this is based on inputs, rather than sucessful moves
    ++numMoves;

    return levelFinished;
}

// Name: updateMapPos()
// Desc: Helper fucntion to update the map once the player has input movement
// Input: char map[][10], int& curRow, int& curCol, int row, int col
// Output: None
// Return: None
void updateMapPos(Maps &level, int& curRow, int& curCol, int row, int col) {
    // Move player to the new spot (checkPos) and update 
    // player curRow/curCol control variable
    level.maps[level.curLevelIndex][curRow][curCol] = '.';
    curRow += row;
    curCol += col;
    level.maps[level.curLevelIndex][curRow][curCol] = 'S';
}

// Name: resetMap()
// Desc: Sends the player back to their spawn point when they die
// Input: Maps &level, int& curRow, int& curCol
// Output: You died message
// Return: None
void resetMap(Maps &level, int& curRow, int& curCol) {
    level.maps[level.curLevelIndex][curRow][curCol] = '.';
    curRow = 1;
    curCol = 1;
    level.maps[level.curLevelIndex][curRow][curCol] = 'S';
    cout << endl << "You Died! Respawning..." << endl;
}

// Name: gameWinMessage()
// Desc: Displays the game win message
// Input: char userName[]
// Output: Game win line and ascii art
// Return: none
void gameWinMessage(char userName[], int numPoints, int numMoves, int numDeaths) {
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
    cout << "\t\t\t    You Got " << numPoints << " points!" << endl;
    cout << "\t\t\t    You made " << numMoves << " moves!" << endl;
    cout << "\t\t\t    You Died " << numDeaths << " times!" << endl;
    cout << endl << "Thank you for playing!" << endl;

}