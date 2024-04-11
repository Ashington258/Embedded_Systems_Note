#ifndef KEY_DETECTION_H
#define KEY_DETECTION_H

#include <stdbool.h>
#include <time.h>

#define MAX_KEYS 4

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

typedef struct
{
    Key keys[MAX_KEYS]; // 多个按键信息
    // 其他可能需要的变量
} KeyDetectionSystem;

// 函数声明
void initKeyDetectionSystem(KeyDetectionSystem *system);
void updateKeyDetectionSystem(KeyDetectionSystem *system, bool isKeyPressed);

#endif /* KEY_DETECTION_H */
