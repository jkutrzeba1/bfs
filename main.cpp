#include <vector>
#include <iostream>

using namespace std;

struct Graph {

    struct Ed {

        int v; // indeks wierzchołka do którego prowadzi krawędź
        int r; // indeks krawędzi przeciwnej

        Ed(int v, int r = -1) : v(v), r(r) { }

    };

    struct Ve : vector<Ed> {
        int d; // dystans do korzenia
        int p; // indeks rodzica

        Ve() : d(-1), p(-1) {}
    };

    vector<Ve> g;

    Graph(int n = 0) : g(n) {}

    void EdgeD(int b, int e){

        // wstawiam krawędź skierowaną prowadzącą z wierzchołka b do e

        g[b].push_back(Ed(e));

    }

    void EdgeU(int b, int e){

        // wstawiam krawędź nieskierowaną reprezentowaną jako dwie krawędzie skierowane z b do e oraz z e do b

        g[b].push_back(Ed(e, g[e].size() + (b==e) ));
        g[e].push_back(Ed(b, g[b].size()-1 ));


    }

    void Write(){

        for(int x = 0; x<g.size(); x++){

            cout<<x<<": ";

            for(auto ed = g[x].begin(); ed!=g[x].end(); ed++){
                cout<<ed->v<<" ";
            }

            cout<<endl;

        }

    }

    void Bfs(int r){

        int distance = g[r].d = 0;
        int parent;

        vector<int> que;

        que.push_back(r);

        int qs = 0;

        while(qs<que.size()){

            distance = g[que[qs]].d + 1;
            parent = que[qs];

            for(auto ed = g[que[qs]].begin(); ed!=g[que[qs]].end(); ed++){

                if( g[ed->v].d != -1 ){
                    continue;
                }

                g[ed->v].d = distance;
                g[ed->v].p = parent;

                que.push_back(ed->v);

            }

            qs++;

        }

    }

    void WriteBfs(){

        for(int x = 0; x<g.size(); x++){

            cout<<x<<": "<<"   D: "<<g[x].d<<"   P: "<<g[x].p<<endl;

        }

    }

};

int main(){

    Graph g1(5);

    g1.EdgeU(0,1);
    g1.EdgeU(1,2);
    g1.EdgeU(2,3);
    g1.EdgeU(3,4);

    g1.Write();

    cout<<endl;

    g1.Bfs(0);
    g1.WriteBfs();

    cout<<endl;

    Graph g2(5);

    g2.EdgeD(0,1);
    g2.EdgeD(1,2);
    g2.EdgeD(2,3);
    g2.EdgeD(3,4);

    g2.Bfs(0);
    g2.WriteBfs();

}
