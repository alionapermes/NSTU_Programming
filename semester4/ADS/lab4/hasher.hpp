#pragma once

#include <cmath>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>


using Hasher   = std::function<size_t (uint64_t, size_t)>;
using Resolver = std::function<size_t (uint64_t, size_t, size_t, Hasher)>;

size_t
module_hashing(uint64_t key, size_t size);

inline double
fract(double num);

uint64_t
to_natural(std::string_view sw);

uint64_t
multiplicative_method(std::string key);

uint64_t
convolution_method(uint64_t num);

uint64_t
choosing_number(uint64_t num);

uint64_t
linear_cr(uint64_t key, size_t size, size_t try_n, Hasher get_hash);

uint64_t
quadratic_cr(uint64_t key, size_t size, size_t try_n, Hasher get_hash);

