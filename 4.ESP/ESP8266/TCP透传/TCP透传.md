<!--
 * @Author: Ashington ashington258@proton.me
 * @Date: 2024-07-02 20:44:06
 * @LastEditors: Ashington ashington258@proton.me
 * @LastEditTime: 2024-07-02 20:55:11
 * @FilePath: \Embedded_Systems_Note\4.ESP\ESP8266\TCP透传\TCP透传.md
 * @Description: 请填写简介
 * 联系方式:921488837@qq.com
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
-->

AT+CWMODE=1

AT+CWJAP="Anime","password"

AT+CIPMUX=0

AT+CIPMODE=1

AT+CIPSTART="TCP","192.168.2.122",8080

AT+CIPSEND