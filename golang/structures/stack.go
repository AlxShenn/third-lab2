package structures

import "fmt"

type Stack struct {
	items []string
}

func NewStack() *Stack {
	return &Stack{items: make([]string, 0)}
}

func (s *Stack) Push(value string) {
	s.items = append(s.items, value)
}

func (s *Stack) Pop() (string, bool) {
	if len(s.items) == 0 {
		return "", false
	}
	val := s.items[len(s.items)-1]
	s.items = s.items[:len(s.items)-1]
	return val, true
}

func (s *Stack) IsEmpty() bool {
	return len(s.items) == 0
}

func (s *Stack) Print() {
	if len(s.items) == 0 {
		fmt.Println("Empty")
		return
	}
	for _, item := range s.items {
		fmt.Print(item, " ")
	}
	fmt.Println()
}
