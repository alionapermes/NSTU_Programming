package main

import (
	"fmt"
	"math"

	"nstu/semester3/math/pkg/vector"
)

const eps = 1e-5

func main() {
	free := vector.New([]float64{38, 20, 52, 43})
	base := vector.New([]float64{0, 0, 0, 0})
	matrix := []*vector.Vector{
		vector.New([]float64{-19, 2, -1, -8}),
		vector.New([]float64{2, 14, 0, -4}),
		vector.New([]float64{6, -5, -20, -6}),
		vector.New([]float64{-6, 4, -2, 15}),
	}

	if IsDiagonallyDominant(matrix) {
		fmt.Println("the matrix is diagonally dominant")
	} else {
		fmt.Println("lox blyat")
	}

	vars, count := f(matrix, free, base, 0)

	fmt.Println("iterations:", count)
	for i := range vars.Items() {
		fmt.Printf("%.5f, ", vars.Get(i))
	}
	fmt.Println("\ndone")
}

func IsDiagonallyDominant(matrix []*vector.Vector) bool {
	size := len(matrix)

	for i := 0; i < size; i++ {
		var ii, sum float64

		for n := 0; n < size; n++ {
			if n == i {
				ii = math.Abs(matrix[i].Get(n))
			} else {
				sum += math.Abs(matrix[i].Get(n))
			}
		}

		if sum > ii {
			return false
		}
	}

	return true
}

func f(
	matrix []*vector.Vector,
	free, base *vector.Vector,
	count int,
) (*vector.Vector, int) {
	_base := vector.NewReserved(base.Length())

	for i := 0; i < free.Length(); i++ {
		tmpRow, _ := vector.Omit(matrix[i], i)
		tmpBase, _ := vector.Omit(base, i)
		prod, _ := vector.Product(tmpRow, tmpBase)
		*_base.At(i) = (free.Get(i) - prod) / matrix[i].Get(i)
	}

	for i := 0; i < free.Length(); i++ {
		if math.Abs(_base.Get(i)-base.Get(i)) >= eps {
			return f(matrix, free, _base, count+1)
		}
	}

	return _base, count + 1
}
