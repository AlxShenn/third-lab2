#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <unordered_map>
#include <map>
#include <list>
#include <utility>

using namespace std;

class LFUCache {
private:
    int capacity;
    int minFreq;

    unordered_map<int, pair<int, int>> cache;
    map<int, list<int>> freqMap;

public:
    LFUCache(int cap);
    int get(int key);
    void put(int key, int value);
};

#endif