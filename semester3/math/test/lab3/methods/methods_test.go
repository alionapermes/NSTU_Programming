package methods

import (
	"fmt"
	. "nstu/semester3/math/pkg/common"
	"nstu/semester3/math/pkg/lab3/methods"
	"testing"
)

const eps = 1e-5

func TestIterations(t *testing.T) {
	free := NewVector([]float64{38, 20, 52, 43})
	base := NewVector([]float64{0, 0, 0, 0})
	matrix := []*Vector{
		NewVector([]float64{-19, 2, -1, -8}),
		NewVector([]float64{2, 14, 0, -4}),
		NewVector([]float64{6, -5, -20, -6}),
		NewVector([]float64{-6, 4, -2, 15}),
	}

	expectedVars := NewVector([]float64{-2, 2, -4, 1})

	vars, count := methods.Iterations(matrix, free, base, 0, eps)
	vars.RoundItems(4)

	if !expectedVars.Equals(vars) {
		t.Errorf(
			"Uncorrect result: expected %v; got %v\n",
			expectedVars.Items(),
			vars.Items(),
		)
	}

	fmt.Println("Iterations count:", count)
	fmt.Println("Variables:", vars.Items())
}

func TestSeidel(t *testing.T) {
	t.Error("method isn't implemented yet")
}
