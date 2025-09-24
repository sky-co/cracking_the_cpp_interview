#include "perf_tunning_utility.h"
#include <cassert>
#include <iostream>

// NOINLINE 测试
NOINLINE void test_noinline_func() {
    std::cout << "NOINLINE function called." << std::endl;
}

// ALWAYS_INLINE 测试
ALWAYS_INLINE int always_inline_add(int a, int b) {
    return a + b;
}

// LIKELY/UNLIKELY 测试
void test_branch_prediction(int x) {
    if (LIKELY(x > 0)) {
        std::cout << "LIKELY branch taken." << std::endl;
    } else if (UNLIKELY(x < 0)) {
        std::cout << "UNLIKELY branch taken." << std::endl;
    } else {
        std::cout << "Neither branch taken." << std::endl;
    }
}

// PREFETCH 测试
void test_prefetch(const int* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        PREFETCH(&arr[i + 1]);
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// PERFORMANCE_SENSITIVE 测试
PERFORMANCE_SENSITIVE void performance_hot_func() {
    std::cout << "PERFORMANCE_SENSITIVE function called." << std::endl;
}

// PERFORMANCE_COLD 测试
PERFORMANCE_COLD void performance_cold_func() {
    std::cout << "PERFORMANCE_COLD function called." << std::endl;
}

// RESTRICT 测试
int restrict_sum(int* RESTRICT a, int* RESTRICT b, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i] + b[i];
    }
    return sum;
}

int main() {
    test_noinline_func();

    int sum = always_inline_add(2, 3);
    assert(sum == 5);

    test_branch_prediction(1);
    test_branch_prediction(-1);
    test_branch_prediction(0);

    int arr[] = {1, 2, 3, 4, 5};
    test_prefetch(arr, 5);

    performance_hot_func();
    performance_cold_func();

    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    assert(restrict_sum(a, b, 3) == 21);

    std::cout << "All perf_tunning_utility macro tests passed." << std::endl;
    return 0;
}
