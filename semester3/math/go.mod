module nstu/semester3/math

go 1.18

replace nstu/semester3/math/pkg/common => ./pkg/common

replace nstu/semester3/math/pkg/lab3 => ./internal/lab3

require (
	nstu/semester3/math/pkg/common v0.0.0-00010101000000-000000000000
	nstu/semester3/math/pkg/lab3 v0.0.0-00010101000000-000000000000
)
