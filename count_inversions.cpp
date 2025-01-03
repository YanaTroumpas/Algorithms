
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

long count_inv = 0;

void Merge(vector<int>& input, vector<int>& aux, size_t lo, size_t mid, size_t hi){
    size_t i = lo;
    size_t j = mid + 1;
    
    for(size_t k = lo; k <= hi; ++k){ // copy input values to aux
        aux[k] = input[k];
    } 

    for(size_t k = lo; k <= hi; ++k){
        if(i > mid and j <= hi){
            input[k] = aux[j]; // end of first subarray, append from the second
            j++;
        }else if(j > hi and i <= mid){ // end of second subarray, append from the first
            input[k] = aux[i];
            i++;
        }else if(aux[i] < aux[j]){ // append value from first subarray
            input[k] = aux[i];
            i++;
        }else{
            input[k] = aux[j]; // append value from second subarray
            j++;
            count_inv = count_inv + (mid - i + 1); // add rest from first subarray
        }
    }
}

void Sort(vector<int>& input, vector<int>& aux, size_t lo, size_t hi){
    if(lo == hi){
        return; // 1 element, base case
    }
    
    size_t mid = lo + (hi - lo)/2;
    Sort(input, aux, lo, mid);
    Sort(input, aux, mid + 1, hi);
    Merge(input, aux, lo, mid, hi);
}

int main()
{
    ifstream f("IntegerArray.txt");
    
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string s;
    vector<int> array;
    while (getline(f, s)){
        int v = stoi(s);
        array.push_back(v);
    }
    
    vector<int> aux(array.size());
    Sort(array, aux, 0, array.size() - 1);
    cout << count_inv << endl;
    
    f.close();
    return 0;
}


