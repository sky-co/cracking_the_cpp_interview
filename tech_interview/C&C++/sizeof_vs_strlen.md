
# sizeof vs. strlen

sizeof和strlen的比较在C++笔试中是很普遍的，平时开发过程中也比较常见，所以熟悉二者的一般区别还是很有必要的。

```c++
#include <stdio.h>
#include <string.h>

int main()
{
    // Sample 1
    char buf1[] = "Hello world!"; // buf length is: 13, the last character is '\0'
    printf("sizeof(buf1) is:%ld\n", sizeof(buf)); // sizeof(buf): 13
    printf("strlen(buf1) is:%ld\n", strlen(buf)); // strlen(buf): 12

    // Sample 2
    char buf2[20]="0123456789"; 
    printf("sizeof(buf2) is:%ld\n", sizeof(buf)); // sizeof(buf): 20
    printf("strlen(buf2) is:%ld\n", strlen(buf)); // strlen(buf): 10

    return 0;
}
``````

## sizeof

sizeof 是一个运算符(宏)，故而sizeof(buf)的结果在编译期就可以知道。参数可以是数组、指针、类型、对象、函数等。另外，它计算的是整个缓冲区的长度，包括字符串末尾的'\0'。返回值是一个size_t类型的值。

功能：获得保证能容纳实现所建立的最大对象的字节大小。具体而言，当传入如下不同类型的参数时，sizeof返回的值为：

- 数组——编译时分配的数组空间的大小，而非实际使用的大小；
- 指针——存储该指针所用的空间的大小（存储该指针的地址的长度，是长整型，应该是4）；
- 类型——该类型所占的空间的大小；
- 对象——对象的实际占用空间大小；
- 函数——函数的返回类型所占的空间大小。函数的返回类型不能是void。

注意：sizeof计算的是类型或者变量占内存的大小。

## strlen

strlen是C库提供的一个函数，用来计算以'\0'结果的字符串的长度，即它的参数类型只能是char*。当数组名作为参数传入时，实际上数组就退化成指针。strlen(buf)只有在运行期才知道结果。其计算的字符串长度不包括末尾的'\0'。strlen在头文件`string.h`中定义。返回值是一个size_t类型的值。

功能：返回字符串的长度。该函数实际完成的功能是从代表该字符串的第一个地址开始遍历，直到遇到结束符'\0'。返回的长度大小不包括'\0'。

注意：sizeof计算的是字符串的实际长度。

## 小结

1. sizeof是运算符，也是关键字，而strlen却是一个函数。
2. sizeof用来(编译期)计算字符串的总长度，包括'\0'，而strlen用来(运行期)计算不包含'\0'的字符串的长度，遇到'\0'就会被截断。
3. 两者的返回值是一个size_t类型的值。
4. sizeof指出整个数组的长度；而strlen返回的是存储在数组中的字符串的长度，而不是数组本身的长度。
