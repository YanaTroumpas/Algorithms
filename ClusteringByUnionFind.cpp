
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <bitset>

using namespace std;

const int NUM_BITS = 24;

class DisjointSet{
public:
    DisjointSet(int n_vertices) : disjoint_sets(n_vertices + 1, -1), rank(n_vertices + 1, 1){
        disjoint_sets[0] = 0; // vertex numeration starts from 1
    }

    int find(int vertex){
        if (disjoint_sets[vertex] == -1){
            return vertex;
        }else{ 
            return find(disjoint_sets[vertex]);
        }
    }

    void join(int leader1, int leader2){
        if (rank[leader1] > rank[leader2]){
            disjoint_sets[leader2] = leader1;
            rank[leader1] += rank[leader2];
        }else{
            disjoint_sets[leader1] = leader2;
            rank[leader2] += rank[leader1];
        }
    }

    int cluster_count() const {
        int cluster_count = 0;
        for (int i = 1; i < disjoint_sets.size(); ++i){
            if (disjoint_sets[i] == -1){
                cluster_count++;
            }
        }
        return cluster_count;
    }

private:
    vector<int> disjoint_sets;
    vector<int> rank;
};

class NeighbourFinder
{
public:
    NeighbourFinder(const std::unordered_map<bitset<NUM_BITS>, vector<int>> &vertexes, int num_vertexes) : vertexes_(move(vertexes)), dj_set_(num_vertexes) {}

    void FindNeighbours(){
        for (const auto &vertex : vertexes_){

            JoinDuplicates(vertex.second);

            for (int i = 0; i < NUM_BITS; ++i){
                int curr_leader = dj_set_.find(vertex.second[0]);
                auto neighbor1 = vertex.first; // neighbor with distance 1
                neighbor1.flip(i);
                CheckNeighbor(curr_leader, neighbor1.to_ulong());

                for (int j = i + 1; j < NUM_BITS; ++j){ // don't look back
                    curr_leader = dj_set_.find(vertex.second[0]);
                    auto neighbor2 = neighbor1; // neighbor with distance 2
                    neighbor2.flip(j);
                    CheckNeighbor(curr_leader, neighbor2.to_ulong());
                }
            }
        }
    }

    int GetClusterCount() const
    {
        return dj_set_.cluster_count();
    }

private:
    void CheckNeighbor(int current_leader, int possible_neighbor){
        if (vertexes_.count(possible_neighbor)){ // such neighbor exists
            for (int neighbor_vertex : vertexes_.at(possible_neighbor)){
                int neighbor_leader = dj_set_.find(neighbor_vertex);
                if (current_leader != neighbor_leader){
                    dj_set_.join(current_leader, neighbor_leader);
                }
            }
        }
    }

    void JoinDuplicates(const vector<int> &vertexes){
        int curr_leader = dj_set_.find(vertexes[0]);
        if (vertexes.size() > 1){
            for (int i = 1; i < vertexes.size(); ++i)
            {
                int neighbor_leader = dj_set_.find(vertexes[i]);
                if (neighbor_leader != curr_leader)
                {
                    dj_set_.join(curr_leader, neighbor_leader);
                }
            }
        }
    }

    std::unordered_map<bitset<NUM_BITS>, vector<int>> vertexes_;
    DisjointSet dj_set_;
};

int main(){
    ifstream f("clustering_big.txt");

    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    string header;
    getline(f, header);
    size_t pos = header.find(" ");
    int n_vertexes = stoi(header.substr(0, pos));
    int bit_len = stoi(header.substr(pos + 1));
    if (NUM_BITS != bit_len){
        return -1;
    }

    std::unordered_map<bitset<NUM_BITS>, vector<int>> vertexes; // value is vector because of duplicates

    string s;
    int row_counter = 0;
    while (getline(f, s)){
        string vertex_bits;
        for (const char c : s){
            if (c != ' '){
                vertex_bits += c;
            }
        }
        bitset<NUM_BITS> vertex(vertex_bits);
        vertexes[vertex].push_back(++row_counter);
    }
    
    NeighbourFinder finder(vertexes, n_vertexes);
    finder.FindNeighbours();
    cout << finder.GetClusterCount() << endl;

    f.close();
    return 0;
}