
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Graph {
    public:
        Graph(int num_vertexes): graph_(num_vertexes + 1){}
        void AddEdge(int v, int w){
            graph_[v].push_back(w);
        }
        int NumVertexes() const {
            return graph_.size();
        }
        const vector<int>& GetAdj(int v) const {
            return graph_[v];
        }
    private:
        vector<vector<int>> graph_;
};

class GraphTraverse {
    public:
        GraphTraverse(const Graph& g): graph_(g), marked_(g.NumVertexes(), false){}
       
        vector<int> RunDFS(){
            for(int v = 1; v < graph_.NumVertexes(); ++v){
                if(!marked_[v]){
                    dfs(v);
                } 
                
            }
            return top_order_;
        }
        
        void RunDFS_SCC(const vector<int>& top_order){
            for(auto it = top_order.rbegin(); it < top_order.rend(); ++it)
                if(!marked_[*it]){
                    num_scc_++;
                    dfs_scc(*it);
                }
        }
        
        void GetTop5SCC(){
            for(auto elem:scc_){
                max_scc_.push(elem.second);
            }
            cout << "num scc: " << scc_.size() << endl;
            for(int i = 0; i < 5; ++i){
                if(!max_scc_.empty()){
                    int top = max_scc_.top();
                    max_scc_.pop();
                    cout << top << " ";
                }else{
                    cout << 0 << " ";
                }
            }
            cout << endl;
        }
    
        
    private:
        void dfs(int v){
            if(!marked_[v]){
                marked_[v] = true;
                for(int w: graph_.GetAdj(v)){
                    dfs(w);
                }
                top_order_.push_back(v);
            } 
        }
        
        void dfs_scc(int v){
            if(!marked_[v]){
                marked_[v] = true;
                scc_[num_scc_]++;
                for(int w: graph_.GetAdj(v)){
                    dfs_scc(w);
                }
                
            } 
        }
    
        
        Graph graph_;
        vector<bool> marked_;
        vector<int> top_order_;
        map<int, int> scc_;
        priority_queue<int> max_scc_;
        int num_scc_ = 0;
};



int main() {
    ifstream f("scc.txt");
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string s;
    
    int num_vertexes = 875714;
    int v = 0;
    int w = 0;

    Graph graph(num_vertexes);
    Graph reverse_graph(num_vertexes);
    
    while (getline(f, s)){
        size_t pos = s.find(' ');
        v = stoi(s.substr(0, pos));
        w = stoi(s.substr(pos + 1));
        graph.AddEdge(v, w);
        reverse_graph.AddEdge(w, v);
    }

    GraphTraverse rev_searcher(reverse_graph);
    auto top_order = rev_searcher.RunDFS();

    GraphTraverse searcher(graph);
    searcher.RunDFS_SCC(top_order);
    
    searcher.GetTop5SCC();
    f.close();
}
