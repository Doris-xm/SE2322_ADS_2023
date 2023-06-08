#include "cuckooHash.h"
namespace cuckoo {
    template<typename T>
    inline void swap(T *a, T *b) {
        assert(a != NULL && b != NULL);
        T tmp = *a;
        *a = *b;
        *b = tmp;
    }

    cuckooHash::cuckooHash() {
        memset(T, 0, sizeof(KeyType) * SIZE);
        threshold = 100;
        hash1 =  &cuckooHash::pre_hash1;
        hash2 = &cuckooHash::pre_hash2;
    }

    int cuckooHash::pre_hash1(const KeyType &key) {
        assert(SIZE != 0);
        int half_size = SIZE / 2;
        return key % half_size;
    }

    int cuckooHash::pre_hash2(const KeyType &key) {
        assert(SIZE != 0);
        int half_size = SIZE / 2;
        return half_size + key / half_size % half_size;
    }

    KeyType cuckooHash::get1(const KeyType &key) {
        return (T[hash1(key)] == key) ? key : 0;
    }

    KeyType cuckooHash::get2(const KeyType &key) {
        return (T[hash2(key)] == key) ? key : 0;
    }

    KeyType cuckooHash::get(const KeyType &key) {
        // 0 is reserved for null, invalid input
        if (key == 0) {
            printf("invalid key\n");
            return 0;
        }
        KeyType ret = get1(key);
        if (ret == 0) ret = get2(key);
        return ret;
    }


    void cuckooHash::put(const KeyType &key) {
        // 0 is reserved for null, invalid input
        if (key == 0) {
            printf("invalid key\n");
            return;
        }

        if (get(key) != 0) {
            printf("duplicate key, put fail\n");
            return;
        }
        if (T[hash1(key)] == 0) {
            T[hash1(key)] = key;
        } else if (T[hash2(key)] == 0) {
            T[hash2(key)] = key;
        } else { // need to evict
            unique_lock<mutex> lck(mtx); // lock

            KeyType evicted = key; // evicted key
            int which = 0;
            int idx = hash1(evicted); // evicted key's new position
            int pre_pos = -1;
            int count = 0;
            while (T[idx] != 0) {
                printf("evicted key %d from %d to %d\n", evicted, pre_pos, idx);
                swap(&T[idx], &evicted);
                pre_pos = idx;
                which = 1 - which;
                idx = (which == 0) ? hash1(evicted) : hash2(evicted);
                if(count > threshold) {
                    printf("evict fail\n");
                    rehash();
                    return;
                }
                count++;
            }
            printf("evicted key %d from %d to %d\n", evicted, pre_pos, idx);
            T[idx] = evicted;
        }
    }


    int cuckooHash::new_hash1(const KeyType& key) {
        assert(SIZE != 0);
        static const int prime1 = 100019;
        return (prime1 * key) % SIZE;
    }

    int cuckooHash::new_hash2(const KeyType& key) {
        assert(SIZE != 0);
        static const int prime2 = 100043;
        return (prime2 * key) % SIZE;
    }

    void cuckooHash::rehash() {
        KeyType tmp[SIZE];
        memcpy(tmp, T, sizeof(KeyType) * SIZE);
        memset(T, 0, sizeof(KeyType) * SIZE);
        hash1 = &cuckooHash::new_hash1;
        hash2 = &cuckooHash::new_hash2;
        for (int i = 0; i < SIZE; i++) {
            if (tmp[i] != 0) {
                put(tmp[i]);
            }
        }
    }

};