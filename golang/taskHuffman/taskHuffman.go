package main

import (
	"bufio"
	"fmt"
	"golang/structures"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Enter string to encode: ")
	text, _ := reader.ReadString('\n')
	text = strings.TrimSpace(text)

	if text == "" {
		fmt.Println("Empty string.")
		return
	}

	coder := structures.NewHuffmanCoder()
	coder.BuildTree(text)

	fmt.Println("\n--- Codes Table ---")
	coder.PrintCodes()

	encoded := coder.Encode(text)
	fmt.Println("\nEncoded string:\n", encoded)

	decoded := coder.Decode(encoded)
	fmt.Println("\nDecoded string:\n", decoded)

	if decoded == text {
		fmt.Println("\n[SUCCESS] Decoded text matches the original!")
	} else {
		fmt.Println("\n[ERROR] Decoded text does NOT match!")
	}
}
