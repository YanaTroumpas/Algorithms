
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    ifstream f("knapsack_big.txt");

    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    string header;
    getline(f, header);
    size_t pos = header.find(' ');
    int knapsack_size = stoi(header.substr(0, pos));
    int num_items = stoi(header.substr(pos + 1));
    vector<int> item_sizes(num_items + 1); // 1-based numeration
    vector<int> item_values(num_items + 1); // 1-based numeration
    
    string s;
    int item_counter = 0;
    while (getline(f, s)){
        pos = s.find(' ');
        int value = stoi(s.substr(0, pos));
        int size = stoi(s.substr(pos + 1));
        item_counter++;
        item_sizes[item_counter] = size; 
        item_values[item_counter] = value;
    }

    vector<int> solution(knapsack_size + 1);
    for(int c = 0; c <= knapsack_size; ++c){
        solution[c] = 0;
    }
        
    for(int i = 1; i <= num_items; ++i){
        vector<int> prev_step = solution;
        for(int c = 0; c <= knapsack_size; ++c){
            if(item_sizes[i] > c){ // item doesn't fit
                solution[c] = prev_step[c];
            }else{ // it fits
                solution[c] = max(prev_step[c], prev_step[c - item_sizes[i]] + item_values[i]);
            }
        }    
    }

    cout << solution[knapsack_size] << endl;
    f.close();
    return 0;
}