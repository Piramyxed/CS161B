/******************************************************************************
# Author:       Aiden Jungels
# Assignment:   A03
# Date:         2/20/26
# Description:  This program asks the user for 
# Input:        char fileName (image as .ppm file to open)
# Output:       output.ppm file (writes modified image data)
# Sources:      https://stackoverflow.com/questions/655065/
                when-should-i-use-the-new-keyword-in-c
                https://www.geeksforgeeks.org/cpp/
                new-and-delete-operators-in-cpp-for-dynamic-memory/
******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Pixel Data struct
struct Pixel {
    int r;
    int g;
    int b;
};

// Image Data struct
struct Image {
    int width;
    int height;
    int maxColorVal;
    Pixel** pixels;
};

const int MAX_FILE_NAME = 101;

// Function Prototypes
void welcome();
bool openImageFile(ifstream &inImage);
bool getImageStats(ifstream &inImage, Image &image);
Pixel** parseImageFile(ifstream &inImage, const Image &image);
int programMenu();
void applyImageFlip(Image &image);
void applyGrayscale(Image &image);
void printNewImage(const Image &image);

// Main Function
int main() {
    ifstream inImage;
    Image image;

    welcome();

    // Attempt to open image
    if (openImageFile(inImage)) {
        // Read header of image file
        if (getImageStats(inImage, image)) {

            int userChoice = programMenu();

            if (userChoice != 0) {
                // Parse image into struct
                image.pixels = parseImageFile(inImage, image);

                // Apply Transformation
                if (userChoice == 1) {
                    applyImageFlip(image);
                }
                else if (userChoice == 2) {
                    applyGrayscale(image);
                }

                // Write image to file
                printNewImage(image);
                
                // Clear memory from pointer array
                for (int i = 0; i < image.height; ++i) {
                    delete[] image.pixels[i];
                }
                delete[] image.pixels;
            }
        }
    }

    inImage.close();
    cout << endl << "Thank you for using!" << endl;
    return 0;
}

// Name: welcome()
// Desc: Displays welcome message
// Input: none
// Output: Welcome message
// Return: none
void welcome() {
    cout << "Welcome to the P3 Image manipulator!" << endl;
}

// Name: openImageFile()
// Desc: Opens an image file, displays error if fail
// Input: ifstream &inImage
// Output: Input prompt, maybe error message
// Return: bool validOpen
bool openImageFile(ifstream &inImage) {
    char fileName[MAX_FILE_NAME];
    bool validOpen = true;

    // Get file name to open
    cout << "Enter the image file name to open: ";
    cin >> fileName;

    // Open and check file
    inImage.open(fileName);
    if (!inImage.is_open()) {
        cout << "Error opening " << fileName << ". Program exiting." << endl;
        validOpen = false;
    }

    return validOpen;
}


// Name: getImageStats()
// Desc: Gets all the header stats of the image
// Input: ifstream &inImage, Image &image
// Output: Maybe error message
// Return: bool validImage
bool getImageStats(ifstream &inImage, Image &image) {
    char fileHeader[3];
    bool validImage = true;

    // Get all the header data, fileHeader is a throwaway value
    inImage >> fileHeader;
    inImage >> image.width;
    inImage >> image.height;
    inImage >> image.maxColorVal;

    // Confirm that all header stats are valid
    if ((image.width < 0) || 
        (image.height < 0) || 
        (image.maxColorVal < 0) || 
        (image.maxColorVal > 255)) 
        {
        cout << "Invalid image stats. Program exiting." << endl;
        validImage = false;
    }

    return validImage;
}

// Name: parseImageFile()
// Desc: Gets data from image file and turns it into a 2D 
//       array for later processing
// Input: ifstream &inImage, const Image &image
// Output: none
// Return: Pixel** imagePixels
Pixel** parseImageFile(ifstream &inImage, const Image &image) {
    Pixel** imagePixels = new Pixel*[image.height];
    // Loop height times
    for (int h = 0; h < image.height; ++h) {
        // Create an array of a single row in the image
        Pixel* pixelRow = new Pixel[image.width];
        for (int w = 0; w < image.width; ++w) {
            // Get the next pixels data
            Pixel nextPixel;
            inImage >> nextPixel.r;
            inImage >> nextPixel.g;
            inImage >> nextPixel.b;

            pixelRow[w] = nextPixel;
        }

        imagePixels[h] = pixelRow;
    }
    
    return imagePixels;
}

// Name: programMenu()
// Desc: Displays options menu and manages user choice
// Input: none
// Output: program menu
// Return: int userChoice
int programMenu() {
    int userChoice = 0;

    // Display menu
    cout << endl << "Image Manipulation Options:" << endl;
    cout << "1. Flip Image Horizontally" << endl;
    cout << "2. Make Image Grayscale" << endl;
    cout << "0. Quit" << endl;
    cout << endl << "Enter your choice: ";

    // Get and validate user input
    cin >> userChoice;
    while (!cin || (userChoice < 0 || userChoice > 2)) {
        cout << "Invalid Input! Please try again: ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> userChoice;
    }
    
    return userChoice;
}

// Name: applyImageFlip()
// Desc: horizontally flips all pixels in each row, mirroring the image
// Input: Image &image
// Output: none
// Return: none
void applyImageFlip(Image &image) {
    Pixel sparePixel;
    // Loop for each row (height)
    for (int h = 0; h < image.height; ++h) {
        // Loop for each column (width)
        for (int w = 0; w < (image.width / 2); ++w) {
            // Get pixel at w (on the first half of the row)
            sparePixel = image.pixels[h][w];

            // Move 'linked' pixel on the second half of the row
            // To the position that spare pixel grabbed from
            image.pixels[h][w] = image.pixels[h][(image.width - 1) - w];

            // Put the spare pixel where the 'linked' pixel in the second
            // half of the row was
            image.pixels[h][(image.width - 1) - w] = sparePixel;
        }
    }
}

// Name: applyGrayScale()
// Desc: Changes the input image into a grayscale image
// Input: const Image &image
// Output: none
// Return: none
void applyGrayscale(Image &image) {
    int nextR = 0;
    int nextB = 0;
    int nextG = 0;
    int avgColor = 0;
    // Loop through each row (height)
    for (int h = 0; h < image.height; ++h) {
        // Loop through each column (width)
        for (int w = 0; w < image.width; ++w) {
            // Find the average value to set RGB to
            nextR = image.pixels[h][w].r;
            nextG = image.pixels[h][w].g;
            nextB = image.pixels[h][w].b;

            avgColor = (nextR + nextG + nextB) / 3;
            // Apply average value to RGB of that pixel
            image.pixels[h][w].r = avgColor;
            image.pixels[h][w].g = avgColor;
            image.pixels[h][w].b = avgColor;
        }
    }
}

// Name: printNewImage()
// Desc: Outputs the final image data to a new file
// Input: const Image &image
// Output: Maybe error message
// Return: none
void printNewImage(const Image &image) {
    ofstream outFile;

    outFile.open("output.ppm");

    if (!outFile.is_open()) {
        cout << "Failed to open output.ppm file" << endl;
    }
    else {
        cout << endl << "Writing image to output.ppm ..." << endl;
        // Write header
        outFile << "P3" << endl;
        outFile << image.width << " " << image.height << endl;
        outFile << image.maxColorVal << endl;

        // Write image data
        for (int h = 0; h < image.height; ++h) {
            for (int w = 0; w < image.width; ++w) {
                outFile << image.pixels[h][w].r << " "
                        << image.pixels[h][w].g << " "
                        << image.pixels[h][w].b << " ";
            }
            outFile << endl;
        }
    }

    outFile.close();
    cout << endl << "Writing complete!" << endl;
}