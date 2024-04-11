// 有限状态机编程Finite State Machine

#include <stdio.h>

// 定义状态枚举
typedef enum
{
    STATE_IDLE,
    STATE_A,
    STATE_B,
    STATE_C,
    NUM_STATES
} State;

// 定义状态机结构体
typedef struct
{
    State currentState;
    // 其他状态机需要的变量
} StateMachine;

// 函数声明
void initStateMachine(StateMachine *machine);
void updateStateMachine(StateMachine *machine);
void setState(StateMachine *machine, State newState);

int main()
{
    StateMachine machine;
    initStateMachine(&machine);

    // 在这里执行状态机更新
    while (1)
    {
        updateStateMachine(&machine);
        // 在这里进行其他操作
    }

    return 0;
}

// 初始化状态机
void initStateMachine(StateMachine *machine)
{
    machine->currentState = STATE_IDLE;
    // 进行其他初始化
}

// 更新状态机
void updateStateMachine(StateMachine *machine)
{
    switch (machine->currentState)
    {
    case STATE_IDLE:
        // 执行状态IDLE下的操作
        printf("Current state: IDLE\n");
        setState(machine, STATE_A);
        break;
    case STATE_A:
        // 执行状态A下的操作
        printf("Current state: A\n");
        setState(machine, STATE_B);
        break;
    case STATE_B:
        // 执行状态B下的操作
        printf("Current state: B\n");
        setState(machine, STATE_C);
        break;
    case STATE_C:
        // 执行状态C下的操作
        printf("Current state: C\n");
        setState(machine, STATE_IDLE);
        break;
    default:
        // 处理未知状态
        printf("Unknown state!\n");
        setState(machine, STATE_IDLE);
        break;
    }
}

// 设置新状态
void setState(StateMachine *machine, State newState)
{
    machine->currentState = newState;
}

#define PEOPLE_NUMBER 4 
typedef struct 
{
    Person number[PEOPLE_NUMBER]; /* data */
}numbers_state;
