
1. **Private includes（私有包含）**：
   - **含义：** 限制了头文件的可见性，只在当前源文件中可见。
   - **示例：**
     ```c
     // 文件: example.c
     #include "private_header.h"
     ```

2. **Private typedef（私有类型定义）**：
   - **含义：** 在当前作用域中定义的类型，仅在当前源文件或模块中可见。
   - **示例：**
     ```c
     // 文件: private_header.h
     typedef struct {
         int privateData;
     } PrivateStruct;
     ```

3. **Private define（私有宏定义）**：
   - **含义：** 在当前源文件或模块中定义的宏，仅在当前源文件或模块中可见。
   - **示例：**
     ```c
     // 文件: private_header.h
     #define PRIVATE_CONSTANT 42
     ```

4. **Private macro（私有宏）**：
   - **含义：** 在当前源文件或模块中定义的宏，只在当前源文件或模块中可见。
   - **示例：**
     ```c
     // 文件: example.c
     #define PRIVATE_MAX(a, b) ((a) > (b) ? (a) : (b))
     ```

5. **Private variables（私有变量）**：
   - **含义：** 在当前源文件或模块中定义的变量，仅在当前源文件或模块中可见。
   - **示例：**
     ```c
     // 文件: private_module.c
     static int privateCounter = 0;
     ```

6. **Private function prototypes（私有函数原型）**：
   - **含义：** 在当前源文件或模块中声明的函数原型，仅在当前源文件或模块中可见。
   - **示例：**
     ```c
     // 文件: private_module.c
     static void privateFunction(void);
     ```

7. **Private user code（私有用户代码）**：
   - **含义：** 一般指用户在源文件中添加的私有实现代码，与其他模块或文件无关。
   - **示例：**
     ```c
     // 文件: user_code.c
     int main() {
         // 用户自定义的私有代码
         return 0;
     }
     ```

这些 "Private" 声明和定义帮助确保了代码的模块化和封装，防止在其他文件或模块中访问和修改私有实现的细节。
```c
/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "interrupt.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_TIM3_Init();
    /* USER CODE BEGIN 2 */


    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */

```

Private includes

Private typedef 

Private define 


Private macro 

Private variables 

Private function prototypes 

Private user code 