
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<int> CalculateMaxWeights(const vector<int>& weights){
    size_t n = weights.size();
    vector<int> solution(n);
    
    solution[0] = weights[0];

    if(weights.size() > 1){
        solution[1] = max(weights[0], weights[1]);
    }

    if(weights.size() > 2){
        for(int i = 2; i < n; ++i){
            solution[i] = max(solution[i - 1], solution[i - 2] + weights[i]);
        }
    }

    int i = n - 1;
    while(i >= 2){
        if(solution[i - 1] >= solution[i - 2] + weights[i]){
            i = i - 1;
        }else{
            i = i - 2;
        }
    }
    return solution;
}

unordered_set<int> Reconstruct(const vector<int>& weights, const vector<int>& solution){
    unordered_set<int> independent_set;
    size_t i = solution.size();
    while(i >= 2){
        if(solution[i - 1] >= solution[i - 2] + weights[i]){
            i--;
        }else{
            independent_set.insert(i);
            i -= 2;
        }
    }

    if(i == 1){
        independent_set.insert(1);
    }
    return independent_set;
}

int main(){
    ifstream f("mwis.txt");

    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    string header;
    getline(f, header);
    int n_vertexes = stoi(header);
    vector<int> weights(n_vertexes + 1);
    
    string s;
    int row_counter = 0;
    while (getline(f, s)){
        int weight = stoi(s);
        weights[++row_counter] = weight;
    }
    
    auto solution = CalculateMaxWeights(weights);
    auto independent_set = Reconstruct(weights, solution);
    vector<int> vertexes_of_interest({1, 2, 3, 4, 17, 117, 517, 997});
    string result;
    for(int v:vertexes_of_interest){
        if(independent_set.count(v)){
            result.push_back('1');
        }else{
            result.push_back('0');
        }
    }
    
    cout << result << endl;

    f.close();
    return 0;
}