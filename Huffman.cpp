
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;
typedef unordered_map<int, string> Codewords; // symbol to codeword
typedef map<set<int>, Codewords> Forest; // symbols to codewords

int main(){
    ifstream f("huffman.txt");

    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    string header;
    getline(f, header);
    int n = stoi(header);
    
    string s;
    
    int symbol_num = 0;
    set<pair<int, set<int>>> weights;
    Forest forest; // every tree contains one symbol at the start
    while (getline(f, s)){
        int weight = stoi(s);
        int symbol = ++symbol_num;
        set<int> tree({symbol});
        weights.insert({weight, tree});
        forest[tree].insert({symbol, {}}); // no codewords in every tree
    }
    
    while(forest.size() > 1){
        // Merge 2 nodes with smallest weights
        auto tree1 = *weights.begin();
        weights.erase(weights.begin());
        auto tree2 = *weights.begin();
        weights.erase(weights.begin());
        
        // Update weights after merge
        int new_weight = tree1.first + tree2.first; 
        auto new_tree = tree1.second;
        new_tree.insert(tree2.second.begin(), tree2.second.end());
        weights.insert({new_weight, new_tree});

        // Update forest
        Codewords merged_codewords;
        auto codewords1 = forest[tree1.second];
        auto codewords2 = forest[tree2.second];
        for(auto word:codewords1){ // Update left child
            merged_codewords.insert({word.first, word.second += "0"});
        }
        for(auto word:codewords2){ // Update right child
             merged_codewords.insert({word.first, word.second += "1"});
        }
        
        forest[new_tree] = merged_codewords;
        forest.erase(tree1.second);
        forest.erase(tree2.second);
    }
    
    size_t min_len = INT_MAX;
    size_t max_len = 0;
    
    for(auto codewords: forest.begin()->second){ // only one merged codeword set left 
        min_len = min(min_len, codewords.second.size());
        max_len = max(max_len, codewords.second.size());
    }
    cout << "max: " << max_len << " min: " << min_len << endl;

    f.close();
    return 0;
}