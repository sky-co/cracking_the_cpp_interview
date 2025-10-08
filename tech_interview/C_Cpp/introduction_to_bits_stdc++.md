# 万能头文件 bits/stdc++.h
![keys](pic/keys.jpg)

`bits/stdc++.h` 是一个在 C++ 编程中常用的头文件，主要用于简化代码的编写。它包含了几乎所有的标准库头文件，方便程序员在编写代码时不必逐一包含每个头文件。
该头文件的所在源码仓库 https://gist.github.com/Einstrasse/ac0fe7d7450621a39364ed3b05cacd11

## 用法
在 C++ 程序中，使用 `bits/stdc++.h` 的方式非常简单。只需在程序的开头添加以下一行代码：

```cpp
#include <bits/stdc++.h>
```

这行代码会自动包含 C++ 标准库中的所有头文件，如 `iostream`、`vector`、`algorithm`、`map` 等。这使得程序员可以直接使用这些库中的功能，而无需单独引入每个头文件。
代码示例如下：
```cpp
#include <bits/stdc++.h> // 包含各种标准 C++ 库

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<int> myVector = {1, 2, 3};
    std::sort(myVector.begin(), myVector.end());
    return 0;
}
```

### 优点
1. **简化代码**：使用 `bits/stdc++.h` 可以减少代码的冗长，使得程序更加简洁易读。
2. **提高开发效率**：在编写竞赛或快速原型时，程序员可以快速使用各种标准库功能，而不必担心遗漏某个头文件。
3. **便于学习**：对于初学者来说，使用这个头文件可以更快地上手 C++ 的标准库，专注于算法和逻辑的实现。
4. **快速原型开发**：在快速开发和测试算法时，能够迅速使用各种标准库功能。

### 缺点
1. **非标准**：它是 GCC 特有的扩展，并不是 C++ 标准的一部分。这意味着使用它的代码可能无法在其他编译器（如 Clang 或 MSVC）上编译。
2. **增加编译时间**：包含大量可能不必要的头文件可能会增加编译时间和可执行文件的大小。
3. **可移植性降低**：依赖于 bits/stdc++.h 的代码在不同编译器和平台之间的可移植性较差。
4. **在专业开发中的不良实践**：在专业软件开发中，使用非标准头文件和包含超过必要的头文件被视为不良实践，因为这可能导致更大的二进制文件、更慢的编译速度和依赖问题。

## 总结
`bits/stdc++.h` 是一个方便的工具，适合在快速开发和竞赛编程中使用。然而，在实际的生产环境中，建议根据需要选择性地包含头文件，以提高代码的可读性和编译效率。对于初学者来说，了解这个头文件的使用可以帮助他们更快地掌握 C++ 的标准库，但在深入学习后，逐步过渡到更规范的做法是非常重要的。

## 头文件内容
其头文件的所在源码仓库 https://gist.github.com/Einstrasse/ac0fe7d7450621a39364ed3b05cacd11
```cpp
// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2015 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

// 17.4.1.2 Headers

// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
```
![compiler_best_practice](pic/compiler_best_practice.png)

## 拓展阅读
- [C++ 标准库](https://book.douban.com/subject/26419721/)
- [Effective STL](https://book.douban.com/subject/1243751/)
