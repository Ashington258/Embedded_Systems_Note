<!--
 * @Author: Ashington ashington258@proton.me
 * @Date: 2024-08-02 16:57:00
 * @LastEditors: Ashington ashington258@proton.me
 * @LastEditTime: 2024-08-02 19:34:53
 * @FilePath: \Embedded_Systems_Note\1.嵌入式基本知识\6.堆栈空间\FreeRTOS_堆栈.md
 * @Description: 请填写简介
 * 联系方式:921488837@qq.com
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
-->
FreeRTOS 是一个轻量级的实时操作系统（RTOS），它管理任务调度、堆栈分配、内存管理等。下面是关于 FreeRTOS 堆栈分配的详细解释：

### 任务堆栈分配

每个 FreeRTOS 任务都有自己的堆栈，独立于其他任务。这些堆栈存储任务的局部变量、函数调用链、任务上下文（寄存器值等）。

#### 1. 静态分配

在任务创建时，堆栈可以静态分配。在静态分配模式下，堆栈内存由用户提供，任务不会动态分配堆栈内存。

```c
#define STACK_SIZE 100
static StackType_t xStack[STACK_SIZE];
static StaticTask_t xTaskBuffer;

TaskHandle_t xHandle = xTaskCreateStatic(
                    vTaskCode,       /* Function that implements the task. */
                    "Task",          /* Text name for the task. */
                    STACK_SIZE,      /* Stack size in words, not bytes. */
                    NULL,            /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    xStack,          /* Array to use as the task's stack. */
                    &xTaskBuffer );  /* Variable to hold the task's data structure. */
```

#### 2. 动态分配

FreeRTOS 提供动态分配函数 `xTaskCreate`，它从 FreeRTOS 的内存堆中为任务分配堆栈内存。

```c
TaskHandle_t xHandle = NULL;

xTaskCreate(
    vTaskCode,       /* Function that implements the task. */
    "Task",          /* Text name for the task. */
    STACK_SIZE,      /* Stack size in words, not bytes. */
    NULL,            /* Parameter passed into the task. */
    tskIDLE_PRIORITY,/* Priority at which the task is created. */
    &xHandle );      /* Variable to hold the task's data structure. */
```

### 内存管理方案

FreeRTOS 支持五种不同的内存管理方案，通过配置文件 `FreeRTOSConfig.h` 中的 `configSUPPORT_DYNAMIC_ALLOCATION` 和 `configSUPPORT_STATIC_ALLOCATION` 宏来选择。

#### 1. heap_1.c

最简单的内存分配策略，不支持内存释放。只适用于分配后不需要释放的场景。

#### 2. heap_2.c

支持内存分配和释放，但不支持内存碎片整理。

#### 3. heap_3.c

将 FreeRTOS 内存管理重定向到标准 C 库的 `malloc` 和 `free` 函数。

#### 4. heap_4.c

支持内存分配和释放，并且包含了简单的内存碎片整理机制。

#### 5. heap_5.c

扩展了 heap_4 的功能，支持多个不连续的内存区域，适用于复杂的嵌入式系统。

### 配置示例

在 `FreeRTOSConfig.h` 中配置内存管理方案：

```c
#define configSUPPORT_DYNAMIC_ALLOCATION    1
#define configSUPPORT_STATIC_ALLOCATION     1
#define configTOTAL_HEAP_SIZE               ( ( size_t ) ( 16 * 1024 ) ) // 16KB
```

### 任务堆栈大小

任务堆栈大小可以在创建任务时指定，需要考虑任务中所需的局部变量、函数调用深度等。若堆栈分配不够，可能会导致栈溢出，进而引发不可预知的行为。

### 堆栈溢出检测

FreeRTOS 提供堆栈溢出检测功能，可以在配置文件中启用：

```c
#define configCHECK_FOR_STACK_OVERFLOW  2
```

然后实现堆栈溢出钩子函数：

```c
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    // 处理堆栈溢出
}
```

### 小结

FreeRTOS
