package methods

import (
	"fmt"
	. "nstu/semester3/math/pkg/common"
	"nstu/semester3/math/pkg/lab3"
	"testing"
)

const eps = 1e-5

func TestIterations(t *testing.T) {
	les := LinearEquationsSystem{
		Free: NewVector([]float64{38, 20, 52, 43}),
		Equations: NewMatrix([]*Vector{
			NewVector([]float64{-19, 2, -1, -8}),
			NewVector([]float64{2, 14, 0, -4}),
			NewVector([]float64{6, -5, -20, -6}),
			NewVector([]float64{-6, 4, -2, 15}),
		}),
		Eps: eps,
	}

	expectedResult := SolutionResult{
		Variables:       NewVector([]float64{-2, 2, -4, 1}),
		IterationsCount: 24,
	}

	solutionResult := les.Solve(lab3.IterationsMethod)
	solutionResult.Variables.RoundItems(4)

	if !solutionResult.Equals(expectedResult) {
		t.Errorf(
			"Uncorrect result: expected %v; got %v\n",
			expectedResult.Variables.Items(),
			solutionResult.Variables.Items(),
		)
	}

	fmt.Println("Iterations count:", solutionResult.IterationsCount)
	fmt.Println("Variables:", solutionResult.Variables.Items())
}

// func TestSeidel(t *testing.T) {
// 	t.Error("method isn't implemented yet")
// }
