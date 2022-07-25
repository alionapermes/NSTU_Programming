package main

import (
	"fmt"
	"math"
)

const eps = 1e-5

func main() {
	free := []float64{38, 20, 52, 43}
	base := []float64{0, 0, 0, 0}
	matrix := [][]float64{
		[]float64{-19, 2, -1, -8},
		[]float64{2, 14, 0, -4},
		[]float64{6, -5, -20, -6},
		[]float64{-6, 4, -2, 15},
	}

	if IsDiagonallyDominant(matrix) {
		fmt.Println("the matrix is diagonally dominant")
	} else {
		fmt.Println("lox blyat")
	}

	vars, count := f(matrix, free, base, 0)

	fmt.Println("iterations:", count)
	for _, item := range vars {
		fmt.Printf("%.5f, ", item)
	}
	fmt.Println("\ndone")
}

func IsDiagonallyDominant(matrix [][]float64) bool {
	size := len(matrix)

	for i := 0; i < size; i++ {
		var ii, sum float64

		for n := 0; n < size; n++ {
			if n == i {
				ii = math.Abs(matrix[i][n])
			} else {
				sum += math.Abs(matrix[i][n])
			}
		}

		if sum > ii {
			return false
		}
	}

	return true
}

func f(matrix [][]float64, free, base []float64, count int) ([]float64, int) {
	_base := make([]float64, len(base))

	for i := 0; i < len(free); i++ {
		prod := Product(Omit(matrix[i], i), Omit(base, i))
		_base[i] = (free[i] - prod) / matrix[i][i]
	}

	for i := 0; i < len(free); i++ {
		if math.Abs(_base[i]-base[i]) >= eps {
			return f(matrix, free, _base, count+1)
		}
	}

	return _base, count + 1
}

func Product(v1, v2 []float64) float64 {
	var prod float64

	for i := 0; i < len(v1); i++ {
		prod += v1[i] * v2[i]
	}

	return prod
}

func Sum(vec []float64) float64 {
	var sum float64

	for _, item := range vec {
		sum += item
	}

	return sum
}

func Omit(vec []float64, index int) []float64 {
	newVec := make([]float64, len(vec)-1)

	for i, item := range vec {
		if i == index {
			continue
		}
		newVec = append(newVec, item)
	}

	return newVec
}
