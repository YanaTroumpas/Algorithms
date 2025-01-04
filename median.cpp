
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    ifstream f("median.txt");
    
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string s;
    vector<int> values;
    while (getline(f, s)){
        int v = stoi(s);
        values.push_back(v);
    }
    
    vector<int> min_heap;
    vector<int> max_heap;

    int sum = values[0]; // k1
    // initialize heaps
    if(values[0] < values[1]){
        min_heap.push_back(values[1]);
        max_heap.push_back(values[0]);
        sum +=values[0]; // k2
    }else{
        min_heap.push_back(values[0]);
        max_heap.push_back(values[1]);
        sum +=values[1]; // k2
    }
    
    make_heap(min_heap.begin(), min_heap.end(), std::greater<>{});
    make_heap(max_heap.begin(), max_heap.end());
    
    
    for(int i = 2; i < values.size(); ++i){
        int curr_val = values[i];
        int curr_max = max_heap.front();
        int curr_min = min_heap.front();
        
        // balance by value
        if(curr_val > curr_min){ // bigger value, goes to min heap
            min_heap.push_back(curr_val);
            push_heap(min_heap.begin(), min_heap.end(), std::greater<>{});
        }else{ // smaller or in between, goes to max heap
            max_heap.push_back(curr_val);
            push_heap(max_heap.begin(), max_heap.end());
        }
        
        // balance by size
        if(i %2 == 1 and max_heap.size() != min_heap.size()){
            if(max_heap.size() > min_heap.size()){
                pop_heap(max_heap.begin(), max_heap.end()); // move largest elem to other heap
                curr_max = max_heap.back();
                max_heap.pop_back();
                min_heap.push_back(curr_max);
                push_heap(min_heap.begin(), min_heap.end(), std::greater<>{});
            }else{
                pop_heap(min_heap.begin(), min_heap.end(), std::greater<>{}); // move smallest elem to other heap
                curr_min = min_heap.back();
                min_heap.pop_back();
                max_heap.push_back(curr_min);
                push_heap(max_heap.begin(), max_heap.end());
            }
        }
        
        // find median
        size_t median_pos = i/2;
        int median = median_pos < max_heap.size() ? max_heap.front() :  min_heap.front();
        sum += median;
    }
    
    cout << sum % 10000 << endl;
    
    f.close();
    return 0;
}


