#pragma once

class BloomFilter
{
    int bit_m;
    int ele_n;
    int hash_k;

    int* Bit;
    int Hash(int value)const;

public:
    BloomFilter(int n, int m, int k);
    ~BloomFilter();
    void insert(int key);
    bool find(int key) const;


};
