#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <string>
#include "dlist.h"

using namespace std;

class LFUCache {
private:
    struct CacheNode {
        int key;
        int value;
        int freq;
        CacheNode* next;
        CacheNode(int k, int v, int f, CacheNode* n = nullptr) 
            : key(k), value(v), freq(f), next(n) {}
    };

    struct FreqNode {
        int freq;
        Dlist keyList; 
        FreqNode* next;
        FreqNode(int f, FreqNode* n = nullptr) : freq(f), next(n) {
            DInitialize(keyList); 
        }
    };

    int capacity;
    int currentSize;
    int minFreq;

    CacheNode* cacheHead; 
    FreqNode* freqHead;   

    CacheNode* findCacheNode(int key);
    void removeCacheNode(int key);
    Dlist& getFreqDlist(int freq);

public:
    LFUCache(int cap);
    ~LFUCache();
    int get(int key);
    void put(int key, int value);
};

#endif