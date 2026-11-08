package main

import (
	"bufio"
	"fmt"
	"golang/structures"
	"os"
	"strconv"
	"strings"
)

func main() {
	fmt.Print("Enter cache capacity: ")
	var cap int
	fmt.Scan(&cap)
	if cap <= 0 {
		fmt.Println("Invalid capacity.")
		return
	}

	// Очищаем буфер после ввода числа
	reader := bufio.NewReader(os.Stdin)
	reader.ReadString('\n')

	cache := structures.NewLFUCache(cap)
	fmt.Printf("Cache initialized with capacity %d.\n", cap)

	for {
		fmt.Print("> ")
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}

		parts := strings.Fields(line)
		cmd := strings.ToUpper(parts[0])

		if cmd == "EXIT" {
			break
		} else if cmd == "SET" {
			if len(parts) == 3 {
				k, _ := strconv.Atoi(parts[1])
				v, _ := strconv.Atoi(parts[2])
				cache.Put(k, v)
				fmt.Printf("Set [%d] = %d\n", k, v)
			} else {
				fmt.Println("Error: usage SET <key> <value>")
			}
		} else if cmd == "GET" {
			if len(parts) == 2 {
				k, _ := strconv.Atoi(parts[1])
				res := cache.Get(k)
				fmt.Println("->", res)
			} else {
				fmt.Println("Error: usage GET <key>")
			}
		} else {
			fmt.Println("Unknown command")
		}
	}
}
