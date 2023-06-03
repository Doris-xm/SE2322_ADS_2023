//#include "skiplist.h"
//#include "limits.h"
//#include "stdlib.h"
//#include "ctime"
//
//void SkipList::clear(node* &h) {
//    if( !h ) return;
//    clear(h->point_list[0]);
//    delete h;
//    h = nullptr;
//}
//
//SkipList::SkipList(double p) {
//    P = (p * 1000 + 0.5);
//    tail = new node(INT_MAX);
//    head = new node(INT_MIN,tail);
//    Max_level = 0;
//}
//SkipList::~SkipList() {
//    clear(head);
//}
//void SkipList::insert(int val) {
//    int curr_level = Max_level;
//    node* next = head;
//    node** update_list = new node*[Max_level + 1];
//
//
//    while(curr_level >= 0) {
//        if( val < next->point_list[curr_level]->key) {
//            update_list[curr_level] = next;//后续可能需要更新
//            curr_level--;
//            continue;
//        }
//        if( val == next->point_list[curr_level]->key){
//            delete []update_list;
//            return;
//        }
//        if( val > next->point_list[curr_level]->key)
//            next = next->point_list[curr_level];
//    }
//    node* NewNode = new node(val, next->point_list[0]);
//    next->point_list[0] = NewNode;
//
////    srand(time(nullptr));
//    int r = rand()% 1000;
//    while(r % 1000 < P){
//        r = rand()% 1000;
//        NewNode->level++;
//        if(NewNode->level > Max_level) {
//            Max_level++;
//            head->point_list.push_back(NewNode);
//            NewNode->point_list.push_back(tail);
//            head->level++;
//            tail->level++;
//            break;
//        }
//        else {
//            NewNode->point_list.push_back( update_list[NewNode->level] -> point_list[NewNode->level] );
//            update_list[NewNode->level] -> point_list[NewNode->level] = NewNode;
//        }
//    }
//
//    return;
//
//}
//
//int SkipList::search(int val) {
//    int step = 1;
//    int curr_level = Max_level;
//    node* next = head;
//
//    while(curr_level >= 0) {
//        step++;
//        if( val == next->point_list[curr_level]->key)
//            return step;
//
//        if( val < next->point_list[curr_level]->key)
//            curr_level--;
//        else
//            next = next->point_list[curr_level];
//    }
//    return 0;
//}
