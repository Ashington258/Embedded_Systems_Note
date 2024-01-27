解决了不使用MicroLib的方式
>https://www.cnblogs.com/milton/p/14711577.html

>https://blog.csdn.net/qq_45772333/article/details/113530716


## 1  引入printf重定向代码块


经博主反复尝试和测试，这段代码最适合加在CubeMX自动生成后的usart.c文件的 / * USER CODE BEGIN 0 * / 和 / * USER CODE END 0 * / 中间
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
