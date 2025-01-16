
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<fstream>
#include<vector>
#include<set>

using namespace std;

class Prim {
    public: 
        Prim(vector<vector<pair<int, int>>> graph):graph_(move(graph)), dist_(vector<int>(graph_.size(), 1000000)) {
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
                    dist_[head] = min(dist_[head], edge_len);
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
    ifstream f("edges.txt");
    
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string header;
    getline(f, header);
    
    size_t h_pos = header.find(' ');
    int n_vertexes = stoi(header.substr(0, h_pos));
    int n_edges = stoi(header.substr(h_pos + 1));

    string s;
    vector<vector<pair<int, int>>> graph(n_vertexes + 1);

    while (getline(f, s)){
        size_t v_pos = s.find(' ');
        int tail = stoi(s.substr(0, v_pos));
        size_t w_pos = s.find(' ', v_pos + 1);
        int head = stoi(s.substr(v_pos + 1, w_pos));
        int weight = stoi(s.substr(w_pos + 1));
        graph[tail].push_back({head, weight});
        graph[head].push_back({tail, weight});
    }
    
    Prim p(graph);
    p.Run();
    
    int tree_cost = 0;
    for(int i = 1; i < n_vertexes + 1; ++i){
        tree_cost += p.GetDistance(i);
    }
    cout << tree_cost << endl;
    f.close();
    return 0;
}
