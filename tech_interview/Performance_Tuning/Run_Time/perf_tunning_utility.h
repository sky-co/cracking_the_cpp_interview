#ifndef PERF_TUNNING_UTILITY_H
#define PERF_TUNNING_UTILITY_H

// 禁止函数内联
#ifdef __GNUC__
#define NOINLINE __attribute__((noinline))
#else
#define NOINLINE
#endif

// 强制函数内联
#ifdef __GNUC__
#define ALWAYS_INLINE inline __attribute__((always_inline))
#else
#define ALWAYS_INLINE inline
#endif

// 分支预测：标记条件更可能/不太可能为真
#ifdef __GNUC__
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#endif

// 预取内存地址，优化缓存命中率
#ifdef __GNUC__
#define PREFETCH(x) __builtin_prefetch(x)
#else
#define PREFETCH(x)
#endif

// 标记函数为性能热点
#ifdef __GNUC__
#define PERFORMANCE_SENSITIVE __attribute__((hot))
#define PERFORMANCE_COLD __attribute__((cold))
#else
#define PERFORMANCE_SENSITIVE
#define PERFORMANCE_COLD
#endif

// restrict 指针（C++20 起支持，GCC/Clang 扩展）
#if defined(__GNUC__) || defined(__clang__)
#define RESTRICT __restrict__
#else
#define RESTRICT
#endif

// 控制编译器优化行为（仅 GCC/Clang 支持）
#ifdef __GNUC__
#define GCC_OPTIMIZE(level) _Pragma(#level)
#else
#define GCC_OPTIMIZE(level)
#endif

#endif // PERF_TUNNING_UTILITY_H
