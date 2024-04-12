#ifndef __KEY_H__
#define __KEY_H__

#define KEY_NUMBER 4

// 状态枚举变量
typedef enum
{
    IDEL,
    pressing_bounce,
    release_bounce,
    PRESSED,

} Keystate;

// 定义Key结构体用于批量声明Keystate状态机
typedef struct
{
    Keystate Key[KEY_NUMBER];
} Key;

// 对整体整个Key结构体，按键系统进行初始化
void KeyInit(Key);

void KeyInit(Key *key) 
{
    for(int i = 0; i < KEY_NUMBER; i++)
    {
        key->Key[i].IDLE = 0;
        key->Key[i].pressing_bounce
    }

};

#endif
