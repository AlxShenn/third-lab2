package main

import (
	"bufio"
	"fmt"
	"golang/structures"
	"os"
	"strings"
)

func printHelp() {
	fmt.Println("=== Hash Set Manager ===")
	fmt.Println("Available commands:")
	fmt.Println("  SETADD <set_name> <value>  - add element to set")
	fmt.Println("  SETDEL <set_name> <value>  - remove element from set")
	fmt.Println("  SET_AT <set_name> <value>  - check if element is in set")
	fmt.Println("  HELP                       - show this message")
	fmt.Println("  EXIT                       - save and quit")
	fmt.Println("=========================")
}

func main() {
	sets := make(map[string]*structures.HashSet)

	printHelp()
	scanner := bufio.NewScanner(os.Stdin)

	for {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}

		parts := strings.Fields(line)
		cmd := strings.ToUpper(parts[0])

		if cmd == "EXIT" {
			break
		} else if cmd == "HELP" {
			printHelp()
			continue
		}

		if len(parts) < 3 {
			fmt.Println("Error: invalid command format. Type HELP.")
			continue
		}

		setName := parts[1]
		val := parts[2]

		if _, exists := sets[setName]; !exists {
			sets[setName] = structures.NewHashSet()
		}
		set := sets[setName]

		switch cmd {
		case "SETADD":
			set.Add(val)
			fmt.Printf("Added %s to %s\n", val, setName)
		case "SETDEL":
			if set.Remove(val) {
				fmt.Printf("Deleted %s from %s\n", val, setName)
			} else {
				fmt.Printf("Not found %s in %s\n", val, setName)
			}
		case "SET_AT":
			if set.Contains(val) {
				fmt.Printf("Yes, %s is in %s\n", val, setName)
			} else {
				fmt.Printf("No, %s is not in %s\n", val, setName)
			}
		default:
			fmt.Printf("Unknown command: %s\n", cmd)
		}
	}
}
