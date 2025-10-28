# 编译单元 vs 翻译单元

## 背景
在一些参考资料上看到编译单元(compilation unit)和翻译单元(translation unit)。很多工程师（包括我自己）也会疑惑：这两个术语是什么意思？两者又有什么联系呢？

在 **C++** 中，**编译单元**和**翻译单元**是两个密切相关但又有所不同的概念。
![black_box](pic/black_box.png)

## 编译单元
**编译单元**是指在编译过程中被单独编译的最小代码单元。通常情况下，一个编译单元对应一个源代码文件（.cpp），它包含了完整的代码，包括所有的头文件和实现代码。简单来说一个 cpp 文件就是一个编译单元。
实际上每个编译单元在编译时都是相互独立的，即每个 cpp 文件之间是不知道对方的存在的。
编译器会分别将每个编译单元进行编译，生成相应的 obj 文件（目标文件），然后链接器会将所有的 obj 文件进行链接，生成最终可执行文件内部链接与外部链接。
只有添加进工程的cpp文件才能作为单独编译单元，其他外部文件夹的 cpp 文件不能单独成为编译单元。

C 标准中根本没有使用 “编译单元” 一词，它只出现在 C 和 C++ 之间突破性变化的理由中的几个地方，在那里其含义与 “翻译单元” 相同。也就是说，翻译单元是编译单元的子集，对于 C++ 而言，二者没有本质的区别。

## 翻译单元

**翻译单元** 则是编译单元的一个更具体的表现，通常指的是源文件文件加上所有包含的头文件，以及对预处理指令的宏展开。在编译过程中，翻译单元是指编译器在解析和生成目标代码时所使用的完整代码上下文。


下面是来自 C++ 标准的定义：
> A translation unit is the basic unit of compilation in C++. It consists of the contents of a single source file, plus the contents of any header files directly or indirectly included by it, minus those lines that were ignored using conditional preprocessing statements.
A single translation unit can be compiled into an object file, library, or executable program.
The notion of a translation unit is most often mentioned in the contexts of the One Definition Rule, and templates.

翻译过来就是：
> 翻译单元是 C++ 中编译的基本单位。它包括单个源文件的内容，加上它直接或间接包含的所有头文件的内容，再减去那些使用条件预处理语句忽略的行。
翻译单元可以被编译成目标文件、库或可执行程序。
翻译单元的概念最常在 `One Definition Rule` 和模板的上下文中被提及。

最后所有的目标文件都会被linker链接起来成为二进制文件(比如 `dll`, `exe` file)。

**注意**
在任何一个翻译单元之中，声明可以有多次，但是定义只能有一次；否则就违反了ODR。這也是在处理mutiple inclusion時需要特別注意的地方。

## 异同点
![translation_compilation_unit](pic/translation_compilation_unit.png)

## 代码示例

```cpp
// header.h
#ifndef HEADER_H
#define HEADER_H

void foo();

#endif

// main.cpp
#include <iostream>
#include "header.h"

void foo() {
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    foo();
    return 0;
}
```

在这个示例中：

- **编译单元**是`main.cpp`，它会被单独编译成目标文件。
- **翻译单元**是`main.cpp`与`header.h`结合后的完整代码，包含了 `foo` 的实现和 `#include` 指令展开后的结果。

---

## 补充

补充一下程序和链接的几个小概念：
**对象文件**，即我们常说的 obj 文件，在通常情况下，是编译单元被编译的结果。

**可执行文件**（Windows 下的EXE， Linux下的可执行二进制文件）是将一个项目的对象文件与运行时库函数连接在一起的结果。

在编译过程中究竟产生了哪些文件取决于编译器，但大多数现代编译器会简单地读取源文件和头文件，然后产生对象文件，如果你只有一个源文件，则直接传递给链接器。随后就产生了可执行文件。
而另一些编译器会把“预处理”作为一个单独的步骤，所以你最终会把所有的编译单元放在一个临时文件中。同样，在过去，在目标文件中不是生成机器代码，而是由编译器输出汇编代码，然后通过汇编器进行汇编，这将产生目标文件。链接的过程类似。

更多关于 GCC 编译的文章可以参考：
- [浅析 GCC 编译流程](tech_interview/C_Cpp/introduction_to_compile_process.md)
- [浅析 GCC 编译器优化](tech_interview/C_Cpp/introduction_to_gcc.md)
- [Linux环境下可执行文件分析工具介绍](tech_interview/C_Cpp/introduction_utility_to_exe.md)

![compiler_best_practice](pic/compiler_best_practice.png)

## 参考资料
- [wiki - Translation unit](https://en.wikipedia.org/wiki/Translation_unit_(programming))
- [Phases of translation](https://zh.cppreference.com/w/cpp/language/translation_phases.html)
- [Translation unit vs Compilation unit vs object file vs ...](https://stackoverflow.com/questions/34479600/translation-unit-vs-compilation-unit-vs-object-file-vs-executable-vs-in-c)
- [Compilation Unit](https://www.techopedia.com/definition/23963/compilation-unit-programming)
- [What is a "translation unit" in C++?](https://stackoverflow.com/questions/1106149/what-is-a-translation-unit-in-c)
