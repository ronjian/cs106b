// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <iostream>
#include "console.h"
#include "simpio.h"   // Stanford library I/O helpers
#include "random.h"
#include <fstream>
#include <sstream>
#include <map.h>
#include <queue>
using namespace std;

int main() {
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout <<  "This program generates random text based on a document." <<endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl;

    cout<<endl;

    string filename;
    ifstream ifs;
    while (!ifs.is_open()){
        cout << "Input file name? " ;
        getline(cin, filename);
        ifs.open(filename);
        if (!ifs.is_open()){
            cout << "Unable to open that file.  Try again." << endl;
        }
    }


    int N = 0;
    while(N<=2){
        N = getInteger("Value of N? ");
        if (N<=2){
            cout << "N must be 2 or greater." << endl;
        }
    }


    string new_word;
    Map<queue<string>, vector<string> > stock;
    queue<string> window;
    vector<string> value;
    while(ifs >> new_word){
        if (window.size() < N){
            window.push(new_word);

        }else{
            value = stock.get(window);
            value.insert(value.end(), new_word);
            stock.put(window, value);
            window.push(new_word);
            window.pop();
        }
    }

    while (true){
        cout << endl;
        int M = -1;
        while( M<4 and M!=0){
            M = getInteger("# of random words to generate (0 to quit): ");
            if ( M<4 and M!=0){
                cout << "Must be at least 4 words." << endl;
            }
        }
        if (M==0){
            break;
        }

        string output = "";
        queue<string> key;
        int r2;
        for (int i=0 ; i < M; i++){
            if(i==0){
                int r1 = randomInteger(0, stock.size()-1);   // inclusive
                key = stock.keys()[r1];
                value = stock.values()[r1];
            }else{
                value = stock.get(key);
            }
            r2 = randomInteger(0, value.size()-1);   // inclusive
            output = output + " " + key.front();
            key.pop();
            key.push(value[r2]);
        }
        cout << "... " << output << " ..."<< endl;
    }

    cout << "Exiting." << endl;
    return 0;
}
