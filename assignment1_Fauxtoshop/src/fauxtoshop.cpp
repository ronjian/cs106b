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
using namespace std;


void openImage(GBufferedImage &img, string & img_name);
int askForChoice();
void saveImage(GBufferedImage &img);
void scatter(Grid<int> & original, Grid<int> & filtered_grid);

int main() {
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
        //TODO filter step
        Grid<int> original = img.toGrid();
        Grid<int> filtered_grid(1,1);
        if(choice == 1){
            scatter(original, filtered_grid);
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
 */
int askForChoice(){
    cout << "Which image filter would you like to apply?\n"
         << "\t1 - Scatter\n"
         << "\t2 - Edge detection\n"
         << "\t3 - \"Green screen\" with another image\n"
         << "\t4 - Compare image with another image\n"
         << "Your choice: ";
    int choice;
    choice = getInteger();
    while (choice != 1 and choice != 2 and choice != 3 and choice !=4) {
        cout << choice << " is not a valid choice, please choose again: ";
        choice = getInteger();
    }
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
void scatter(Grid<int> & original, Grid<int> & filtered_grid){
    string prompt = "Enter degree of scatter [1-100]: ";
    int radius=getIntegerBetween(prompt, 1, 100);
    const int height = original.height();
    const int width = original.width();
    filtered_grid.resize(height, width);
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
