// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "grammarsolver.h"
#include "map.h"
#include "vector.h"
#include "strlib.h"
#include "random"
#include "vector"
using namespace std;

void grammarGenerateHelp(string & terminal_seq, string & symbol, const Map<string, vector<Vector<string> > > grammar){
    if (grammar.containsKey(symbol)){
        vector<Vector<string> > v = grammar[symbol];
        int random_idx = randomInteger(0, v.size()-1);
        for (string x: v[random_idx]){
            if(grammar.containsKey(x)){
                grammarGenerateHelp(terminal_seq, x, grammar);
            }else{
                terminal_seq += " " + x;
            }
        }
    }else{
        terminal_seq += trim(symbol);
    }

}

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // Part 1: Reading the Input File
    Map<string, vector<Vector<string> > > grammar;
    while(!input.eof()){
        string line;
        getline(input, line);
        string key = line.substr(0, line.find_first_of("::="));
        Vector<string> tmp = stringSplit(line.substr(line.find_first_of("::=")+3, line.size()), "|");
        vector<Vector<string> > value;
        for (string x : tmp){
            value.push_back(stringSplit(x, " "));
        }
        if(grammar.containsKey(key)){
            throw string("Duplicated symbols: " + key);
        }else{
            grammar.add(key, value);
        }
    }

    // Part 2: Generating Random Expansions from the Grammar
    Vector<string> output;
    for (int i=0 ; i < times; i++){
        string terminal_seq = "";
        grammarGenerateHelp(terminal_seq, symbol, grammar);
        output.add(terminal_seq);
    }
    return output;
}
