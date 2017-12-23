#include <iostream>
#include <set>
#include <queue>
#include <stack>
#include "console.h"
#include <fstream>
using namespace std;

int main() {

    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the"
           << " first into the second by modifying one letter at a time." <<endl;
    cout << endl;
    cout << "Dictionary file name: ";
    string dict_name;
    getline(cin,dict_name);
    ifstream ifs;
    ifs.open(dict_name);
    string line;
    set<string> dict;
    while(getline(ifs , line)){
        dict.insert(line);
    }

    cout << endl;
    cout << "Word 1 (or Enter to quit): " ;
    string word1;
    getline( cin , word1);
    string word2;
    cout << "Word 2 (or Enter to quit): "  ;
    getline(cin , word2);

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
                        //in dictionary and not in stock
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

    cout << "Have a nice day." << endl;

    return 0;
}
