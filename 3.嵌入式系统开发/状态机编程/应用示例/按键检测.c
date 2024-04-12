#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

// 在示例中，存在两个结构体的原因是为了更好地组织代码和数据。让我来解释一下：

// 1. * *KeyState 枚举： * *
//         -这个枚举定义了按键的不同状态，如空闲、按下、消抖、短按、长按和双击状态。 -
//     枚举提供了一种简洁的方式来表示不同的按键状态，让代码更易读和理解。

//  2. * *Key 结构体： * *
//         -这个结构体用于表示单个按键的状态和相关信息。 -
//     每个按键都有自己的状态、时间戳以及其他标记，如是否被按下、是否被释放、是否被双击等。这些信息是与每个按键相关的，因此需要一个结构体来存储。

//         通过将按键的状态信息封装在`Key`结构体中，可以更好地管理和处理每个按键的状态。同时，使用`KeyState`枚举可以让代码更清晰地表达按键的不同状态。这种组织结构使得代码更模块化、可维护性更高，并且易于扩展和修改。

// 定义按键状态枚举
typedef enum
{
    KEY_IDLE,         // 按键空闲状态，表示按键未被按下
    KEY_DOWN,         // 按键按下状态，表示按键已被按下但未释放
    KEY_DEBOUNCE,     // 按键消抖状态，用于消除按键抖动影响
    KEY_SHORT_PRESS,  // 按键短按状态，表示按键被短暂按下
    KEY_LONG_PRESS,   // 按键长按状态，表示按键被长时间按下
    KEY_DOUBLE_CLICK, // 按键双击状态，表示按键被连续快速按下两次
    NUM_KEY_STATES    // 按键状态枚举总数，用于数组大小等
} KeyState;

// 定义按键结构体
typedef struct
{
    KeyState state;       // 当前按键状态
    time_t timestamp;     // 按键状态改变时的时间戳
    bool isPressed;       // 按键是否被按下
    bool isReleased;      // 按键是否被释放
    bool isDoubleClicked; // 按键是否被双击
} Key;

// 定义按键检测系统结构体
#define MAX_KEYS 4
typedef struct
{
    Key keys[MAX_KEYS]; // 多个按键信息
    // 其他可能需要的变量
} KeyDetectionSystem;

// 函数声明
void initKeyDetectionSystem(KeyDetectionSystem *system);
void updateKeyDetectionSystem(KeyDetectionSystem *system, bool isKeyPressed);

int main()
{
    KeyDetectionSystem system; // 对按键系统进行声明，利用结构体对按键进行批量化声明
    initKeyDetectionSystem(&system);

    // 模拟按键输入，实际情况下可能需要使用中断或轮询方式获取按键状态
    bool isKeyPressed[MAX_KEYS] = {false}; // 数组表示多个按键的按下状态
    while (1)
    {
        // 获取按键状态
        // 这里假设 isKeyPressed 是由外部更新得到的，true 表示按键按下，false 表示按键释放
        for (int i = 0; i < MAX_KEYS; ++i)
        {
            updateKeyDetectionSystem(&system, isKeyPressed[i]);
        }

        // 在这里进行其他操作
    }

    return 0;
}

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