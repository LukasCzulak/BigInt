#include <benchmark/benchmark.h>

#include <random>
#include <string>

#include "BigInt.hpp"
#include "Utils.hpp"

static std::string generate_digits(size_t num_digits, uint32_t seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> first_digit_generator(1, 9);
    std::uniform_int_distribution<int> other_digit_generator(0, 9);

    std::string s;
    s.reserve(num_digits);
    s.push_back('0' + first_digit_generator(rng));
    for (size_t i = 1; i < num_digits; ++i) {
        s.push_back('0' + other_digit_generator(rng));
    }
    return s;
}

static void Benchmark_BigIntAdd(benchmark::State& state) {
    // Setup
    const size_t n = state.range(0);
    const BigInt a(generate_digits(n, 42));
    const BigInt b(generate_digits(n, 1337));

    // timed from now
    for (auto _ : state) {
        BigInt res = a + b;
        // DoNotOptimize such that res is not skipped by compiler.
        benchmark::DoNotOptimize(res);
    }

    state.SetComplexityN(n);
}

static void Benchmark_BigIntMultiply(benchmark::State& state) {
    const size_t n = state.range(0);
    const BigInt a(generate_digits(n, 42));
    const BigInt b(generate_digits(n, 1337));

    for (auto _ : state) {
        BigInt res = a * b;
        benchmark::DoNotOptimize(res);
    }

    state.SetComplexityN(n);
}

static void Benchmark_BigIntInitString(benchmark::State& state) {
    const size_t n = state.range(0);
    const std::string str = generate_digits(n, 42);

    for (auto _ : state) {
        BigInt res = BigInt(str);
        benchmark::DoNotOptimize(res);
    }

    state.SetComplexityN(n);
}

static void Benchmark_BigIntToString(benchmark::State& state) {
    const size_t n = state.range(0);
    const std::string str = generate_digits(n, 42);
    const BigInt bi(str);

    for (auto _ : state) {
        std::string res = bi.toString();
        benchmark::DoNotOptimize(res);
    }

    state.SetComplexityN(n);
}

static void Benchmark_BigIntPipeline(benchmark::State& state) {
    const size_t n = state.range(0);
    const std::string str1 = generate_digits(n, 42);
    const std::string str2 = generate_digits(n, 1337);
    const std::string expr =
        "(" + str1 + "+" + str2 + ")" + "*" + "(" + str2 + "+" + str1 + ")";

    for (auto _ : state) {
        BigInt res = parse_and_evaluate(expr);
        benchmark::DoNotOptimize(res);
    }

    state.SetComplexityN(n);
}

BENCHMARK(Benchmark_BigIntAdd)
    ->RangeMultiplier(4)
    ->Range(16, 65536)
    ->Complexity();

BENCHMARK(Benchmark_BigIntMultiply)
    ->RangeMultiplier(2)
    ->Range(16, 1024)
    ->Complexity();

BENCHMARK(Benchmark_BigIntInitString)
    ->RangeMultiplier(4)
    ->Range(16, 65536)
    ->Complexity();

BENCHMARK(Benchmark_BigIntToString)
    ->RangeMultiplier(4)
    ->Range(16, 65536)
    ->Complexity();

BENCHMARK(Benchmark_BigIntPipeline)
    ->RangeMultiplier(2)
    ->Range(16, 1024)
    ->Complexity();