#include "key_detection.h"
#include <stdio.h>

// 初始化按键检测系统
void initKeyDetectionSystem(KeyDetectionSystem *system)
{
    for (int i = 0; i < MAX_KEYS; ++i)
    {
        system->keys[i].state = KEY_IDLE;
        system->keys[i].timestamp = 0;
        system->keys[i].isPressed = false;
        system->keys[i].isReleased = false;
        system->keys[i].isDoubleClicked = false;
    }
    // 进行其他初始化
}

// 更新按键检测系统状态的函数
void updateKeyDetectionSystem(KeyDetectionSystem *system, bool isKeyPressed)
{
    // 根据当前按键状态执行相应的逻辑
    for (int i = 0; i < MAX_KEYS; ++i)
    {
        switch (system->keys[i].state)
        {
        case KEY_IDLE:
            // 如果检测到按键被按下，则将按键状态切换为按下状态，并记录按下的时间戳
            if (isKeyPressed)
            {
                system->keys[i].state = KEY_DOWN;
                system->keys[i].timestamp = time(NULL);
                system->keys[i].isPressed = true; // 标记按键为被按下状态
            }
            break;
        case KEY_DOWN:
            // 如果检测到按键被释放，则将按键状态切换回空闲状态，并标记按键为已释放状态
            if (!isKeyPressed)
            {
                system->keys[i].state = KEY_IDLE;
                system->keys[i].isPressed = false; // 标记按键为未被按下状态
                system->keys[i].isReleased = true; // 标记按键为已释放状态
            }
            else
            {
                // 如果按键仍然被按下且按下时间超过一定时间（例如1秒），则将按键状态切换为长按状态
                time_t currentTime = time(NULL);
                if (currentTime - system->keys[i].timestamp >= 1)
                {
                    system->keys[i].state = KEY_LONG_PRESS;
                }
            }
            break;
        case KEY_LONG_PRESS:
            // 如果检测到按键被释放，则将按键状态切换回空闲状态，并标记按键为已释放状态
            if (!isKeyPressed)
            {
                system->keys[i].state = KEY_IDLE;
                system->keys[i].isReleased = true; // 标记按键为已释放状态
            }
            break;
        default:
            break;
        }
    }

    // 在这里可以继续扩展处理双击等其他按键状态
}

