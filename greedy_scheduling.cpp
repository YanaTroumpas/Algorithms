
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

struct JobDiff{
    JobDiff(int w, int l):weight(w), length(l){
        priority = weight - length;
    }
    int priority;
    int weight;
    int length;
};

struct JobRatio{
    JobRatio(int w, int l):weight(w), length(l){
        priority = weight/(length * 1.0);
    }
    double priority;
    int weight;
    int length;
};

int main()
{
    ifstream f("jobs.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string s;
    vector<JobDiff> jobs_diff;
    vector<JobRatio> jobs_ratio;
    size_t n = 0;
    int w, l;
    while (getline(f, s)){
        size_t pos = s.find(' ');
        if(pos == string::npos){ // first row
            n = stoi(s); 
            continue;
        }
        
        w = stoi(s.substr(0, pos));
        l = stoi(s.substr(pos + 1));
        jobs_diff.push_back({w, l});
        jobs_ratio.push_back({w, l});
    }
    
    sort(jobs_diff.begin(), jobs_diff.end(), [](JobDiff a, JobDiff b){
                                if(a.priority > b.priority){
                                    return true;
                                }if(a.priority == b.priority and a.weight > b.weight){
                                    return true;
                                }else{
                                    return false;
                                }
                                });
                                
    sort(jobs_ratio.begin(), jobs_ratio.end(), [](JobRatio a, JobRatio b){
                                return a.priority > b.priority;
                                });
    
    long long completion_time_diff = 0;
    long long total_time_diff = 0;
    for(auto j:jobs_diff){
        completion_time_diff += j.length;
        total_time_diff += j.weight * completion_time_diff;
    }
    cout << total_time_diff << endl;
    
    long long completion_time_ratio = 0;
    long long total_time_ratio = 0;
    for(auto j:jobs_ratio){
        completion_time_ratio += j.length;
        total_time_ratio += j.weight * completion_time_ratio;
    }
    cout << total_time_ratio << endl;
    
    f.close();
    return 0;
}




