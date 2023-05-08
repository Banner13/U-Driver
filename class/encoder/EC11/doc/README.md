[TOC]

### How to use EC11 driver

#### EC11 Init
	需要实现三个函数：
	EC11_PinInit：配置GPIO为输入，并使能相应Pin脚的边沿(上下边沿)中断。
    EC11_Read_A	：读取 A Pin 的状态。
    EC11_Read_B	：读取 B Pin 的状态。
	配置旋转绝对值: 确保count值在一定范围内。

	然后创建 EC11 实例，可以通过 EC11_Remove 释放实例。
```c
struct EC11* Example_EC11_Create(void)
{
    struct EC11_Init initStruct;

    initStruct.HardwareInit =   EC11_PinInit;
    initStruct.ReadA        =   EC11_Read_A;
    initStruct.ReadB        =   EC11_Read_B;
    initStruct.modulus      =   100U;

    return EC11_Init(&initStruct);
}
```

#### Enable callbak function
	创建实例后，需要在GPIO的中断回调中进行 EC11 的处理。此时实例已在别的文件中创建，只需要在A、B对应的GPIO中断回调中调用 CallbackProcess 即可。
```c
extern struct EC11* g_EC11;
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        /* Clear the EXTI line 15 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line12);
        g_EC11->CallbackProcess(g_EC11->this);
    }
    else if(EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        /* Clear the EXTI line 15 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line14);
        g_EC11->CallbackProcess(g_EC11->this);
    }
}
```

#### Usage
```c
struct EC11* g_EC11;

int main(void)
{
    g_EC11 = Example_EC11_Create();

    while (1)
    {
        count = g_EC11->GetModCount(g_EC11->this);
    }

    return count;
}

```

### API
```c
struct EC11 {
//  public
	// this 指针指向实例本身，使得其他函数可以访问实例中的变量。虽然这对C本身来说是多余的，但我不想让有些变量直接裸奔。
    struct EC11 *this;
    // CallbackProcess GPIO中断回调需要用该函数进行处理。
    void (*CallbackProcess)(struct EC11 *this);
    // GetSumCount 获取实例的总计数。
    int (*GetSumCount)(struct EC11 *this);
    // SetSumCount 设置实例的总计数。
    void (*SetSumCount)(struct EC11 *this, int count);
    // GetSumCount 获取当前的绝对值。
    unsigned int (*GetModCount)(struct EC11 *this);
    // SetModulus 设置绝对值的最大值。
    void (*SetModulus)(struct EC11 *this, int modulus);
};
```