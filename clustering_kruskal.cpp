
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

struct Edge{
    Edge(int h, int t, int w): head(h), tail(t), weight(w){}
    int head;
    int tail;
    int weight;
    bool operator<(const Edge& other){
        return weight < other.weight;
    }
};

class DisjointSet{
    public:
    DisjointSet(int n_vertices): disjoint_sets(n_vertices + 1, -1){}
    int find(int vertex){
        if(disjoint_sets[vertex] == -1){
            return vertex;
        }else{
            return find(disjoint_sets[vertex]);
        }
    }
    void join(int leader1, int leader2){
        disjoint_sets[leader1] = leader2;
    }
    
    int cluster_count() const{
        int cluster_count = 0;
        for(int s: disjoint_sets){
            if(s == -1){
                cluster_count++;
            }
        }
        return cluster_count;
    }
    
    vector<int> disjoint_sets;
};


int main()
{
    int MAX_CLUSTER_COUNT = 4;

    ifstream f("clustering1.txt");
    
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string header;
    getline(f, header);
    
    int n_vertexes = stoi(header);
    DisjointSet dj_set(n_vertexes);
    
    string s;
    vector<Edge> edges;

    while (getline(f, s)){
        size_t v_pos = s.find(' ');
        int tail = stoi(s.substr(0, v_pos));
        size_t w_pos = s.find(' ', v_pos + 1);
        int head = stoi(s.substr(v_pos + 1, w_pos));
        int weight = stoi(s.substr(w_pos + 1));
        edges.emplace_back(head, tail, weight);
    }
    
    sort(edges.begin(), edges.end());

    int sep_distance = 0;
    for(auto edge:edges){
        int leader1 = dj_set.find(edge.tail);
        int leader2 = dj_set.find(edge.head);
        if(leader1 != leader2){
            dj_set.join(leader1, leader2);
            if(dj_set.cluster_count() == MAX_CLUSTER_COUNT){
                sep_distance = edge.weight;
                break;
            }
        }
    }
    
    cout << sep_distance << endl;
    
    f.close();
    return 0;
}
