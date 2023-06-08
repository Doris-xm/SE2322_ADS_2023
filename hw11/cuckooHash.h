#ifndef HW11_CUCKOOHASH_H
#define HW11_CUCKOOHASH_H
#define SIZE (100000)
#include <mutex>
#include <cstdio>
#include <cstring>
#include <thread>
#include <cassert>

using namespace std;
namespace cuckoo {
    typedef int KeyType;
    class cuckooHash {
    protected:
        mutex mtx;
        KeyType T[SIZE];
        static int pre_hash1(const KeyType & key);
        static int pre_hash2(const KeyType & key);
        int (*hash1)(const KeyType&) ; //hash1 函数指针
        int (*hash2)(const KeyType&);
        static int new_hash1(const KeyType & key);
        static int new_hash2(const KeyType & key);
        // find key by hash func 1 in T, exist return key otherwise 0
        KeyType get1(const KeyType & key);
        KeyType get2(const KeyType & key);
//        void bt_evict(const KeyType & key, int which, int pre_pos);
        void rehash();

    public:
        cuckooHash();
        KeyType  get(const KeyType & key);
        void put(const KeyType & key);
        int threshold;

    };
};



#endif
