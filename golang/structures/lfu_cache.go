package structures

import "container/list"

type LFUEntry struct {
	key, value, freq int
}

type LFUCache struct {
	capacity int
	minFreq  int
	cache    map[int]*list.Element
	freqMap  map[int]*list.List
}

func NewLFUCache(cap int) *LFUCache {
	return &LFUCache{
		capacity: cap,
		cache:    make(map[int]*list.Element),
		freqMap:  make(map[int]*list.List),
	}
}

func (c *LFUCache) Get(key int) int {
	if elem, ok := c.cache[key]; ok {
		entry := elem.Value.(*LFUEntry)
		c.updateFreq(elem)
		return entry.value
	}
	return -1
}

func (c *LFUCache) Put(key int, value int) {
	if c.capacity <= 0 {
		return
	}

	if elem, ok := c.cache[key]; ok {
		entry := elem.Value.(*LFUEntry)
		entry.value = value
		c.updateFreq(elem)
		return
	}

	if len(c.cache) >= c.capacity {
		minList := c.freqMap[c.minFreq]
		back := minList.Back()
		evictEntry := back.Value.(*LFUEntry)
		delete(c.cache, evictEntry.key)
		minList.Remove(back)
		if minList.Len() == 0 {
			delete(c.freqMap, c.minFreq)
		}
	}

	entry := &LFUEntry{key: key, value: value, freq: 1}
	if _, ok := c.freqMap[1]; !ok {
		c.freqMap[1] = list.New()
	}
	elem := c.freqMap[1].PushFront(entry)
	c.cache[key] = elem
	c.minFreq = 1
}

func (c *LFUCache) updateFreq(elem *list.Element) {
	entry := elem.Value.(*LFUEntry)
	oldFreq := entry.freq
	listOld := c.freqMap[oldFreq]
	listOld.Remove(elem)
	if listOld.Len() == 0 {
		delete(c.freqMap, oldFreq)
		if c.minFreq == oldFreq {
			c.minFreq++
		}
	}

	entry.freq++
	if _, ok := c.freqMap[entry.freq]; !ok {
		c.freqMap[entry.freq] = list.New()
	}
	newElem := c.freqMap[entry.freq].PushFront(entry)
	c.cache[entry.key] = newElem
}
