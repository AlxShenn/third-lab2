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
	reader := bufio.NewReader(os.Stdin)
	fmt.Println("Enter the expression separated by spaces:")
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)

	stack := structures.NewStack()
	tokens := strings.Fields(input)
	isError := false

	for _, token := range tokens {
		if token == "+" || token == "-" || token == "*" || token == "/" {
			op1Str, ok1 := stack.Pop()
			op2Str, ok2 := stack.Pop()
			if !ok1 || !ok2 {
				isError = true
				break
			}
			op1, _ := strconv.Atoi(op1Str)
			op2, _ := strconv.Atoi(op2Str)
			var res int
			switch token {
			case "+":
				res = op2 + op1
			case "-":
				res = op2 - op1
			case "*":
				res = op2 * op1
			case "/":
				if op1 == 0 {
					fmt.Println("Error: division by zero!")
					isError = true
					break
				}
				res = op2 / op1
			}
			stack.Push(strconv.Itoa(res))
		} else {
			stack.Push(token)
		}
	}

	if !isError {
		if res, ok := stack.Pop(); ok && stack.IsEmpty() {
			fmt.Println("Result:", res)
		} else {
			fmt.Println("Error: invalid expression")
		}
	} else {
		fmt.Println("Error in expression")
	}
}
