# include 文件

## include介绍

`#include` 是一个来自 C 语言的宏命令，它在编译器进行编译之前，即在预编译阶段就会起作用。
`#include` 的作用是：在预编译阶段把它后面所写的那个文件的内容，完完整整地、一字不改地包含到当前的文件中。值得一提的是，它本身唯一的作用就是把每一个它出现的地方，在预编译阶段替换成它后面所包含的文件的内容，即简单的文本替换。

### include <文件名>

系统自带的头文件用尖括号（`<...>`）括起来，这样程序编译时，编译器将只按照系统指定的路径中查找该文件。
一般用于标准库\系统头文件。

```c++
#include <文件名>
```

### include "文件名"

源程序(项目)自定义的文件使用双引号（`"..."`），这样程序编译时，编译器首先在源程序所在的目录（当前目录）中查找被包含的文件；若找不到该文件，再按系统指定的路径查找该文件（先到 C++ 安装目录中查找，最后在系统文件中查找）。

```c++
#include "文件名"
```

## 拓展

### gcc 在哪查找 include 的头文件
- https://stackoverflow.com/questions/344317/where-does-gcc-look-for-c-and-c-header-files/72762087#72762087
- http://commandlinefanatic.com/cgi-bin/showarticle.cgi?article=art026

### include "xxx.cpp"

- `#include xxx.h` 文件理解为声明。
- `#include xxx.cpp` 文件理解为实现（代码复制拷贝）。

函数声明和实现的区别在于：声明只是一个符号链接，目的是告诉编译器该函数的定义（实现）在别的地方，即其他文件夹或lib中的 `xxx.cpp`里。 外部文件夹的 cpp 文件并不能生成单独的编译文件，所以不参与未解决符号表和导出符号表的生成，而 include 外部的头文件也只是拷贝头文件中的函数声明而已，并没有没有函数定义。

如果只 `#include xxx.h` （对应的 xxx.cpp 不在同一个文件夹或 lib 中）就会报错：“error LNK2019: 无法解析的外部符号”。但是单独 `#include xxx.cpp` 就能运行了，而此时 xxx.cpp 里面有没有对应的 xxx.h 头文件都可以正确运行（xxx.h 文件里有 `#pragma once` 防止多次定义）。

同样如果我们将 xxx.cpp 文件中的函数实现放入 xxx.h 头文件中，直接 include 该头文件也可以达到目的，但会有一个问题，假如项目中的其他多个文件中都 include 了该头文件，那么该函数定义就会重复出现多次，链接时编译器会报错 `multiple definition`。这时有两个常见做法：
[1] 将声明和实现分别放入头文件 `.h` 和 `.cpp` 中，声明和实现分离， link时指定外部编译单元目标对象的地址。
[2] 将该函数声明为 `inline`，这样仅会存在一个函数的定义，避免了重复定义。
（单一定义的规则：如果不同的编译单元看到不同的定义的话，那链接时使用哪个定义是不确定的，结果就可能会让人吃惊。）

### include "xxx.hpp"

现代C++项目中的头文件和源文件的差别已经不太大，这与最初声明和实现分离的想法可谓背道而驰。
从源码阅读的效率上来说，为了避免在头文件和源文件的声明和实现之间切换，便推出了新的文件类型`xxx.hpp`。可以理解为头文件和和源文件的统一。
但这可能会出现上述的重复定义的问题，至于项目中怎么取舍，最终还是由软件需求和架构来统一。

### 一些小技巧
####
- `g++ -H ...`
  以一种格式打印包含文件的完整路径，如果不想输出文件的话，可以使用 `g++ -H -fsyntax-only ...`，clang也是类似的，只要把 g++ 换成 clang++ 就可以了。
- `gcc  -M ...`
  这将给出依赖关系，并列出include文件的绝对路径。如果你不想要包含系统文件（即#include <something.h>），那么使用 `gcc  -MM ...`。


### 模块（module）
C++20 提出模块的概念，类似Java/Python导入包(lib)。详情请参见 第 xxx 章
在大的工程项目中还有很多冗余的include，种种原因，导致编译速度相当的慢，而modules却大大改善了这种问题。
modules使用方式和include差不多，但modules使用比include头文件速度更快，C++全球开发者大会中，C++之父贴出来过测试数据，modules效率比include高了25倍。

## 参考资料
- https://stackoverflow.com/questions/344317/where-does-gcc-look-for-c-and-c-header-files/72762087#72762087
- http://commandlinefanatic.com/cgi-bin/showarticle.cgi?article=art026
- https://mp.weixin.qq.com/s/NVEZnF1HqpIMSBlw_PXwyA
- https://blog.csdn.net/u011913417/article/details/100183653
