#include "skipList.h"
#include <string>
#include <climits>

KVStore::KVStore()
{
    P = 368; // probability = 1/e
    tail = new node(INT_MAX);
    head = new node(INT_MIN,tail);
    Max_level = 0;
}

KVStore::~KVStore()
{
    clear(head);
}

/**
 * Insert/Update the key-value pair.
 * No return values for simplicity.
 */
void KVStore::put(uint64_t key)
{
    int curr_level = Max_level;
    node* next = head;
    node** update_list = new node*[Max_level + 1];


    while(curr_level >= 0) {
        if( key < next->point_list[curr_level]->key) {
            update_list[curr_level] = next;//后续可能需要更新
            curr_level--;
            continue;
        }
        if( key == next->point_list[curr_level]->key){
            delete []update_list;
            return;
        }
        if( key > next->point_list[curr_level]->key)
            next = next->point_list[curr_level];
    }
    node* NewNode = new node(key,next->point_list[0]);
    next->point_list[0] = NewNode;

//    srand(time(nullptr));
    int r = rand() % 1000;
    while(r % 1000 < P){
        r = rand() % 1000;
        NewNode->level++;
        if(NewNode->level > Max_level) {
            Max_level++;
            head->point_list.push_back(NewNode);
            NewNode->point_list.push_back(tail);
            head->level++;
            tail->level++;
            break;
        }
        else {
            NewNode->point_list.push_back( update_list[NewNode->level] -> point_list[NewNode->level] );
            update_list[NewNode->level] -> point_list[NewNode->level] = NewNode;
        }
    }

}
/**
 * Returns the (string) value of the given key.
 * An empty string indicates not found.
 */
uint64_t KVStore::get(uint64_t key)
{
    int curr_level = Max_level;
    node* next = head;

    while(curr_level >= 0) {
        if( key == next->point_list[curr_level]->key)
            return key;

        if( key < next->point_list[curr_level]->key)
            curr_level--;
        else
            next = next->point_list[curr_level];
    }

    return -1;
}
/**
 * Delete the given key-value pair if it exists.
 * Returns false iff the key is not found.
 */
bool KVStore::del(uint64_t key)
{
    int curr_level = Max_level;
    node* next = head;

    while(curr_level >= 0) {
        if( key < next->point_list[curr_level]->key) {
            curr_level--;
            continue;
        }
        if( key == next->point_list[curr_level]->key)
            break;

        if( key > next->point_list[curr_level]->key)
            next = next->point_list[curr_level];
    }

    if(curr_level < 0) return false;

    node** update_list = new node*[curr_level + 1];
    int update_level = curr_level;
    while(curr_level >= 0) {
        if( key == next->point_list[curr_level]->key) {
            update_list[curr_level] = next;//后续可能需要更新
            curr_level--;
            continue;
        }
        next = next->point_list[curr_level];
    }
    next = next->point_list[0];

    while(update_level >= 0) {
        if(update_level && update_level == Max_level && update_list[update_level]->key == head->key && next->point_list[update_level]->key == tail->key) {
            head->point_list.pop_back();
            tail->point_list.pop_back();
            Max_level--;
        }
        else
            update_list[update_level]->point_list[update_level] = next->point_list[update_level];

        update_level --;
    }
    delete next;
    delete []update_list;
    return true;
}

/**
 * This resets the kvstore. All key-value pairs should be removed,
 * including memtable and all sstables files.
 */
void KVStore::reset()
{
    clear(head);
    tail = new node(INT_MAX);
    head = new node(INT_MIN,tail);
    Max_level = 0;
}


void KVStore::clear(node *&h) {
    if( !h ) return;
    clear(h->point_list[0]);
    delete h;
    h = nullptr;
}