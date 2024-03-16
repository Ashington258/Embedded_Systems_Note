'''
Author: 小叶同学
Date: 2024-03-16 20:52:11
LastEditors: Please set LastEditors
LastEditTime: 2024-03-16 20:57:20
Description: 请填写简介
'''
import serial

def receive_motor_speed(port='/dev/ttyUSB0', baudrate=9600):
    """这个函数用于接收电机的转速，直到程序的终止

    Args:
        port (str, optional): 串口设备路径，默认为 '/dev/ttyUSB0'.
        baudrate (int, optional): 波特率，默认为 9600.
    """
    # 打开串口
    ser = serial.Serial(port, baudrate)
    
    try:
        while True:
            # 读取串口数据
            data = ser.readline().decode().strip()
            
            # 打印接收到的数据
            print("Received:", data)

    except KeyboardInterrupt:
        # 当按下 Ctrl+C 时关闭串口
        ser.close()



# 调用函数开始接收舵机速度数据
receive_motor_speed()
