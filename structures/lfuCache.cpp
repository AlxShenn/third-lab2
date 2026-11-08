#include "lfuCache.h"

LFUCache::LFUCache(int cap) : capacity(cap), minFreq(0) {}

int LFUCache::get(int key) {
    if (cache.find(key) == cache.end()) {
        return -1;
    }
    
    int val = cache[key].first;
    int freq = cache[key].second;
    
    freqMap[freq].remove(key);
    if (freqMap[freq].empty()) {
        freqMap.erase(freq);
        if (minFreq == freq) minFreq++;
    }
    
    cache[key].second++;
    freqMap[freq + 1].push_back(key);
    
    return val;
}

void LFUCache::put(int key, int value) {
    if (capacity <= 0) return;

    if (cache.find(key) != cache.end()) {
        cache[key].first = value;
        get(key);
        return;
    }

    if (cache.size() == capacity) {
        int evictKey = freqMap[minFreq].front();
        freqMap[minFreq].pop_front();
        if (freqMap[minFreq].empty()) {
            freqMap.erase(minFreq);
        }
        cache.erase(evictKey);
    }

    cache[key] = {value, 1};
    freqMap[1].push_back(key);
    minFreq = 1;
}