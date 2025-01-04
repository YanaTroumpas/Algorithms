
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<fstream>
#include<unordered_set>
#include<set>

using namespace std;

int main()
{
    ifstream f("2sum.txt");
    
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string s;
    set<long> sorted_vals;
    while (getline(f, s)){
        long v = stol(s);
        sorted_vals.insert(v);
    }
    
    long start_t = -10000;
    long end_t = 10000;
    set<int> t;

    for(auto it = sorted_vals.begin(); it != sorted_vals.end();){
        long lower_border = start_t - *it; 
        long upper_border = end_t - *it;
        auto lower_it = sorted_vals.upper_bound(lower_border);
        auto upper_it = sorted_vals.lower_bound(upper_border);

        if(lower_it != sorted_vals.end()){
            for(auto valid_it = lower_it; valid_it != upper_it; ++valid_it){
                t.insert(*valid_it + *it);
            }
        }
        
        it = sorted_vals.erase(it);
    }
    
    cout << t.size() << endl;
    f.close();
    return 0;
}



