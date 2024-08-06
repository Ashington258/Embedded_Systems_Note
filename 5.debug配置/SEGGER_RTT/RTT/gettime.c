/*
 * @Author: Ashington ashington258@proton.me
 * @Date: 2024-08-06 13:17:58
 * @LastEditors: Ashington ashington258@proton.me
 * @LastEditTime: 2024-08-06 13:18:05
 * @FilePath: \Embedded_Systems_Note\5.debug配置\SEGGER_RTT\RTT\gettime.c
 * @Description: 请填写简介
 * 联系方式:921488837@qq.com
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */

// 该文件可以放获取时间的函数，用户LOG.h的调用，输出时间戳，以下是一个HAL库的示例
__weak uint32_t HAL_GetUs()
{
    uint32_t tms = SysTick->LOAD + 1;
    return (tms - SysTick->VAL) * 1000 / tms;
}