# Linux环境下可执行文件分析工具介绍
![knife](pic/knife.jpg)
今天介绍一些常用的分析工具及如何用它们从不同层次分析生成的二进制文件。
还是同样的示例代码：
```cpp
#include <iostream>

int main() {
    std::cout << "Hello World!\n";
}
```
这里使用常见命令编译：`g++ -o hello hello.cpp`（默认生成 ELF 动态可执行文件，x86_64 或其他架构视平台而定）。

## file - 快速识别文件类型
- **用途**：根据魔数判断文件类型、架构、是否为动态可执行文件、是否剥离符号等。
- **典型场景**：初步确认文件类型、架构、是否为可执行文件或库文件。
- **命令示例**:
  ```sh
  file hello
  ```
- **输出示例**：
  ```sh
  hello: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=535dcdadf482ef71ee1af5b066d7b909a56a4630, for GNU/Linux 3.2.0, not stripped
  ```
- **补充说明**：可用于识别二进制文件、库文件、脚本等类型，快速判断平台兼容性。

## readelf - 检查 ELF 结构化元数据
- **用途**：查看 ELF 头、节表、程序头、动态段、符号表、入口点等细节。
- **典型场景**：分析 ELF 文件结构、依赖库、入口点、符号表等。
- **常用命令**:
  - ELF 头： `readelf -h hello`
  - 程序头（运行相关段）： `readelf -l hello`
  - 节表： `readelf -S hello`
  - 动态段（依赖库、SONAME 等）： `readelf -d hello`
  - 符号表： `readelf -s hello`
- **补充说明**：可用于定位 PT_INTERP（动态链接器）、NEEDED（依赖库）、.text/.data/.rodata 等段的偏移和大小。

## ldd - 列出运行时共享库依赖
- **用途**：显示可执行文件在运行时需要加载的共享库及解析路径。
- **典型场景**：快速检查程序依赖哪些动态库，排查库缺失问题。
- **命令示例**:
  ```sh
  ldd hello
  ```
- **输出示例**：
  ```sh
  linux-vdso.so.1 (0x00007ffe7b2f3000)
  libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x000078dd8c000000)
  libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x000078dd8bc00000)
  libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x000078dd8bf19000)
  /lib64/ld-linux-x86-64.so.2 (0x000078dd8c2b2000)
  libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x000078dd8c271000)
  ```
- **补充说明**：对不可信二进制直接运行 ldd 有安全风险；可用 `readelf -d` 替代手动解析 NEEDED 条目。

## nm - 查看符号表（定义/引用）
- **用途**：列出可执行文件中的符号（函数、全局变量），标明已定义或未定义。
- **典型场景**：分析函数和变量的符号、定位 main、查看未定义符号（外部依赖）。
- **命令示例**:
  ```sh
  nm -C hello
  ```
- **输出关注点**：
  - `T`/`t`：文本段已定义函数（如 main）。
  - `U`：未定义符号（如 std::cout、operator<<、__libc_start_main）。
- **补充说明**：`-C` 对 C++ 名称进行解码（demangle），便于识别 iostream 相关符号。可用于分析静态库、动态库和可执行文件。

## objdump - 反汇编与节/段视图
- **用途**：反汇编机器码、显示节内容与节头，结合调试信息可以显示源代码对应位置。
- **典型场景**：分析程序指令、节布局、定位字符串常量、调试入口流程。
- **常用命令**:
  - 反汇编： `objdump -d hello`
  - 带源/符号： `objdump -C -S hello`（需带调试信息）
  - 节头表： `objdump -h hello`
  - 显示 .rodata（字符串常量）： `objdump -s -j .rodata hello`
- **补充说明**：可用于分析启动流程、静态初始化、C++ 构造/析构顺序、定位常量字符串等。

## hexdump - 查看原始字节与嵌入字符串
- **用途**：以十六进制+ASCII 显示文件的原始字节，便于查看 ELF 魔数、内嵌字符串（如 "Hello World!\n"）及特定偏移内容。
- **典型场景**：定位文件头、查找嵌入字符串、分析二进制结构。
- **命令示例**:
  ```sh
  hexdump -C hello | less
  hexdump -n 128 -s 0 hello
  ```
- **补充说明**：结合 `readelf -S` 或 `objdump -s -j .rodata` 可定位字符串在文件中的偏移和内容。

## ldconfig - 管理共享库缓存（系统层面）
- **用途**：维护动态链接器的缓存 (/etc/ld.so.cache)，用于查找共享库路径。
- **典型场景**：系统层面管理库路径、解决库查找失败问题。
- **常用操作**:
  - 刷新缓存（需 root）： `sudo ldconfig`
  - 打印缓存： `ldconfig -p`
- **补充说明**：当 `ldd/readelf` 显示库未找到时，可通过配置 `/etc/ld.so.conf.d/` 并运行 `sudo ldconfig` 使系统识别新库位置。

## strings - 提取可打印字符串
- **用途**：从二进制文件中提取所有可打印字符串，快速定位硬编码文本、调试信息等。
- **典型场景**：查找程序中嵌入的文本、调试符号、版权信息等。
- **命令示例**:
  ```sh
  strings hello
  ```
- **补充说明**：可用于安全分析、逆向工程、快速定位关键字。

## strip - 去除符号表和调试信息
- **用途**：移除可执行文件中的符号表和调试信息，减小体积、提升安全性。
- **典型场景**：发布版本去除调试信息，防止泄露源码结构。
- **命令示例**:
  ```sh
  strip hello
  ```
- **补充说明**：去除符号后无法用 gdb 调试源码，但可减少文件体积。

## gdb - 交互式调试器
- **用途**：调试可执行文件，单步执行、设置断点、查看变量和调用栈。
- **典型场景**：定位程序崩溃、分析运行时行为、调试复杂逻辑。
- **命令示例**:
  ```sh
  gdb hello
  ```
- **补充说明**：需编译时加 `-g` 选项生成调试信息。

---

## 推荐分析流程
![ladder](pic/ladder.jpeg)

下面的是针对二进制可执行文件`hello`的推荐分析流程
1. 首先使用 `file hello` 来确认类型与架构。
2. 接着使用 `readelf -h -l -S -d hello` 来检查 ELF 头、程序头、节表与动态依赖（PT_INTERP、NEEDED）。
3. 然后使用 `ldd hello` 快速查看运行时库（或用 readelf -d 替代以免风险）。
4. 然后再使用 `nm -C hello` 来查看 main 与未定义的库符号（iostream/stdio）。
5. 接着可以使用 `objdump -d hello` 反汇编观察入口、对 libc/libstdc++ 的调用与启动序列。
6. 使用 `objdump -s -j .rodata hello` 或 `hexdump -C hello` 来定位并查看 "Hello World!\n" 字符串字节。
7. 用 `strings hello` 快速查找所有嵌入文本。
8. 若需发布，使用 `strip hello` 去除符号表和调试信息。
9. 若需调试，使用 `gdb hello` 进行交互式调试。


以上工具从文件识别、ELF 元数据、依赖关系、符号信息、机器码到原始字节，提供了对 hello 可执行文件的全面分析手段。

---

## 总结
Linux 下分析可执行文件内容，推荐结合 `file`、`readelf`、`ldd`、`nm`、`objdump`、`hexdump`、`strings`、`strip`、`gdb` 等工具，从文件类型、结构、依赖、符号、汇编、原始字节到调试和发布全流程进行系统性分析。掌握这些工具不仅有助于理解程序底层实现，也能提升排查问题和性能调优的能力。

---

## 拓展阅读
![tuning_light](../Performance_Tuning/Run_Time/pic/tuning_light.png)
- [《深入理解计算机系统》（CSAPP）](https://book.douban.com/subject/26912767)
- [《程序员的自我修养》](https://book.douban.com/subject/3652388)
- [《Linux/UNIX 系统编程手册》](https://book.douban.com/subject/25809330)
- [《Programming from the Ground Up》](https://book.douban.com/subject/1787855/)
- [objdump 官方文档](https://sourceware.org/binutils/docs/binutils/objdump.html)
- [readelf 官方文档](https://sourceware.org/binutils/docs/binutils/readelf.html)
- [Linux工具快速教程](https://linuxtools-rst.readthedocs.io/zh-cn/latest/index.html)
