
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<fstream>
#include<vector>
#include<set>

using namespace std;

class Dijkstra {
    public: 
        Dijkstra(vector<vector<pair<int, int>>> graph):graph_(move(graph)), dist_(vector<int>(graph_.size(), 1000000)) {
            dist_[1] = 0;
            for(int i = 1; i < dist_.size(); ++i){
                heap_.insert({dist_[i], i});
            }
        }
        void Run(){
            while(!heap_.empty()){
                auto v = *(heap_.begin());
                int vertex = v.second;
                int dist_to_vertex = v.first;
                dist_[vertex] = dist_to_vertex;
                heap_.erase(heap_.begin());
                visited_.insert(vertex);
                for(auto edge: graph_[vertex]){
                    int head = edge.first;
                    int edge_len = edge.second;
                    if(visited_.count(head) == 1){
                        continue;
                    }
                    int old_dist = dist_[head];
                    heap_.erase(make_pair(old_dist, head));
                    dist_[head] = min(dist_[head], dist_to_vertex + edge_len);
                    heap_.insert(make_pair(dist_[head], head));
                }
            }
        }
    int GetDistance(int vertex){
        return dist_[vertex];
    }
    
    private:
        vector<vector<pair<int, int>>> graph_;
        vector<int> dist_;
        set<pair<int, int>> heap_;
        set<int> visited_;
};

int main()
{
    ifstream f("dijkstraData.txt");
    
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string s;
    int n = 200 + 1;
    vector<vector<pair<int, int>>> graph(n);
    
    while (getline(f, s)){
        size_t v_pos = s.find('\t');
        int v = stoi(s.substr(0, v_pos));
        s = s.substr(v_pos + 1);
        
        while(s != "\r") {
            int w = 0;
            int l = 0;
            size_t c_pos = s.find(',');
            w = stoi(s.substr(0, c_pos));
            
            size_t s_pos = s.find('\t');
            l = stoi(s.substr(c_pos + 1, s_pos - (c_pos + 1)));
            graph[v].push_back({w, l});
            s = s.substr(s_pos + 1);
        }
    }
    
    Dijkstra d(graph);
    d.Run();
    vector<int> vertexes;
    vertexes = {7, 37,59,82,99,115,133,165,188,197};
    for(auto v:vertexes){
        cout << d.GetDistance(v) << ",";
    }
    cout << endl;
    f.close();
    return 0;
}
,

