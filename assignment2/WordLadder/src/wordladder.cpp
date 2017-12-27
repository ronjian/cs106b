#include <iostream>
#include <set>
#include <queue>
#include <stack>
#include "console.h"
#include <fstream>
#include <algorithm>
using namespace std;

void openDict(set<string> & dict);

int main() {

    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time." <<endl;
    cout << endl;
    set<string> dict;
    openDict(dict);

    while(true){
        cout << endl;
        cout << "Word 1 (or Enter to quit): " ;
        string word1="";
        getline(cin , word1);
        transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
        if (word1 == ""){
            cout << "Have a nice day." << endl;
            return 0;
        }

        cout << "Word 2 (or Enter to quit): "  ;
        string word2;
        getline(cin , word2);
        transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
        if (word2 == ""){
            cout << "Have a nice day." << endl;
            return 0;
        }

        if (word1.length() != word2.length()){
            cout << "The two words must be the same length." <<endl;
            continue;
        }else if (dict.find(word1) == dict.end() or dict.find(word2) == dict.end()){
            cout << "The two words must be found in the dictionary." <<endl;
            continue;
        }else if (word1 == word2){
            cout << "The two words must be different." <<endl;
            continue;
        }
        set<string> stock;
        stock.insert(word1);
        string new_word;

        queue<stack<string> > Q;
        stack<string> S;
        S.push(word1);
        Q.push(S);

        string last_word;
        while (!Q.empty()){
            for (int q = 0; q < Q.size() ; q++){
                S = Q.front();
                Q.pop();
                last_word = S.top();
                for (int i=0; i<last_word.length() ; i++){
                    for (char ch='a' ; ch <= 'z'; ch++) {
                        if ( last_word[i] != ch ) {
                            new_word = last_word.substr(0, i) + ch + last_word.substr(i+1);
                            //new word is in dictionary and but not in stock
                            if (dict.find(new_word) != dict.end() and stock.find(new_word) == stock.end()){
                                stock.insert(new_word);
                                stack<string> new_S = S;
                                new_S.push(new_word);
                                Q.push(new_S);
                                if (new_word == word2){
                                    cout << "A ladder from " << word2 << " back to " << word1 << ":" << endl;
                                    while(!new_S.empty()){
                                        cout << new_S.top()
                                             << " ";
                                        new_S.pop();
                                    }
                                    cout << endl;
                                    break;
                                }
                            }
                        }
                    }
                }

            }

        }
        cout << "No word ladder found from "
             << word2
             << " back to "
             << word1
             << "." << endl;
    }


    cout << "Have a nice day." << endl;
    return 0;
}

void openDict(set<string> & dict){
    ifstream ifs;
    string dict_name;
    string line;
    while(ifs.is_open() == false){
        cout << "Dictionary file name: ";
        getline(cin,dict_name);
        ifs.open(dict_name);
        if (!ifs.is_open()){
            cout << "Unable to open that file.  Try again." <<endl;
        }
    }
    while(getline(ifs , line)){
        dict.insert(line);
    }
}

