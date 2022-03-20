
# extern 关键字

extern关键字源于C语言，在C++中对其语义和功能赋予了更进一层的含义，具体如下：

## extern 修饰变量和函数

将extern置于变量/函数前是C语言的主要用法，如

```c++
extern int g_Int；
```

或

```c++
extern void foo();
```

这是用来说明“此全局变量/函数是在别处**定义**的，要在此处**引用**”,提示编译器在遇到此变量和函数时，要到其他模块中寻找其定义。**注意**，这是一个声明不是定义，即不分配存储空间。

在引用全局变量或函数之前，必须要有这个变量或者函数的声明（或者定义）。通常，在模块的头文件中对本模块提供给其它模块引用的全局变量或函数用关键字 `extern` 声明。
也就是说模块B(编译单元)要是引用了模块A(编译单元)中定义的全局变量或函数时，它只要包含模块A的头文件即可;在编译阶段，模块B不会因为找不到该函数或变量而报错，它会在链接时从模块A生成的目标代码中找到此变量或函数。

与 `extern` 对应的关键字是 `static` (详情请参阅·[static 关键字](./static_keyword.md))，被它修饰的全局变量和函数只能在本模块中使用。因此，一个函数或变量只可能被本模块使用时，其不可能被 extern "C" 修饰。

在一个文件中定义了变量和函数， 在其他文件中要使用它们， 可以有两种方式：
- 使用头文件，然后声明它们，然后其他文件去包含头文件
- 在其他文件中直接extern

## extern "C" 的作用

C++的项目中，经常会看到下面的代码:

```c++
#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif
```

这是告诉编译器在编译`fun`这个函数时候按着C的规矩去翻译，而不是C++的规则。这个行为与C++的重载有关，但C语言并不支持函数重载。C++为了支持重载，需要进行`name managling`，所以函数被C++编译器编译后在库中的名字与C语言的不同。

这样就会导致一个问题：如果C++中使用C语言实现的函数，在编译链接的时候，会出错，提示找不到对应的符号。此时extern "C"就起作用了：告诉链接器去寻找_add这类的C语言符号，而不是经过C++修饰的符号。从而实现了C与C++混合编程，即在C++程序中以C的规则去编译链接C部分的代码，并最终实现在C++程序中调用C的接口。但反过来，C中并不能直接调用C++库函数。

### extern "C" 用法1

如果需要编写一个C语言的模块，供以后使用。头文件中声明函数时需要用条件编译包含起来，代码如下：

```c++
#ifdef __cpluscplus
extern "C" {
#endif

/* some code */

#ifdef __cplusplus
}
#endif

```

### extern "C" 用法2

如果目标模块已经存在代码库中，并且模块的.h文件中没有extern "C"关键字，这个模块又不希望被改动的情况下，可以在C++文件中，在包含该模块的头文件时加上extern "C", 代码如下：

```c++
extern "C" {
#include "extern_c_header.h"
}
```

### extern "C" 用法3

如果只想使用模块中的某个函数，而不是include整个模块时，可以单独声明该函数，代码如下:

```c++
extern "C"{
void foo();
}
```

## 其它

### C++ demangle工具

有时候，c++/c程序在编译的时候不会报错，但是在运行的时候会报dlopen失败。此时多数是因为动态库的路径找不到。其实我们完全没有必要等到运行的时候才去发现此问题，我们可以通过ldd -r 命令（执行数据对象和函数的重定位，并且报告任何丢失的对象和函数）来找出undefined函数名，比如用ldd -r test.so查出缺少_ZNK4Json5ValueixEPKc。我们可以用[c++filt](http://sourceware.org/binutils/docs/binutils/c_002b_002bfilt.html)来还原函数名。

c++filt _ZNK4Json5ValueixEPKc
Json::Value::operator[](char const*) const

#### c++filt 参数

```c++
$ c++filt --help

Usage: c++filt [options] [mangled names]
Options are:
[-_|--strip-underscore] Ignore first leading underscore
[-n|--no-strip-underscore] Do not ignore a leading underscore (default)
[-p|--no-params] Do not display function arguments
[-i|--no-verbose] Do not show implementation details (if any)
[-t|--types] Also attempt to demangle type encodings
[-s|--format {none,auto,gnu,lucid,arm,hp,edg,gnu-v3,java,gnat,dlang}]
[@<file>] Read extra options from <file>
[-h|--help] Display this information
[-v|--version] Show the version information
```

每个编译器都有一套自己内部的名字，比如对于linux下g++而言。以下是基本的方法：

每个方法都是以_Z开头，对于嵌套的名字（比如名字空间中的名字或者是类中间的名字,比如Class::Func）后面紧跟N ， 然后是各个名字空间和类的名字，每个名字前是名字字符的长度，再以E结尾。(如果不是嵌套名字则不需要以E结尾)。

比如对于_Z3foov 就是函数foo() , v 表示参数类型为void。又如N:C:Func 经过修饰后就是 _ZN1N1C4FuncE，这个函数名后面跟参数类型。 如果跟一个整型，那就是_ZN1N1C4FuncEi。


#### 程序设计风格

- 不要把变量定义放入.h文件，这样容易导致重复定义错误。
- 尽量使用static关键字把变量定义限制于该源文件作用域，除非变量被设计成全局的。
- 也就是说，可以在头文件中声明一个变量，在用的时候包含这个头文件就声明了这个变量。

#### 资源

- https://github.com/Light-City/CPlusPlusThings/tree/master/basic_content/extern
- https://www.cnblogs.com/banmei-brandy/p/11338314.html
- https://www.cnblogs.com/skynet/archive/2010/07/10/1774964.html
- https://zhuanlan.zhihu.com/p/123269132
- https://www.jianshu.com/p/111dcd1c0201
- https://blog.csdn.net/kongshuai19900505/article/details/52972786
