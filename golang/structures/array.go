package structures

import (
	"fmt"
	"strings"
)

type Array struct {
	data []string
}

func NewArray() *Array {
	return &Array{data: make([]string, 0)}
}

func (a *Array) AddEnd(text string) {
	a.data = append(a.data, text)
}

func (a *Array) AddIndex(text string, index int) {
	if index < 0 || index > len(a.data) {
		return
	}
	a.data = append(a.data, "")
	copy(a.data[index+1:], a.data[index:])
	a.data[index] = text
}

func (a *Array) Get(index int) string {
	if index < 0 || index >= len(a.data) {
		return ""
	}
	return a.data[index]
}

func (a *Array) RemoveIndex(index int) {
	if index < 0 || index >= len(a.data) {
		return
	}
	a.data = append(a.data[:index], a.data[index+1:]...)
}

func (a *Array) Length() int {
	return len(a.data)
}

func (a *Array) Print() {
	fmt.Println(strings.Join(a.data, " "))
}
