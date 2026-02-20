/******************************************************************************
# Author:       Aiden Jungels
# Assignment:   
# Date:         
# Description:  
# Input:        
# Output:       
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
bool openImageFile(ifstream &inImage);
bool getImageStats(ifstream &inImage, Image &image);
Pixel** parseImageFile(ifstream &inImage, const Image &image);
void applyImageFlip(Image &image);
void printNewImage(const Image &image);

// Main Function
int main() {
    ifstream inImage;
    Image image;

    // Attempt to open image
    if (openImageFile(inImage)) {
        // Read header of image file
        if (getImageStats(inImage, image)) {

            image.pixels = parseImageFile(inImage, image);

            applyImageFlip(image);

            //Pixel** imagePixels;
            
            // loop height times
                // Create a single row in the image of pixel object pointers
                // Loop width times
                    // Loop 3 times
                        // First value in r, second g, third b as the pixel struct
                    // Add pixel object row num
                // Pixel* pixelRow with length of width
                // add the Pixel* to Pixel**
                //image[/*current row in image*/] = pixelRow;
            //image.pixels = imagePixels;


            //image.pixels[/*row number*/][/*num pixel objects (3 numbers in each) print each of the three numbers with a space*/]
            printNewImage(image);
            // Clear memory from pointer array
            for (int i = 0; i < image.height; ++i) {
                delete[] image.pixels[i];
            }
            delete[] image.pixels;
        }
    }

    inImage.close();
    return 0;
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

            /*
            cout << "For w loop in pIF -- r: "
                 << nextPixel.r << " g: "
                 << nextPixel.g << " b: "
                 << nextPixel.b << endl;
            */

            pixelRow[w] = nextPixel;
        }

        imagePixels[h] = pixelRow;
    }

    /*
    cout << "test r: " << imagePixels[0][0].r << endl;
    cout << "test g: " << imagePixels[0][0].g << endl;
    cout << "test b: " << imagePixels[0][0].b << endl;

    cout << "Width 1" << endl;
    cout << "test r: " << imagePixels[0][1].r << endl;
    cout << "test g: " << imagePixels[0][1].g << endl;
    cout << "test b: " << imagePixels[0][1].b << endl;
    */
    
    return imagePixels;
    
    
    // loop height times
                // Create a single row in the image of pixel object pointers
                // Loop width times
                    // Loop 3 times
                        // First value in r, second g, third b as the pixel struct
                    // Add pixel object row num
                // Pixel* pixelRow with length of width
                // add the Pixel* to Pixel**
                //image[/*current row in image*/] = pixelRow;
            //image.pixels = imagePixels;


            //image.pixels[/*row number*/][/*num pixel objects (3 numbers in each) print each of the three numbers with a space*/]
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
}