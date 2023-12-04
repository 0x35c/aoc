package main

import (
	"os"
	"fmt"
	"strings"
	"strconv"
	"sort"
)

func check(err error) {
	if err != nil {
		panic(err)
	}
}

func main() {
	var	tot []int
	var	sum int	
	input, err := os.ReadFile("input")
	check(err)
	parse_tab := strings.Split(string(input), "\n")
	for i := 0; i < len(parse_tab); i++ {
		if parse_tab[i] != "" {
			tmp, err := strconv.Atoi(parse_tab[i])
			sum += tmp
			check(err)
		} else {
			tot = append(tot, sum)
			sum = 0
		}
	}
	sort.Ints(tot)
	fmt.Println(tot)
}
