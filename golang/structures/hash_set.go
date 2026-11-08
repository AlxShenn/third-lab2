package structures

type HashSet struct {
	table map[string]bool
}

func NewHashSet() *HashSet {
	return &HashSet{table: make(map[string]bool)}
}

func (h *HashSet) Add(value string) {
	h.table[value] = true
}

func (h *HashSet) Remove(value string) bool {
	if _, exists := h.table[value]; exists {
		delete(h.table, value)
		return true
	}
	return false
}

func (h *HashSet) Contains(value string) bool {
	return h.table[value]
}

func (h *HashSet) GetSize() int {
	return len(h.table)
}

func (h *HashSet) GetAll() []string {
	keys := make([]string, 0, len(h.table))
	for k := range h.table {
		keys = append(keys, k)
	}
	return keys
}
