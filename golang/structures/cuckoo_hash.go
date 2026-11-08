package structures

import "hash/fnv"

type CuckooHash struct {
	table1   []string
	table2   []string
	occupied []bool
	capacity int
}

func NewCuckooHash(cap int) *CuckooHash {
	if cap <= 0 {
		cap = 100
	}
	return &CuckooHash{
		table1:   make([]string, cap),
		table2:   make([]string, cap),
		occupied: make([]bool, cap),
		capacity: cap,
	}
}

func hash1(key string, cap int) int {
	h := fnv.New32a()
	h.Write([]byte(key))
	return int(h.Sum32()) % cap
}

func hash2(key string, cap int) int {
	h := fnv.New32a()
	h.Write([]byte(key + "salt"))
	return int(h.Sum32()) % cap
}

func (c *CuckooHash) Add(key string) {
	if c.Contains(key) {
		return
	}

	for i := 0; i < 100; i++ {
		pos1 := hash1(key, c.capacity)
		if !c.occupied[pos1] {
			c.table1[pos1] = key
			c.occupied[pos1] = true
			return
		}
		c.table1[pos1], key = key, c.table1[pos1]

		pos2 := hash2(key, c.capacity)
		if !c.occupied[pos2] {
			c.table2[pos2] = key
			c.occupied[pos2] = true
			return
		}
		c.table2[pos2], key = key, c.table2[pos2]
	}
}

func (c *CuckooHash) Contains(key string) bool {
	pos1 := hash1(key, c.capacity)
	if c.occupied[pos1] && c.table1[pos1] == key {
		return true
	}
	pos2 := hash2(key, c.capacity)
	if c.occupied[pos2] && c.table2[pos2] == key {
		return true
	}
	return false
}
