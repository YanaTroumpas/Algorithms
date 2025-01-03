
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
#include<map>

using namespace std;

void MergeVertexes(int first_vertex, int second_vertex, int new_vertex, multimap<int, int>& edges, set<int>& vertices){
    multimap<int, int> new_edges;
    for(auto it = edges.begin(); it != edges.end();){
        int tail = it->first;
        int head = it->second;
        if(tail == first_vertex or tail == second_vertex){
            tail = new_vertex;
        }
        if(head == first_vertex or head == second_vertex){
            head = new_vertex;
        }
        if(tail == new_vertex or head == new_vertex){ // replace edge
            if(tail != head){
                new_edges.insert({tail, head}); // avoid self-loops
            }
            it = edges.erase(it);
        }else{
            ++it;
        }
    }
    
    vertices.erase(first_vertex);
    vertices.erase(second_vertex);
    vertices.insert(new_vertex);
    
    // merge new edges
    for(auto edge:new_edges){
        edges.insert(edge);
    }
}

int FindMinCut(set<int> vertices, multimap<int, int> edges, int seed){
    while(vertices.size() > 2){
        srand (seed++);
        int tail_index = rand() % vertices.size(); // pick random tail vertex
        auto tail_it = vertices.begin();
        for(int i = 0; i < tail_index; ++i){
            tail_it++;
        }
        int v = *tail_it; // first vertex to merge
        
        auto adj_vertexes = edges.equal_range(v);
        auto adj_size = distance(adj_vertexes.first, adj_vertexes.second);
        
        srand(seed++);
        int head_index = rand() % adj_size; // pick random head vertex
        auto head_it = adj_vertexes.first;
        for(int i = 0; i < head_index; ++i){
            head_it++;
        }
        int w = head_it->second; // second vertex to merge
        
        int new_vertex = *vertices.rbegin() + 1; // add new supernode

        MergeVertexes(v, w, new_vertex, edges, vertices);
    }
    
    return edges.size()/2;
}

int main(){
    
    ifstream f("kargerMinCut.txt");
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string s;
    set<int> vertices;
    multimap<int, int> edges;
    
    // Parse input graph
    while (getline(f, s)){
        size_t t_pos = s.find('\t');
        int v = stoi(s.substr(0, t_pos));
        
        stringstream ss(s.substr(t_pos + 1));
        string adj_vertex;
        
        while(getline(ss, adj_vertex, '\t')) {
            if(adj_vertex == "\r"){
                continue;
            }
            int w = stoi(adj_vertex);
            edges.insert({v, w});
        }
        vertices.insert(v); // processed vertex
    }
    
    cout << FindMinCut(vertices, edges, 9) << endl;
    cout << FindMinCut(vertices, edges, 1) << endl;
    cout << FindMinCut(vertices, edges, 333) << endl;
    cout << FindMinCut(vertices, edges, 7777) << endl;
    cout << FindMinCut(vertices, edges, 55) << endl;
    cout << FindMinCut(vertices, edges, 12345678) << endl;
    cout << FindMinCut(vertices, edges, 888) << endl;
    
    f.close();
    return 0;
}


