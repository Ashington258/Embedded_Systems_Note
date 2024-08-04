# 中断服务函数机制

## 1 启动文件定义中断向量表

首先 HAL 库层会在启动文件中配置中断服务例程（ISR），启动文件中会定义一个中断向量表，通常是一个数组，其中每个元素对应一个中断服务例程（ISR）的地址。

```assembly

g_pfnVectors:
    .word  _estack          /* 初始栈指针 */
    .word  Reset_Handler    /* 复位处理函数 */
    .word  NMI_Handler      /* NMI 处理函数 */
    .word  HardFault_Handler /* 硬故障处理函数 */
    /* 其他中断处理函数 */
    .word  USART2_IRQHandler /* USART2 中断处理函数 */
    /* 继续定义其他中断 */

```

## 2 中断文件规定服务函数入口

```C
void USART2_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart2);

}
```

上面的启动文件规定中断向量表后，触发`USART2_IRQHandler(void)`**中断服务例程（ISR，Interrupt Service Routine）**，ISR 中再调用`HAL_UART_IRQHandler(&huart2);
`，他是一个中断服务函数，中断处理函数，主要负责中断触发逻辑业务，例如清空标志位，**触发何种回调函数等**。

