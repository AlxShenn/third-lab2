package main

import (
	"fmt"
	"golang/structures"
	"strconv"
)

func main() {
	var N int
	fmt.Print("Enter number of turtles N: ")
	fmt.Scan(&N)

	validClaims := structures.NewHashSet()

	fmt.Println("Enter pairs (a_i b_i):")
	for i := 0; i < N; i++ {
		var a, b int
		fmt.Scan(&a, &b)
		if a+b+1 == N {
			claim := strconv.Itoa(a) + "_" + strconv.Itoa(b)
			validClaims.Add(claim)
		}
	}

	fmt.Println("Max truthful turtles:", validClaims.GetSize())
}
