# 编译单元 vs 翻译单元

## 背景

在一些参考资料上看到 Compilation Unit（编译单元）和 Translation Unit（翻译单元）。很多 工程师（包括我自己）也会疑惑：这两个术语是什么意思？两者又有什么联系呢？

### 翻译单元

下面是来自 C++ 标准的定义：
> A translation unit is the basic unit of compilation in C++. It consists of the contents of a single source file, plus the contents of any header files directly or indirectly included by it, minus those lines that were ignored using conditional preprocessing statements.
A single translation unit can be compiled into an object file, library, or executable program.
The notion of a translation unit is most often mentioned in the contexts of the One Definition Rule, and templates.

翻译过来就是：
> 翻译单元是 C++ 中编译的基本单位。它包括单个源文件的内容，加上它直接或间接包含的所有头文件的内容，再减去那些使用条件预处理语句忽略的行。
翻译单元可以被编译成目标文件、库或可执行程序。
翻译单元的概念最常在 `One Definition Rule` 和模板的上下文中被提及。

### 编译单元

那什么是编译单元呢？简单来说一个 cpp 文件就是一个编译单元。
实际上每个编译单元在编译时都是相互独立的，即每个 cpp 文件之间是不知道对方的存在的。
编译器会分别将每个编译单元进行编译，生成相应的 obj 文件（目标文件），然后链接器会将所有的 obj 文件进行链接，生成最终可执行文件内部链接与外部链接。
只有添加进工程的cpp文件才能作为单独编译单元，其他外部文件夹的 cpp 文件不能单独成为编译单元。

C 标准中根本没有使用 “编译单元” 一词，它只出现在 C 和 C++ 之间突破性变化的理由中的几个地方，在那里其含义与 “翻译单元” 相同。也就是说，翻译单元是编译单元的子集，对于 C++ 而言，二者没有本质的区别。

## 补充

补充一下程序和链接的几个小概念：
**对象文件**，即我们常说的 obj 文件，在通常情况下，是编译单元被编译的结果。

**可执行文件**（Windows
下的EXE， Linux下的可执行的二进制文件）是将一个项目的对象文件与运行时库函数连接在一起的结果。

在编译过程中究竟产生了哪些文件取决于编译器，但大多数现代编译器会简单地读取源文件和头文件，然后产生对象文件，如果你只有一个源文件，则直接传递给链接器。这就产生了可执行文件。

而另一些编译器会把“预处理”作为一个单独的步骤，所以你最终会把所有的编译单元放在一个临时文件中。同样，在过去，在目标文件中不是生成机器代码，而是由编译器输出汇编代码，然后通过汇编器进行汇编，这将产生目标文件。链接的过程类似。

## 参考资料

- https://blog.csdn.net/u011913417/article/details/100183653
- https://cplusplus.com/forum/general/103518/
- https://stackoverflow.com/questions/34479600/translation-unit-vs-compilation-unit-vs-object-file-vs-executable-vs-in-c
- https://www.techopedia.com/definition/23963/compilation-unit-programming
- http://web.archive.org/web/20090427201018/http://efnetcpp.org/wiki/Translation_unit
- https://stackoverflow.com/questions/1106149/what-is-a-translation-unit-in-c
- https://stackoverflow.com/questions/4992247/how-is-compilation-unit-defined-in-c
