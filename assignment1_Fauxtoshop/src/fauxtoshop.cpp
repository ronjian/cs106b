// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: rewrite this comment

#include <iostream>
#include "console.h"
#include "gbufferedimage.h"
#include "grid.h"
#include "gwindow.h"
#include "fauxtoshop-provided.h"   // instructor-provided code
#include "simpio.h"   // Stanford library I/O helpers
#include "math.h"
using namespace std;


void openImage(GBufferedImage &img, string & img_name);
int askForChoice();
void saveImage(GBufferedImage &img);
void scatter(const Grid<int> & original, Grid<int> & filtered_grid, const int height, const int width);
void edgeDetection(const Grid<int> & original, Grid<int> & filtered_grid
                   , const int height, const int width, const int WHITE, const int BLACK);

int main() {
    // pre-defined color constants
    const int WHITE = 0xFFFFFF;
    const int BLACK = 0x000000;
    const int GREEN = 0x00FF00;

    cout << "Welcome to Fauxtoshop!" << endl;

    // basic setup of Graphics Window
    GWindow gw;
    gw.setTitle("Fauxtoshop");
    gw.setExitOnClose(true);
    gw.setVisible(true);
    GBufferedImage img;
    //want the same random numbers on each run
    fakeRandomNumberGenerator();
    string img_name;
    while (true){
        //ask for the image name, and store image in GBufferedImage img
        openImage(img, img_name);
        //quit if user enter blank
        if (img_name == "")
            break;
        //add the image to Graphics Window
        gw.setCanvasSize(img.getWidth(),img.getHeight());
        gw.add(&img,0,0);
        //ask for the filter choice number
        int choice = askForChoice();
        Grid<int> original = img.toGrid();
        const int height = original.height();
        const int width = original.width();
        Grid<int> filtered_grid(height, width);
        if(choice == 1){
            scatter(original, filtered_grid, height, width);
        }else if(choice == 2){
            edgeDetection(original, filtered_grid, height, width, WHITE, BLACK);
        }
        img.fromGrid(filtered_grid);
        //ask for file name and save
        saveImage(img);
        //clean Gwindow and image before starting next round
        img.clear();
        gw.clear();
        cout << endl;
    }

    //close Gwindow
    gw.close();
    return 0;
}
/*
 * 1.ask for file name to open
 * 2.if user enter blank, quit this function, and store the img_name as "",
 * which will be the identicator to quit the program
 * 3.if the image name is not valid, ask again
 * 4.store the result in output parameters img and img_name
 */
void openImage(GBufferedImage &img, string & img_name){
    bool result = false;
    string prompt = "Enter name of image file to open (or blank to quit): ";
    while (not result) {
        cout << prompt;
        getline(cin, img_name);
        if (img_name ==""){
            break;
        }
        cout << "Opening image file, may take a minute..." << endl;
        result = openImageFromFilename(img, img_name);
        if (not result){
            prompt = img_name + " is not valid image name, please re-enter: " ;
        }
    }
}
/*
 * ask for the choice number of filtering,
 * limit the choice number in (1,2,3,4).
 * return choice number as integer.
 * reference for concating string:
 * https://stackoverflow.com/questions/662918/how-do-i-concatenate-multiple-c-strings-on-one-line
 */
int askForChoice(){
    stringstream ss;
    ss << "Which image filter would you like to apply?\n"
         <<"\t1 - Scatter\n"
         <<"\t2 - Edge detection\n"
         <<"\t3 - \"Green screen\" with another image\n"
         <<"\t4 - Compare image with another image\n"
         <<"Your choice: ";
    string prompt = ss.str();
    int choice = getIntegerBetween(prompt,1,4);
    return choice;
}

/*
 * 1.ask for file name to save the image
 * 2.if user enter blank, then skip saving
 * 3.if the name is invalid, re-ask
 */
void saveImage(GBufferedImage & img){
    bool result = false;
    string prompt = "Enter file name to save image (or blank to skip saving): ";
    string save_img_name;
    while (not result){
        cout << prompt;
        //https://stackoverflow.com/questions/6649852/getline-not-working-properly-what-could-be-the-reasons
        getline(cin, save_img_name);
        //enter blank to skip saving
        if (save_img_name == ""){
            break;
        }
        result = saveImageToFilename(img, save_img_name);
        if (not result){
            prompt = save_img_name + " is not a valid file name, please re-enter: ";
        }
    }
}

/*
 * 1.ask for degree/radius of scatter
 * 2.select a random pixel
 * 3.if the random pixel is out of the bound of the image, redo selecting.
 */
void scatter(const Grid<int> & original, Grid<int> & filtered_grid, const int height, const int width){
    string prompt = "Enter degree of scatter [1-100]: ";
    int radius=getIntegerBetween(prompt, 1, 100);
    for(int h=0; h < height; h++){
        for(int w=0; w < width; w++){
            int w_new;
            int h_new;
            do{
                w_new = randomInteger(w - radius, w + radius);
                h_new = randomInteger(h - radius, h + radius);
            }while(not original.inBounds(h_new, w_new));
            filtered_grid[h][w] = original.get(h_new, w_new);
        }
    }
}
/*
 * 1.ask for threshold for edge detection
 * 2.loop each pixel in the image,
 * 3.if get true from edgeIdentificator,
 * then set as color BLACK in new image,
*/
bool edgeIdentificator(const Grid<int> & original, const int row, const int col, const int threshold) ;
void edgeDetection(const Grid<int> & original, Grid<int> & filtered_grid
                   , const int height, const int width, const int WHITE, const int BLACK){
    //ask for threshold
    string prompt = "Enter threshold for edge detection: ";
    const int threshold = getInteger(prompt);
    //loop all pixels
    for (int row =0 ; row <height ; row++){
        for (int col = 0; col < width ; col++ ){
            if (edgeIdentificator(original, row, col, threshold)){
                filtered_grid[row][col] = BLACK;
            }else {
                filtered_grid[row][col] = WHITE;
            }
        }
    }
}
/*
 * focus on one pixel and identify if it is edge.
 * if any distance(Euclidean distance between RGB values treated as vectors of dimension 3)
 * of the pixel with its neighbors
 * pixels (nearby 9 pixels, include itself)
 * is greater than the threshold, then it is edge, return true.
 */
bool edgeIdentificator(const Grid<int> & original, const int row, const int col, const int threshold) {
    const int current_pixel = original[row][col];
    int red, green, blue;
    GBufferedImage::getRedGreenBlue(current_pixel, red, green, blue);
    for (int r=row-1; r <= row+1; r++){
        for (int c=col-1; c <= col+1; c++){
            if (original.inBounds(r,c)){
                int neighbor = original[r][c];
                int n_red, n_green, n_blue;
                GBufferedImage::getRedGreenBlue(neighbor, n_red, n_green, n_blue);
                int distance = sqrt(pow((red-n_red),2) + pow((green-n_green),2) + pow((blue-n_blue),2));
                if (distance > threshold){
                    return true;
                }
            }
        }
    }
   return false;
}
