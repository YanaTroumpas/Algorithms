
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class QuickSortBase {
    public: 
        QuickSortBase() = default;
        virtual int ChoosePivot(const vector<int>& array, int begin, int end) = 0;

        void QuickSort(vector<int>& array, int begin, int end){
            if(begin >= end){ // subarray with size 0 or 1
                return;
            }
            int pivot = ChoosePivot(array, begin, end);

            if(pivot != begin){
                swap(array[pivot], array[begin]);
            }
            
            int new_pivot = Partition(array, begin, end);
            QuickSort(array, begin, new_pivot - 1); // sort right half
            QuickSort(array, new_pivot + 1, end); // sort left half
        }
        
        int GetNumComp() const{
            return num_comp_;
        }
        
    protected:
        int Partition(vector<int>& array, int begin, int end){
            num_comp_ += end - begin;
            int pivot = array[begin];
            int i = begin + 1;
            for(int j = begin + 1; j <= end; j++){
                if(array[j] < pivot){
                    swap(array[i], array[j]);
                    i++;
                }
            }
    
            int new_pivot_pos = --i;
            swap(array[new_pivot_pos], array[begin]);
            return new_pivot_pos;
        }
        
        int num_comp_ = 0;
    };

class QuickSortFirst: public QuickSortBase {
    public:
        QuickSortFirst() = default;
        int ChoosePivot(const vector<int>& array, int begin, int end) override {
            return begin;
        }
};

class QuickSortLast: public QuickSortBase {
    public:
        QuickSortLast() = default;
        int ChoosePivot(const vector<int>& array, int begin, int end) override {
            return end;
        }
};

class QuickSortMedian: public QuickSortBase {
    public:
        QuickSortMedian() = default;
        int ChoosePivot(const vector<int>& array, int begin, int end) override {
            int middle = begin + (end - begin)/2;
            int min_val = min(array[begin], min(array[middle], array[end]));
            int max_val = max(array[begin], max(array[middle], array[end]));
            
            if(array[begin] != min_val and array[begin] != max_val){
                return begin;
            }
            if(array[middle] != min_val and array[middle] != max_val){
                return middle;
            }
            return end;
        }
};


int main(){
    ifstream f("QuickSort.txt");
    
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
    
    //QuickSortFirst mysort;
    //QuickSortLast mysort;
    QuickSortMedian mysort;
    
    mysort.QuickSort(array, 0, array.size() - 1);
    cout << mysort.GetNumComp() << endl;
    
    f.close();
    return 0;
}


