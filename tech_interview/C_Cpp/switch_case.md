# swtich case 中不能定义变量

switch 语句提供了一条便利的途径，使得程序的执行会在若干 case 标签选项中做出选择。其执行流程大致如下：
- switch 语句首先对括号里的表达式求值，该表达式紧跟在 switch 之后（表达式可以是一个初始化的变量声明）。表达式的值转换成整数类型，然后与每个 case 标签的值比较。
- 如果表达式和某个 case 标签的值匹配成功，该 case 标签之前的部分会被忽略掉，程序将会从该标签之后的第一条语句开始执行，直到到达 switch 的结尾或是遇到 break 语句为止。
- 如果与其他 case 标签都无法匹配成功，程序将会进入 default 标签定义的代码块执行。

## 问题

《C++ Primer 5th》 描述过这么一个场景：
> switch 的执行流程可能会跨过某些 case 标签。如果程序跳转到了某个特定的 case，则 switch 结构中该 case 标签之前的部分会被忽略掉。这种忽略掉一部分代码的行为引出了一个有趣的问题：如果被略过的代码中含有变量的定义该怎么办？
答案是：如果在某处一个带有初值的变量位于作用域之外，在另一处该变量位于作用域之内，则从前一处跳转到后一处的行为是非法行为。

```cpp
// switch.cpp

#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
  int val = 2;
  switch (val) {
  case 1:
    int x = 0;
    break;
  case 2:
    x = 2;
    break;
  default:
    break;
  }

  return 0;
}
```

结果报错：

```error
error: jump to case label
note: crosses initialization of ‘int x’
```

## 原因

switch 大括号内所有 case 同属一个“作用域”，并且 “变量初始化”语句是一个在程序运行时才会被调用的语句，是可以被 case 跳转屏蔽掉的语句。

而上述示例中程序的执行流程可能绕开 `case 1:` 中的变量（隐式或显式）初始化语句，与 `case 2` 匹配，所以该 switch 语句不合法。也就是说 switch 的 case 语句中不能定义变量，不然就会报错。

这条规则简单来说就是：在任何作用域内，假如存在变量（隐式或显式）初始化语句，该初始化语句不可以被跳过，一定要执行！
这里强调作用域内的变量一旦初始化就不能跳过，但是可以跳过整个作用域！

## 解决方案

1. 用 if else 代替 switch 语句。

2. 在 case 中用 {} 将代码括起来，这样在 {} 中就能定义变量了。变量的作用域位于 {} 内，出了作用域，变量自动销毁，即为上述的“跳过整个作用域”。

```cpp
// 变量声明置于 switch 和 case 之间
switch (val) {
 int x;
 case 1:
 {
   int x = 1;
   break;
 }
 case 2:
 {
   int x = 2;
   break;
 }
 default:
   break;
 }
```

3. 如果变量在每个 case 标签中都要用，那么应该把变量定义在 switch 外。

4. 将变量的声明移至 switch 和 case 之间，或将 case 之间的变量初始化改为变量定义 (不推荐)。原因在于：如果只是声明变量，该变量采用隐式初始化（内置类型编译器译器自动初始化为 0），那么可能存在未定义的行为。

```cpp
// 变量 x 的定义置于 switch 和 case 之间
switch (val) {
 int x;  // 是声明，也是定义，未初始化
 case 1:
   break;
 case 2:
   x = 2;
   break;
 default:
   break;
 }
```

```cpp
// case 之间的变量 x 定义
switch (val) {
 case 1:
   int x;
   break;
 case 2:
   x = 2;
   break;
 default:
   break;
 }
```

## 补充

关于声明、定义和初始化：
①声明变量不会分配内存空间。
②定义变量 `int x`，编译的时候会分配内存，但是并不会产生任何可执行的代码。以 `int x` 这句话只是在编译的时候有用，执行的时候跳过的时候也无所谓！
③初始化变量分配空间并初始化（编译时分配空间，运行时初始化赋值），假如存在，一定要执行！

## 参考资料

- https://blog.csdn.net/LvzJason/article/details/123445116
- https://blog.csdn.net/aaron1996123456/article/details/102832468
