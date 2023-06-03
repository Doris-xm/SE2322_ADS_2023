#include "BloomFilter.h"
#include <functional>

BloomFilter::BloomFilter(int n, int m, int k) {
    bit_m = m;
    ele_n = n;
    hash_k = k;
    Bit = new int[bit_m];
    for(int i =0;i<m;++i)
        Bit[i] = 0;

}

BloomFilter::~BloomFilter() {
    delete Bit;
}

void BloomFilter::insert(const int key) {
//    std::hash<int> h;
//    for(int i =0;i < hash_k;++i)
//        Bit[h(key + i) % bit_m] = 1;
    for(int i =0;i < hash_k;++i)
        Bit[Hash(key + i * 107 ) ] = 1;

}

bool BloomFilter::find(const int key)const {
//    std::hash<int> h;
//    for(int i =0;i < hash_k;++i)
//        if( !Bit[h(key + i) % bit_m] )
//            return false;
    for(int i =0;i < hash_k;++i)
        if( !Bit[Hash(key + i * 107 ) ] )
            return false;
    return true;
}

int BloomFilter::Hash(const int value) const {
    return (value * 17 / 11) % bit_m;
}