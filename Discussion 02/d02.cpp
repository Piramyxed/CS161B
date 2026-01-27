/******************************************************************************
# Author:           Jason Pelkey and Aiden Jungels
# Lab:              Discussion #2
# Date:             January 15, 2026
# Description:      Creates a strong password using a word, a number, and a
#                    unique character
# Input:            phrase (char[]) - A unique word or phrase
#                   number (char[] [len <= 4]) - A number under 5 digits
#                   character (char) - A single character
# Output:           password (char[]) - The password generated
# Sources:          Zybooks Chapter 10, Discussion 2 Assignment
#******************************************************************************/

#include <iostream>
using namespace std;

// Function prototypes
void welcome();
int getSize();
void getArrValues(int arr[], int length);
void getStartEnd(int &start, int &end, int length);
bool checkOrder(int arr[], int start, int end);

int main() {

  int numbers[20] = {};
  int start = 0;
  int end = 0;
  int size = 0;

  welcome();

  size = getSize();
  getArrValues(numbers, size);
  getStartEnd(start, end, size);

  bool isSorted = checkOrder(numbers, start, end);
  cout << (isSorted ? "yes" : "no") << endl;

  return 0;
}

void welcome() { cout << "Welcome to the array sorting checker!" << endl; }

int getSize() {
  int size;

  // Display prompt and get input
  cout << "Please enter the number of integers: ";
  cin >> size;

  // Data validation
  while (!cin) {
    cout << "Please enter an integer!";
    cout << ">> ";
    cin.clear();
    cin.ignore(100, '\n');
    cin >> size;
  }

  return size;
}

void gerArrValues(int arr[], int length) {
  cout << "Enter the values: ";
  // Loop through each item and add it to the array
  for (int i = 0; i < length; ++i) {
    cin >> arr[i];
  }
}

void getStarEnd(int &start, int &end, int length) {
  // Display prompt and get input
  cout << "Enter the start and end index: ";
  cin >> start;
  cin >> end;

  // Validate for start index
  while (!cin || start < 0) {
    cout << "Please enter a valid starting number (above 0): ";
    cin.clear();
    cin.ignore(100, '\n');
    cin >> start;
  }

  // Validate for end index
  while (!cin || end > length) {
    cout << "Please enter a valid ending index (less than " << length << "): ";
    cin.clear();
    cin.ignore(100, '\n');
    cin >> end;
  }
}

bool checkOrder(int arr[], int start, int end) {

  int prevValue = 0;
  int curValue = 0;
  bool isSorted = true;

  // Loop through specified range within the array
  for (int i = start; i <= end; i++) {

    // Set first value if not yet populated
    if (i == start) {
      prevValue = arr[i];
    } else { // Otherwise, compare prevValue with current array value
      curValue = arr[i];
      if (curValue < prevValue) { // Next value was less than prev value
        isSorted = false;         // meaning it is not sorted
      }
      prevValue = curValue;
    }
  }

  return isSorted;
}