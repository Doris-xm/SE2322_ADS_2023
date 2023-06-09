#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Edge {
public:
    int u;
    int v;
    int w;

    friend bool operator<(const Edge& E1, const Edge& E2) {
        return E1.w < E2.w;
    }
};
vector<Edge> edges; // adjacency matrix
// 创建并查集
void MakeSet(vector<int>& uset, int n) {
    uset.assign(n, 0);
    for (int i = 0; i < n; i++)
        uset[i] = i;
}

// 查找当前元素所在集合的代表元
int FindSet(vector<int>& uset, int u) {
    int i = u;
    while (uset[i] != i)
        i = uset[i];
    return i;
}

void Kruskal(const vector<Edge>& edges, int n) {
    vector<int> uset;
    vector<Edge> SpanTree;
    int Cost = 0, e1, e2;
    MakeSet(uset, n);
    for (int i = 0; i < edges.size(); i++) {
        e1 = FindSet(uset, edges[i].u);
        e2 = FindSet(uset, edges[i].v);
        if (e1 != e2) {
            SpanTree.push_back(edges[i]);
//            Cost += edges[i].w;
            uset[e1] = e2;
        }
    }
    cout << "Result:\n";
//    cout << "Edges:\n";
    for (int j = 0; j < SpanTree.size(); j++)
        Cost += SpanTree[j].w;

    cout << "Cost: " << Cost << endl;
//        cout << SpanTree[j].u << " " << SpanTree[j].v << " " << SpanTree[j].w << endl;
//    cout << endl;
}
void readGraphFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // 读取顶点数和边数
    int n, m;
    inFile >> n >> m;
    edges.assign(m, Edge());
    for (int i = 0; i < m; i++)
        inFile >> edges[i].u >> edges[i].v >> edges[i].w;
    sort(edges.begin(), edges.end());

    Kruskal(edges,n);
    inFile.close();
}
void run(const std::string& filename) {
    readGraphFromFile(filename);
}