package methods

import (
	"fmt"
	"nstu/semester3/math/pkg/common/vector"
	"nstu/semester3/math/pkg/lab3/methods"
	"testing"
)

const eps = 1e-5

func TestIterations(t *testing.T) {
	free := vector.New([]float64{38, 20, 52, 43})
	base := vector.New([]float64{0, 0, 0, 0})
	matrix := []*vector.Vector{
		vector.New([]float64{-19, 2, -1, -8}),
		vector.New([]float64{2, 14, 0, -4}),
		vector.New([]float64{6, -5, -20, -6}),
		vector.New([]float64{-6, 4, -2, 15}),
	}

	expectedVars := vector.New([]float64{-2, 2, -4, 1})

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
	fmt.Println("Variables", vars.Items())
}
