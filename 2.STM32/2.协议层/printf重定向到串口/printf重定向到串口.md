解决了不使用MicroLib的方式
>https://www.cnblogs.com/milton/p/14711577.html

>https://blog.csdn.net/qq_45772333/article/details/113530716

>https://www.cnblogs.com/Lxk0825/p/15358822.html#:~:text=STM32%20CUBEIDE%20%E4%B8%B2%E5%8F%A3%E7%9A%84%E4%BD%BF%E7%94%A8%E4%B8%8Eprintf%E9%87%8D%E5%AE%9A%E5%90%91,1.%E9%85%8D%E7%BD%AEIOC%E6%96%87%E4%BB%B6%20%E4%BF%9D%E5%AD%98%E5%90%8E%E7%94%9F%E6%88%90%E4%BB%A3%E7%A0%81%EF%BC%8C%E6%B2%A1%E6%9C%89%E4%BD%BF%E7%94%A8DMA%E6%A8%A1%E5%BC%8F%202.%E5%9C%A8main.c%E6%88%96%E8%80%85.h%E4%B8%AD%E6%B7%BB%E5%8A%A0%E4%BB%A5%E4%B8%8B%E4%BB%A3%E7%A0%81%E8%BF%9B%E8%A1%8C%E9%87%8D%E5%AE%9A%E5%90%91

## 1  引入printf重定向代码块


经博主反复尝试和测试，这段代码最适合加在CubeMX自动生成后的usart.c文件的 / * USER CODE BEGIN 0 * / 和 / * USER CODE END 0 * / 中间

### **CUBEIDE**

```C
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

```

### **KEIL**

```c
/* USER CODE BEGIN 0 */
#include <stdio.h>

 #ifdef __GNUC__
     #define PUTCHAR_PROTOTYPE int _io_putchar(int ch)
 #else
     #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
 #endif /* __GNUC__*/
 
 /******************************************************************
     *@brief  Retargets the C library printf  function to the USART.
     *@param  None
     *@retval None
 ******************************************************************/
 PUTCHAR_PROTOTYPE
 {
     HAL_UART_Transmit(&huart1, (uint8_t *)&ch,1,0xFFFF);
     return ch;
 }
/* USER CODE END 0 */

```


## 2 添加#include<stdio.h>

比较全局的办法就是将#include<stdio.h>直接加入main.h中，因为Cube生成文件大部分都是包含了main.h的，所以除了自建文件几乎都可以全局包含到stdio.h，而且自建文件也可以直接包含main.h，我的习惯是把工程用的共性的概率高的头文件都放在main.h里面，具体位置如下：

```c
//main.h

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<stdio.h>
/* USER CODE END Includes */

```
