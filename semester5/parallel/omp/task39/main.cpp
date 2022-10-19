#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdio.h>

#include <omp.h>

struct match;
struct computing_result;

using matches      = std::array<match, 6>;
using compute_func = computing_result (*)(uint64_t);


struct match
{
    uint8_t  value;
    uint64_t count;
};

struct computing_result
{
    uint64_t value;
    double time;
};


matches
get_primes(uint64_t N)
{
    match p0{0, 0},
          p1{1, 0},
          p2{2, 0},
          p3{3, 0},
          p5{5, 0},
          p7{7, 0};

	for (; N > 0; N /= 10) {
		uint8_t dig = N % 10;

        if (dig == 0) {
            ++p0.count;
        } else if (dig == 1) {
            ++p1.count;
        } else if (dig == 2) {
            ++p2.count;
        } else if (dig == 3) {
            ++p3.count;
        } else if (dig == 4) {
            p2.count += 2;
        } else if (dig == 5) {
            ++p5.count;
        } else if (dig == 6) {
            ++p2.count;
            ++p3.count;
        } else if (dig == 7) {
            ++p7.count;
        } else if (dig == 8) {
            p2.count += 3;
        } else if (dig == 9) {
            p3.count += 2;
        }
    }

    return {p0, p1, p2, p3, p5, p7};
}

bool
is_array_degree(const matches& primes)
{
    if (primes[0].count > 0) {
        return false;
    }

	uint8_t variants_count{};
	uint64_t rarest{};

    for (const auto& prime : primes) {
        if (prime.count > 0) {
            variants_count++;
        }
    }

    rarest = std::min_element(primes.begin(), primes.end(),
        [] (const match& lhs, const match& rhs) -> bool {
            if (rhs.count == 0) {
                return true;
            }
            if (lhs.count == 0) {
                return false;
            }
            return lhs.count < rhs.count;
        }
    )->count;

	if (rarest == 1) {
        return false;
    }

	if (variants_count == 1) { 
        return rarest > 1; // is digit
	}

    for (const auto& prime : primes) {
        if (prime.count % rarest != 0) {
            return false;
        }
    }

	return true;
}

bool
is_number_degree(uint64_t N)
{ return is_array_degree(get_primes(N)); }

computing_result
compute_linear(uint64_t N)
{
	double time = omp_get_wtime();

	for (uint64_t n = N + 1; n < ULLONG_MAX; ++n) {
		if (is_number_degree(n)) {
			return {n, omp_get_wtime() - time};
		}
	}

	return {0, omp_get_wtime() - time};
};

computing_result
compute_parallel(uint64_t N)
{
	const uint8_t threads_count = 4;
	omp_set_num_threads(threads_count);

	bool found      = false;
	uint64_t result = ULLONG_MAX;
	double time     = omp_get_wtime();

#pragma omp parallel
    for (
        uint64_t n = N + 1 + omp_get_thread_num();
        !found;
        n += threads_count
    ) {
        if (is_number_degree(n)) {
#pragma omp critical
            if (n < result) {
                result = n;
                found  = true;
            }
        }
    }

	return {result, omp_get_wtime() - time};
}

int
main()
{
	char mode;
	uint64_t n;
    const char* label;
    compute_func f;

    printf(
        "Task #39\nType 0 to exit at anytime\n\n"
        "Enter N: "
    );

    std::cin >> n;

	while (true) {
        printf("mode ([s]equential/[p]arallel): ");
        std::cin >> mode;

        if (mode == '0') {
            printf("\nExiting…\n");
            return 0;
        } else if (mode == 's') {
            f     = compute_linear;
            label = "Sequential";
        } else if (mode == 'p') {
            f     = compute_parallel;
            label = "Parallel";
        }

        auto result = f(n);

        printf(
            "\n[RESULTS]\n"
            "%s: %lu (%fs)\n\n",
            label, result.value, result.time
        );
	}
}

