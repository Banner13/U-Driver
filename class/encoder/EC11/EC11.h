
/* *****************************************************************************
 *
 *  ec11 rotary encoder driver
 *  author: huke
 *  date:   2023-4-30
 *  description: ec11 headfile
 * 
 * ***************************************************************************/
#ifndef EC11_H
#define EC11_H

#include "ec11_api.h"

/* *****************************************************************************
 *  definition
 * ****************************************************************************/
enum EC11_Status{
    EC11_STATUS_FREE        = 0,

    //  CCW Status
    EC11_STATUS_CCW_START   = 1,
    EC11_STATUS_CCW_RUNNING = 2,
    EC11_STATUS_CCW_WAIT    = 3,

    //  CW Status
    EC11_STATUS_CW_START    = 5,
    EC11_STATUS_CW_RUNNING  = 6,
    EC11_STATUS_CW_WAIT     = 7,
};

struct EC11 {
//  public
    struct EC11 *this;
    void (*CallbackProcess)(struct EC11 *this);
    int (*GetSumCount)(struct EC11 *this);
    void (*SetSumCount)(struct EC11 *this, int count);
    unsigned int (*GetModCount)(struct EC11 *this);
    void (*SetModulus)(struct EC11 *this, int modulus);
//  priviate
    volatile enum EC11_Status currentStatus;
    volatile int sumCount;
    unsigned int modulus;
    char (*ReadA)(void);
    char (*ReadB)(void);
};

struct EC11_Init {
//  public
    unsigned int modulus;
    void (*HardwareInit)(void);
    char (*ReadA)(void);
    char (*ReadB)(void);
};


/* *****************************************************************************
 *  prototype
 * ****************************************************************************/
struct EC11* EC11_Init(struct EC11_Init *initStruct);
void EC11_Remove(struct EC11 *ec11);

#endif  // EC11_H