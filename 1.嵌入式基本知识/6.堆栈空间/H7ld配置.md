<!--
 * @Author: Ashington ashington258@proton.me
 * @Date: 2024-08-02 16:49:57
 * @LastEditors: Ashington ashington258@proton.me
 * @LastEditTime: 2024-08-02 16:50:04
 * @FilePath: \Embedded_Systems_Note\1.嵌入式基本知识\6.堆栈空间\H7ld配置.md
 * @Description: 请填写简介
 * 联系方式:921488837@qq.com
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
-->
在你提供的内存配置中，这些区的分布如下：

- **DTCMRAM (Data Tightly Coupled Memory RAM)**: ORIGIN = 0x20000000, LENGTH = 128K
- **RAM_D1**: ORIGIN = 0x24000000, LENGTH = 512K
- **RAM_D2**: ORIGIN = 0x30000000, LENGTH = 288K
- **RAM_D3**: ORIGIN = 0x38000000, LENGTH = 64K
- **ITCMRAM (Instruction Tightly Coupled Memory RAM)**: ORIGIN = 0x00000000, LENGTH = 64K
- **FLASH**: ORIGIN = 0x08000000, LENGTH = 2048K

### 在RAM上的区域
1. **DTCMRAM**: 这是一个专门用于数据的高速RAM，通常用于需要快速访问的数据。
2. **RAM_D1**: 一般用于主存储器，适用于堆栈、全局变量等。
3. **RAM_D2**: 也是用于主存储器，可以用来存放中断向量表或其他全局数据。
4. **RAM_D3**: 较小的一块RAM，可以用于特殊需求的数据存储。
5. **ITCMRAM**: 主要用于存放指令，以提高指令访问速度，但也可以存放数据。

### 在FLASH上的区域
1. **FLASH**: 这是程序存储器，通常用于存放程序代码和常量数据。程序代码在上电后从FLASH加载到RAM中运行。

### 内存分配和生命周期
- **栈区 (Stack)**: 用于函数调用、局部变量分配等。生命周期在函数调用时创建，函数结束时销毁。
- **堆区 (Heap)**: 动态内存分配，由程序员使用`malloc`、`free`等函数管理。生命周期由程序员控制。
- **全局/静态存储区**: 包含全局变量、静态变量等。这些变量在程序启动时分配，在程序结束时销毁。
- **常量存储区**: 包含只读数据，如字符串常量。通常位于FLASH中。
- **代码区**: 存放程序指令，位于FLASH中。

### 关键字解释
- **变量**: 用于存储数据的命名存储空间。
- **数据类型**: 定义变量的类型，如`int`, `float`, `char`等。
- **程序**: 一系列指令，用于执行特定任务。
- **函数**: 具有特定功能的代码块，可以被调用执行。
- **static**: 修饰符，用于声明静态变量，生命周期贯穿程序始终。
- **volatile**: 修饰符，指示编译器不优化该变量，因为其值可能在任何时刻被改变。

