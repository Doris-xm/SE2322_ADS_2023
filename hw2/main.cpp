#include <algorithm>
#include <iostream>
#include "ctime"
#include "stdlib.h"
#include <vector>
//#include "skiplist.h"
#include "SkipListTest.h"

const int Size = 1000;
vector<int> temp;


void rand_gen() { // 随机生成0 — Size-1乱序数
    for (int i = 0; i < Size; ++i) {
        temp.push_back(i);
    }
    random_shuffle(temp.begin(), temp.end());

}
int get_rand() {
    return rand()%Size;
}

int main() {
//    double p = 1/ 2.7183;
//    srand(time(nullptr));
//    double p = 0.4;
//    SkipList sl(p);
//    rand_gen();
//    for(auto it = temp.begin();it != temp.end();++it)
//        sl.insert((*it));
//
//
//
//    double ave = 0;
//    for(int i = 0; i < 10000;++i){
//        int random = get_rand();
//        ave += sl.search(random);
//    }
//    cout<<"average search length is "<<ave / 10000.<<endl;

    class KVStore store;
    store.put(1, "SE");
    cout<<store.del(1)<<endl;
    cout<<store.del(1)<<endl;
    return 0;
}
