package main

import (
	"bufio"
	"fmt"
	"golang/structures"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Enter your text: ")
	text, _ := reader.ReadString('\n')

	uniqueChars := structures.NewArray()
	counts := make(map[rune]int)

	for _, c := range text {
		if c != ' ' && c != '\n' && c != '\r' {
			if counts[c] == 0 {
				uniqueChars.AddEnd(string(c))
			}
			counts[c]++
		}
	}

	if uniqueChars.Length() == 0 {
		fmt.Println("No characters to display.")
		return
	}

	maxHeight := 0
	for _, v := range counts {
		if v > maxHeight {
			maxHeight = v
		}
	}

	for h := maxHeight; h > 0; h-- {
		for i := 0; i < uniqueChars.Length(); i++ {
			c := rune(uniqueChars.Get(i)[0])
			if counts[c] >= h {
				fmt.Print("#")
			} else {
				fmt.Print(" ")
			}
		}
		fmt.Println()
	}

	for i := 0; i < uniqueChars.Length(); i++ {
		fmt.Print(uniqueChars.Get(i))
	}
	fmt.Println()
}
