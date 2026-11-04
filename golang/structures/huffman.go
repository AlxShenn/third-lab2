package structures

import (
	"container/heap"
	"fmt"
)

type HuffmanNode struct {
	ch    rune
	freq  int
	left  *HuffmanNode
	right *HuffmanNode
}

type PriorityQueue []*HuffmanNode

func (pq PriorityQueue) Len() int            { return len(pq) }
func (pq PriorityQueue) Less(i, j int) bool  { return pq[i].freq < pq[j].freq }
func (pq PriorityQueue) Swap(i, j int)       { pq[i], pq[j] = pq[j], pq[i] }
func (pq *PriorityQueue) Push(x interface{}) { *pq = append(*pq, x.(*HuffmanNode)) }
func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	*pq = old[0 : n-1]
	return item
}

type HuffmanCoder struct {
	root  *HuffmanNode
	codes map[rune]string
}

func NewHuffmanCoder() *HuffmanCoder {
	return &HuffmanCoder{codes: make(map[rune]string)}
}

func (h *HuffmanCoder) BuildTree(text string) {
	freq := make(map[rune]int)
	for _, ch := range text {
		freq[ch]++
	}

	pq := &PriorityQueue{}
	heap.Init(pq)
	for ch, f := range freq {
		heap.Push(pq, &HuffmanNode{ch: ch, freq: f})
	}

	for pq.Len() > 1 {
		left := heap.Pop(pq).(*HuffmanNode)
		right := heap.Pop(pq).(*HuffmanNode)
		parent := &HuffmanNode{
			freq:  left.freq + right.freq,
			left:  left,
			right: right,
		}
		heap.Push(pq, parent)
	}

	if pq.Len() > 0 {
		h.root = heap.Pop(pq).(*HuffmanNode)
		h.codes = make(map[rune]string)
		h.generateCodes(h.root, "")
	}
}

func (h *HuffmanCoder) generateCodes(node *HuffmanNode, code string) {
	if node == nil {
		return
	}
	if node.left == nil && node.right == nil {
		h.codes[node.ch] = code
	}
	h.generateCodes(node.left, code+"0")
	h.generateCodes(node.right, code+"1")
}

func (h *HuffmanCoder) Encode(text string) string {
	res := ""
	for _, ch := range text {
		res += h.codes[ch]
	}
	return res
}

func (h *HuffmanCoder) Decode(encoded string) string {
	res := ""
	cur := h.root
	for _, bit := range encoded {
		if bit == '0' {
			cur = cur.left
		} else {
			cur = cur.right
		}
		if cur.left == nil && cur.right == nil {
			res += string(cur.ch)
			cur = h.root
		}
	}
	return res
}

func (h *HuffmanCoder) PrintCodes() {
	for ch, code := range h.codes {
		fmt.Printf("'%c': %s\n", ch, code)
	}
}
