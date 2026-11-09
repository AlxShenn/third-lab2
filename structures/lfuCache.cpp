#include "lfuCache.h"

LFUCache::LFUCache(int cap) 
    : capacity(cap), currentSize(0), minFreq(0), cacheHead(nullptr), freqHead(nullptr) {}

LFUCache::~LFUCache() {
    while (cacheHead != nullptr) {
        CacheNode* temp = cacheHead;
        cacheHead = cacheHead->next;
        delete temp;
    }

    while (freqHead != nullptr) {
        FreqNode* temp = freqHead;
        freqHead = freqHead->next;
        DFree(temp->keyList); 
        delete temp;
    }
}

LFUCache::CacheNode* LFUCache::findCacheNode(int key) {
    CacheNode* cur = cacheHead;
    while (cur != nullptr) {
        if (cur->key == key) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void LFUCache::removeCacheNode(int key) {
    CacheNode* cur = cacheHead;
    CacheNode* prev = nullptr;
    while (cur != nullptr) {
        if (cur->key == key) {
            if (prev != nullptr) prev->next = cur->next;
            else cacheHead = cur->next;
            delete cur;
            currentSize--;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

Dlist& LFUCache::getFreqDlist(int freq) {
    FreqNode* cur = freqHead;
    while (cur != nullptr) {
        if (cur->freq == freq) {
            return cur->keyList;
        }
        cur = cur->next;
    }

    freqHead = new FreqNode(freq, freqHead);
    return freqHead->keyList;
}

int LFUCache::get(int key) {
    CacheNode* node = findCacheNode(key);
    if (node == nullptr) {
        return -1;
    }
    
    int val = node->value;
    int freq = node->freq;
    string keyStr = to_string(key);
    
    Dlist& oldList = getFreqDlist(freq);
    DDeleteValue(oldList, keyStr);
    
    if (oldList.head == nullptr) {
        if (minFreq == freq) minFreq++;
    }

    node->freq++;
    Dlist& newList = getFreqDlist(freq + 1);
    DPushTail(newList, keyStr);
    
    return val;
}

void LFUCache::put(int key, int value) {
    if (capacity <= 0) return;

    CacheNode* node = findCacheNode(key);
    if (node != nullptr) {
        node->value = value;
        get(key); 
        return;
    }

    if (currentSize == capacity) {
        Dlist& minList = getFreqDlist(minFreq);
        if (minList.head != nullptr) {
            int evictKey = stoi(minList.head->text); 
            DDeleteHead(minList);                    
            removeCacheNode(evictKey);              
        }
    }

    cacheHead = new CacheNode(key, value, 1, cacheHead);
    currentSize++;
    
    Dlist& list1 = getFreqDlist(1);
    DPushTail(list1, to_string(key));
    minFreq = 1;
}