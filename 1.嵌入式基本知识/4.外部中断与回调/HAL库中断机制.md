<!--
 * @Author: Ashington ashington258@proton.me
 * @Date: 2024-08-03 09:21:12
 * @LastEditors: Ashington ashington258@proton.me
 * @LastEditTime: 2024-08-03 09:30:18
 * @FilePath: \Embedded_Systems_Note\1.嵌入式基本知识\4.外部中断与回调\HAL库中断机制.md
 * @Description: 请填写简介
 * 联系方式:921488837@qq.com
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
-->

# HAL中断机制

## 1 中断的一般化流程

在STM32H7系列微控制器中，使用串口（UART）空闲中断是一种有效的方法来检测数据接收完成情况。以下是实现这一功能的典型流程：

### 1.1 配置步骤

1. **初始化UART**
   - 配置UART的波特率、数据位、停止位、校验位等参数。
   - 使能UART的接收中断。

2. **使能空闲中断**
   - 在UART初始化完成后，启用空闲中断（IDLE interrupt）。



#### 1.1.1 初始化UART

```c
UART_HandleTypeDef huart;

void UART_Init(void)
{
    huart.Instance = USARTx;  // 替换为你的具体USART实例，例如 USART1
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        // 初始化错误处理
    }

    // 使能接收空闲中断
    __HAL_UART_ENABLE_IT(&huart, UART_IT_IDLE);
    // 使能接收中断
    __HAL_UART_ENABLE_IT(&huart, UART_IT_RXNE);
}
```

#### 1.1.2 配置NVIC

配置中断向量控制器以响应UART中断。

```c
void NVIC_Config(void)
{
    HAL_NVIC_SetPriority(USARTx_IRQn, 0, 1);  // 设置优先级
    HAL_NVIC_EnableIRQ(USARTx_IRQn);          // 使能中断
}
```

#### 1.1.3 中断处理函数

在中断服务例程（ISR）中处理接收到的数据并清除空闲中断标志。

```c
void USARTx_IRQHandler(void)
{
    uint32_t isrflags = __HAL_UART_GET_FLAG(&huart, UART_FLAG_IDLE);

    if (isrflags != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart);  // 清除空闲中断标志
        HAL_UART_IdleCpltCallback(&huart);  // 调用空闲中断完成回调函数
    }

    HAL_UART_IRQHandler(&huart);  // 处理其他UART中断
}
```

#### 1.1.4 空闲中断回调函数

实现空闲中断回调函数，处理接收到的数据。

```c
void HAL_UART_IdleCpltCallback(UART_HandleTypeDef *huart)
{
    // 在此处理接收完成的数据
    // 例如：读取接收缓冲区数据
}
```

### 完整流程

以下是一个包含完整步骤的示例代码：

```c
UART_HandleTypeDef huart;

void UART_Init(void)
{
    huart.Instance = USARTx;  // 替换为你的具体USART实例，例如 USART1
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        // 初始化错误处理
    }

    // 使能接收空闲中断
    __HAL_UART_ENABLE_IT(&huart, UART_IT_IDLE);
    // 使能接收中断
    __HAL_UART_ENABLE_IT(&huart, UART_IT_RXNE);
}

void NVIC_Config(void)
{
    HAL_NVIC_SetPriority(USARTx_IRQn, 0, 1);  // 设置优先级
    HAL_NVIC_EnableIRQ(USARTx_IRQn);          // 使能中断
}

void USARTx_IRQHandler(void)
{
    uint32_t isrflags = __HAL_UART_GET_FLAG(&huart, UART_FLAG_IDLE);

    if (isrflags != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart);  // 清除空闲中断标志
        HAL_UART_IdleCpltCallback(&huart);  // 调用空闲中断完成回调函数
    }

    HAL_UART_IRQHandler(&huart);  // 处理其他UART中断
}

void HAL_UART_IdleCpltCallback(UART_HandleTypeDef *huart)
{
    // 在此处理接收完成的数据
    // 例如：读取接收缓冲区数据
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    UART_Init();
    NVIC_Config();

    while (1)
    {
        // 主循环
    }
}
```


## 2 HAL库中的中断处理机制

**为什么有的时候并未在ISR中调用回调函数，但是回调函数仍然会被触发？**

在STM32H7系列微控制器中，如果回调函数在未在ISR（中断服务例程）中显式调用的情况下仍然被触发，可能的原因有以下几点：

### 2.1 HAL库中的中断处理机制
STM32的HAL库在处理UART中断时，通常会在`HAL_UART_IRQHandler`函数中根据具体的中断标志位调用相应的回调函数。因此，即使在ISR中没有显式调用回调函数，HAL库内部也可能会根据中断标志位来触发相应的回调函数。

```c
void USARTx_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart);  // 处理所有UART相关的中断
}
```

在`HAL_UART_IRQHandler`函数中，会检查各种中断标志位（例如RXNE、TC、IDLE等），并调用相应的回调函数，例如：

- `HAL_UART_RxCpltCallback`：接收完成回调
- `HAL_UART_TxCpltCallback`：发送完成回调
- `HAL_UART_IdleCpltCallback`：空闲中断回调


### 示例分析
假设在您的代码中，您没有在ISR中显式调用空闲中断回调函数，但回调函数仍然被触发：

```c
void USARTx_IRQHandler(void)
{
    // 假设没有显式调用回调函数
    HAL_UART_IRQHandler(&huart);  // HAL库内部处理中断并可能调用回调函数
}
```

在`HAL_UART_IRQHandler`内部，可能会有类似如下的处理逻辑：

```c
void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    uint32_t isrflags = READ_REG(huart->Instance->ISR);
    uint32_t cr1its = READ_REG(huart->Instance->CR1);
    
    // 检查空闲中断标志
    if (((isrflags & USART_ISR_IDLE) != RESET) && ((cr1its & USART_CR1_IDLEIE) != RESET))
    {
        __HAL_UART_CLEAR_IDLEFLAG(huart);  // 清除空闲中断标志
        HAL_UART_IdleCpltCallback(huart);  // 调用空闲中断回调函数
    }
    
    // 处理其他中断...
}
```

在这种情况下，即使在ISR中未显式调用回调函数，`HAL_UART_IRQHandler`函数内部仍会根据中断标志位和配置触发相应的回调函数。

### 解决方案
确保在ISR中正确处理并清除中断标志位，以避免不必要的中断回调触发。此外，仔细检查HAL库的中断处理逻辑，了解库函数如何处理和触发回调函数。

例如，在空闲中断处理中显式调用回调函数并清除标志位：

```c
void USARTx_IRQHandler(void)
{
    uint32_t isrflags = __HAL_UART_GET_FLAG(&huart, UART_FLAG_IDLE);

    if (isrflags != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart);  // 清除空闲中断标志
        HAL_UART_IdleCpltCallback(&huart);  // 调用空闲中断完成回调函数
    }

    HAL_UART_IRQHandler(&huart);  // 处理其他UART中断
}
```
