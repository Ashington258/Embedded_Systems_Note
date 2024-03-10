

// 定义相关变量
uint8_t aRxBuffer;               // 接收中断缓冲
uint8_t Uart1_RxBuff[256] = {0}; // 接收缓冲
uint8_t Uart1_Rx_Cnt = 0;        // 接收缓冲计数
uint8_t Uart1_RxFlag = 0;
uint8_t cAlmStr[] = "数据溢出(大于256)\r\n";

// 在usart.h 中编写回调函数

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
    /* NOTE: This function Should not be modified, when the callback is needed,the HAL_UART_TxCpltCallback could be implemented in the user file
     */

    if (Uart1_Rx_Cnt >= 255) // 溢出判断
    {
        Uart1_Rx_Cnt = 0;
        memset(Uart1_RxBuff, 0x00, sizeof(Uart1_RxBuff));
        HAL_UART_Transmit(&huart1, (uint8_t *)&cAlmStr, sizeof(cAlmStr), 0xFFFF);
    }
    else
    {
        Uart1_RxBuff[Uart1_Rx_Cnt++] = aRxBuffer; // 接收数据转存

        if ((Uart1_RxBuff[Uart1_Rx_Cnt - 1] == 0x0A) && (Uart1_RxBuff[Uart1_Rx_Cnt - 2] == 0x0D)) // 判断结束位
        {
            Uart1_RxFlag = 1;
        }
    }

    HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1); // 再开启接收中断
}
