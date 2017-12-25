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
    cout << "Input file name? " ;
    string filename;
    getline(cin, filename);
    const int N = getInteger("Value of N? ");

    ifstream ifs;
    ifs.open(filename);
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

    cout << stock.size() << endl;

    const int M = getInteger("# of random words to generate (0 to quit): ");
    string output = "";
    queue<string> key;
    int r1;
    int r2;
    for (int i=0 ; i < M-N; i++){
        if(i==0){
            r1 = randomInteger(0, stock.size()-1);   // inclusive
            key = stock.keys()[r1];
            while(!key.empty()){
                output = output + key.front() + " ";
                key.pop();
            }
            value = stock.values()[r1];
            r2 = randomInteger(0, value.size()-1);   // inclusive
            output = output + " " + value[r2];
            key = stock.keys()[r1];
            key.pop();
            key.push(value[r2]);
        }else{
            value = stock.get(key);
            r2 = randomInteger(0, value.size()-1);   // inclusive
            output = output + " " + value[r2];
            key.pop();
            key.push(value[r2]);
        }

    }
     cout << "... " << output << endl;



    cout << "Exiting." << endl;
    return 0;
}
