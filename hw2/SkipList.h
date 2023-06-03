//#pragma once
//#include <vector>
//using namespace std;
//
//struct node{
//    int key;
//    int level;
//    vector<node*> point_list;
//    node(int k = 0,node* n = nullptr,int l = 0):key(k),level(l) {
//        point_list.push_back(n);
//    }
//};
//
//class SkipList{
//    int Max_level;
//    node* head;
//    node* tail;
//    int P;
//public:
//    SkipList(double p);
//    ~SkipList();
//    void insert(int val);
//    int search(int val);
//    void clear(node* &h);
//};
//
