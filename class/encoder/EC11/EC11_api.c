
/* *****************************************************************************
 *
 *  ec11 rotary encoder driver
 *  author: huke
 *  date:   2023-4-30
 *  description: ec11 code
 * 
 * ***************************************************************************/
#include "ec11_api.h"

// User header
#include "board.h"
/* *****************************************************************************
 *  code
 * ****************************************************************************/

// Need config A and B as input pin, and enable interrupt
void EC11_PinInit(void)
{
    EXTI_InitTypeDef   EXTI_InitStructure;
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Mode   =   GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Pin    =   GPIO_Pin_12 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_PuPd   =   GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource12);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource14);

    EXTI_InitStructure.EXTI_Line = EXTI_Line12 | EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

// Read Pin A
char EC11_Read_A(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
}

// Read Pin B
char EC11_Read_B(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
}

struct EC11* Example_EC11_Create(void)
{
    struct EC11_Init initStruct;

    initStruct.HardwareInit =   EC11_PinInit;
    initStruct.ReadA        =   EC11_Read_A;
    initStruct.ReadB        =   EC11_Read_B;
    initStruct.modulus      =   100U;

    return EC11_Init(&initStruct);
}

/*


*/

